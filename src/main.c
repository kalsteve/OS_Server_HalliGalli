


#include "main.h"

#define PORT 4892

Game* game;
pthread_mutex_t g_mutex;

int main() {
    game = initGame();
    
    int socket_fd = initSocket(PORT, MAX_CLIENT_NUM);
    pthread_t game_thread;
    pthread_t player_thread;
    
    pthread_mutex_init(&g_mutex, NULL);
    
    pthread_create(&game_thread, NULL, wait_Player, (void *)socket_fd);
    pthread_join(game_thread, NULL);
    
    // 플레이어 대기
    while(game->status == GAME_INIT) {
        // 플레이어가 게임을 시작하면 시작
        if(isReady(game)) {
                pthread_mutex_lock(&g_mutex);
                game->status = GAME_START;
                pthread_mutex_unlock(&g_mutex);
                break;
        }
    }

    

    pthread_mutex_lock(&g_mutex);
    startGame(game);
    pthread_mutex_unlock(&g_mutex);

    // 게임 시작 알림
    pthread_create(&player_thread, NULL, sendALLPlayerAction, (void*)PLAYER_GAMING);
    pthread_join(player_thread, NULL);
    
    // 게임 시작하는 플레이어를 정함
    pthread_mutex_lock(&g_mutex);
    game->player_turn = game->players[game->turn].id;
    pthread_mutex_unlock(&g_mutex);

    // 게임시작으로 인한 플레이어 스레드 생성
    for(int i = 0; i < game->join_num; i++) {
        pthread_create(&game_thread, NULL, playerJoinGame, (void*)&game->players[i]);
    }

    // 게임 진행
    while(game->status != GAME_END) {

    }

    // 게임 종료
    destroyGame(game);
    closeSocket(socket_fd);
    pthread_mutex_destroy(&g_mutex);
}

void* wait_Player(void* socket) {
    int server_sock_fd = (int)socket;

    while(game->status == GAME_INIT) {
        Player* player;
        int client_socket_fd;
        struct sockaddr_in client_addr;
        PLAYER_STATUS player_status;

        client_socket_fd = acceptSocket(server_sock_fd, &client_addr, sizeof(client_addr));
        player = initPlayer(client_socket_fd, MAX_CARD_NUM);
    
        if(game->status != GAME_INIT) {
            perror("gameStatus is not GAME_INIT");
            sendALLPlayerAction((void*)PLAYER_DENY);
            return NULL;
        }

        pthread_mutex_lock(&g_mutex);
        // 플레이어에게 게임 정보 전송
        sendPlayerAction(player);
        // 플레이어를 추가하고 메모리 조정
        joinPlayer(game, player);
        pthread_mutex_unlock(&g_mutex);

        // 플레이어를 더 받을지 결정
        player_status = (PLAYER_STATUS)getPlayerAction((void*)&client_socket_fd);

        if(player_status == PLAYER_NOT_WANT) {
            break;
        }
        
    }

    

    // 클라이언트 소켓 반환
    return NULL;
}

void* getPlayerAction(void* socket) {
    int client_socket_fd = *((int*)socket);
    Player* player;
    char* data;
    int* action;
    pthread_t player_thread;
    
    recvSocket(client_socket_fd, data, MAX_BUFFER_SIZE);
    *action = deserializePlayerAction(data);

    // 플레이어 구하기
    for(int i = 0; i < game->join_num; i++) {
        if(game->players[i].id == client_socket_fd) {
            player = &game->players[i];
        }
    }

    if(*action == PLAYER_READY) {
        pthread_mutex_lock(&g_mutex);
        readyPlayer(game, player);
        pthread_mutex_unlock(&g_mutex);
        sendPlayerAction(player);
    }

    if(*action == PLAYER_START) {
        pthread_mutex_lock(&g_mutex);
        pthread_create(&player_thread, NULL, sendALLPlayerAction, (void*)PLAYER_START);
        pthread_mutex_unlock(&g_mutex);
    }

    
    
    return NULL;
}

void* playerJoinGame(void* player) {
    Player* in_game_player = (Player*)player;
    int client_socket_fd = in_game_player->id;
    char* data;
    int action;

    while(1) {
        // 플레이어 턴이면
        if(game->player_turn == in_game_player->id){
            recvSocket(client_socket_fd, data, MAX_BUFFER_SIZE);
            action = deserializePlayerAction(data);

            // 플레이어가 종을 쳤을 때
            if(action == PLAYER_BELL) {
                pthread_mutex_lock(&g_mutex);
                ringBell(game, in_game_player);
                pthread_mutex_unlock(&g_mutex);
                data = serializeSendData(game, in_game_player, MAX_BUFFER_SIZE);
                sendSocket(client_socket_fd, data, MAX_BUFFER_SIZE);
                free(data);
            }

            // 플레이어가 카드를 냈을 때
            if(action == PLAYER_DRAW) {
                pthread_mutex_lock(&g_mutex);
                putCardOnTable(game, in_game_player);
                pthread_mutex_unlock(&g_mutex);
                data = serializeSendData(game, in_game_player, MAX_BUFFER_SIZE);
                sendSocket(client_socket_fd, data, MAX_BUFFER_SIZE);
                free(data);
            }

            // 플레이어가 턴을 종료했을 때
            if(action == PLAYER_TURN_END) {
                pthread_mutex_lock(&g_mutex);
                playerTurnEnd(game, in_game_player);
                pthread_mutex_unlock(&g_mutex);
                data = serializeSendAction(in_game_player->id, PLAYER_GAMING, MAX_BUFFER_SIZE);
                sendSocket(client_socket_fd, data, MAX_BUFFER_SIZE);
                free(data);
            }
            
            // 플레이어가 패배했을 때
            if(isPlayerDeckEmpty(in_game_player)) {
                in_game_player->info = PLAYER_LOSE;
                game->join_num--;
                destroyPlayer(in_game_player);
                data = serializeSendAction(in_game_player->id, PLAYER_BELL, MAX_BUFFER_SIZE);
                sendSocket(client_socket_fd, data, MAX_BUFFER_SIZE);
                free(data);
                break;
            }
        }     
    }
    
    return NULL;
}

void* sendALLPlayerAction(void* arg) {
    char* data;
    PLAYER_STATUS player_status = (PLAYER_STATUS)arg;

    // 플레이어가 스타트를 눌렀을 때
    if(player_status == PLAYER_START) {
        for(int i = 0; i < game->join_num; i++) {
            if(game->players[i].info == PLAYER_READY) {
                data = serializeSendAction(game->players[i].id , PLAYER_NOT_READY, MAX_BUFFER_SIZE);
                sendSocket(game->players[i].id , data, MAX_BUFFER_SIZE);
            }

            if(game->players[i].info == PLAYER_INIT) {
                data = serializeSendAction(game->players[i].id , ALL_PLAYER_NOT_READY, MAX_BUFFER_SIZE);
                sendSocket(game->players[i].id , data, MAX_BUFFER_SIZE);
            }
        }
    }

    // 플레이어가 게임을 시작했을 때
    if(player_status == PLAYER_GAMING) {
        for(int i = 0; i < game->join_num; i++) {
            if(game->players[i].info == PLAYER_READY) {
                data = serializeSendAction(game->players[i].id , PLAYER_GAMING, MAX_BUFFER_SIZE);
                sendSocket(game->players[i].id , data, MAX_BUFFER_SIZE);
            }
        }
    }


    return NULL;
}

void* sendPlayerAction(void* player) {
    Player* in_player = (Player*)player;
    char* data;

    data = serializeSendAction(in_player->id, in_player->info, MAX_BUFFER_SIZE);
    sendSocket(in_player->id, data, MAX_BUFFER_SIZE);
    free(data);

    return NULL;
}

void* sendPlayerData(void* arg) {
    Player* player = (Player*)arg;
    char* data;

    data = serializeSendData(game, player, MAX_BUFFER_SIZE);
    sendSocket(player->id, data, MAX_BUFFER_SIZE);
    free(data);

    return NULL;
}
