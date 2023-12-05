


#include "main.h"

#define PORT 4892

Game* game;
pthread_mutex_t g_mutex;

int main() {
    game = initGame();
    Player temp_player;
    
    int socket_fd = initSocket(PORT, MAX_CLIENT_NUM);
    pthread_t game_thread;
    pthread_t player_thread[MAX_CLIENT_NUM];

    
    
    pthread_mutex_init(&g_mutex, NULL);
    
    
    // 플레이어 대기
    while(game->status != GAME_INIT) {
        pthread_create(&game_thread, NULL, wait_Player, (void *)socket_fd);
        pthread_join(game_thread, (void*)&temp_player);

        joinPlayer(game, &temp_player);
        readyPlayer(game, &temp_player);
    
        for(int i = 0; i < game->join_num; i++) {
            pthread_create(&player_thread[i], NULL, getPlayerAction, (void*)socket_fd);
        }
    }

    startGame(game);

    // 게임시작으로 인한 플레이어 스레드 생성
    for(int i = 0; i < game->join_num; i++) {
        pthread_create(&game_thread, NULL, playerJoinGame, (void*)&game->players[i]);
    }

    // 게임 진행
    while(game->status != GAME_END)

    // 게임 종료
    destroyGame(game);
    closeSocket(socket_fd);
    pthread_mutex_destroy(&g_mutex);
}

void* wait_Player(void* socket) {
    Player* player;
    int server_sock_fd = (int)socket;
    int client_socket_fd;
    struct sockaddr_in client_addr;
    
    client_socket_fd = acceptSocket(server_sock_fd, &client_addr, sizeof(client_addr));
    player = initPlayer(client_socket_fd, MAX_CARD_NUM);

    player->id = client_socket_fd;

    // 클라이언트 소켓 반환
    return (void*)player;
}

void* getPlayerAction(void* socket) {
    int client_socket_fd = (int)socket;
    char* data;
    int* action;
    
    recvSocket(client_socket_fd, data, MAX_BUFFER_SIZE);
    *action = deserializePlayerAction(data);
    
    return (void*)action;
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