#include "game.h"

#define PORT 4892


pthread_mutex_t g_mutex;

int main() {
    Player temp_player;
    Game* game = initGame();
    int socket = initSocket(PORT, MAX_CLIENT_NUM);
    pthread_t game_thread;
    pthread_t player_thread[MAX_CLIENT_NUM];
    
    pthread_mutex_init(&g_mutex, NULL);
    
    while(game->status != GAME_INIT) {
        pthread_create(&game_thread, NULL, wait_Player, (void*)socket);
        pthread_join(game_thread, (void*)&temp_player);

        joinPlayer(game, &temp_player);

        readyPlayer(game, &temp_player);
    
        for(int i = 0; i < game->join_num; i++) {
            pthread_create(&player_thread[i], NULL, getPlayerAction, (void*)socket);
        }
    }

    startGame(game);

    // 
    for(int i = 0; i < game->join_num; i++) {
        
        pthread_create(&game_thread, NULL, playerJoinGame, (void*)&temp_game);
    }


    

}

void* wait_Player(void* socket) {
    Player* player = initPlayer();
    int server_sock_fd = (int)socket;
    int client_socket_fd;
    struct sockaddr_in client_addr;
    
    client_socket_fd = acceptSocket(server_sock_fd, &client_addr, sizeof(client_addr));

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

void* playerJoinGame(void* game) {
    Game* in_game = (Game*)game;
    Player* in_game_player = (Player*)in_game->players;
    int client_socket_fd = in_game_player->id;
    char* data;
    int action;
    
    recvSocket(client_socket_fd, data, MAX_BUFFER_SIZE);
    action = deserializePlayerAction(data);

    if(action == PLAYER_DRAW) {
        putCardOnTable(in_game_player);
        sendSocket(client_socket_fd, serializeSendData(game, in_game_player), MAX_BUFFER_SIZE);
    }
    
    return NULL;
}

void* sendPlayerData(void* socket) {
    
}