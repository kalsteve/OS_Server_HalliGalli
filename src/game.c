/**
 * 게임 관련 함수들을 정의한 소스 파일
*/
#include "game.h"

// 게임 초기화 함수
Game* initGame() {
    // 카드 덱 초기화
    CardDeck* cardDeck = initCardDeck(MAX_CARD_NUM);
    // 플레이어 초기화
    Player* player = initPlayer();

    // 게임 상태 초기화
    Game* game;
    game = (Game *)malloc(sizeof(Game*));
    game->status = GAME_INIT;

    return game;
}

// 플레이어를 게임에 참여시키는 함수
int joinPlayer(Game* game, Player* player) {
    // 게임 상태가 초기화 상태가 아니면 실패
    if(game->status != GAME_INIT) {
        return -1;
    }
    // 게임에 참여한 플레이어 수가 최대 플레이어 수를 넘으면 실패
    if(game->join_num >= MAX_PLAYER_NUM) {
        return -1;
    }

    // 게임에 플레이어 추가
    addPlayer(game->players, player);
    // 게임에 참여한 플레이어 수 증가
    game->join_num++;
    return 0;
}

// 플레이어의 준비 상태를 변경하는 함수
int readyPlayer(Game* game, Player* player) {
    // 게임 상태가 초기화 상태가 아니면 실패
    if(game->status != GAME_INIT) {
        perror("gameStatus is not GAME_INIT");
        return -1;
    }
    // 게임에 참여한 플레이어 수가 최대 플레이어 수를 넘으면 실패
    if(game->joinNum >= MAX_PLAYER_NUM) {
        perror("joinNum is over MAX_PLAYER_NUM");
        return -1;
    }

    // 플레이어의 준비 상태 변경
    for(int count = 0; count < game->join_num ; count++) {

        if(game->players[count].id == player.id) {
            game->players[count].info = PLAYER_READY;
        }
    }
    
    return 0;
}

// 게임 준비 완료 확인 함수
int isReady(Game* game) {
    // 게임 상태가 초기화 상태가 아니면 실패
    if(game->status != GAME_INIT) {
        perror("gameStatus is not GAME_INIT");
        return -1;
    }

    for(int count = 0; count < game->join_num ; count++) {

        if(game->players[count]->info != PLAYER_READY) {
            return -1;
        }
    }
    
    return 0;
}


// 게임 시작 함수
void startGame(Game* game) {
    // 게임 상태 변경
    game->status = GAME_START;

    for(int count = 0; count < game->join_num ; count++) {
        // 플레이어의 상태 변경
        game->players[count]->info = PLAYER_GAMING;
    }

    // 플레이어에게 카드 배분
    distributeCard(game);

}

//
int PlayerTurn(Game* game, Player* player) {

    // 게임 상태가 시작 상태가 아니면 실패
    if(game->status != GAME_START) {
        perror("gameStatus is not GAME_START");
        return -1;
    }

    // 플레이어의 상태가 게임 중이 아니면 실패
    if(player->info != PLAYER_GAMING) {
        perror("playerStatus is not PLAYER_GAMING");
        return -1;
    }

    // n번 플레이어의 턴
    game->player_turn++;
    game->player_turn %= game->join_num;

    return 0;
}

int putCardOnTable(Game* game, Player* player) {
    // 게임 상태가 시작 상태가 아니면 실패
    if(game->status != GAME_START) {
        perror("gameStatus is not GAME_START");
        return -1;
    }

    // 플레이어의 상태가 게임 중이 아니면 실패
    if(player->info != PLAYER_GAMING) {
        perror("playerStatus is not PLAYER_GAMING");
        return -1;
    }

    putCardToDeck(player->cardDeckOnTable, drawCard(player->cardDeck));
}

int distributeCard(Game* game) {
    int index = 0;
    int card_num = MAX_CARD_NUM / game->join_num;
    int max_index = MAX_CARD_NUM - card_num;

    // 게임 상태가 시작 상태가 아니면 실패
    if(game->status != GAME_START) {
        perror("gameStatus is not GAME_START");
        return -1;
    }

    for(int count = 0; count < game->join_num ; count++) {
        splitCardDeck(game->players[count++]->cardDeck, game->cardDeck, index, card_num);
        index += card_num;
    }

}

int takeCardFromPlayersDeck(Game* game, Player* player) {
    // 게임 상태가 시작 상태가 아니면 실패
    if(game->status != GAME_START) {
        perror("gameStatus is not GAME_START");
        return -1;
    }

    // 플레이어의 상태가 게임 중이 아니면 실패
    if(player->info != PLAYER_GAMING) {
        perror("playerStatus is not PLAYER_GAMING");
        return -1;
    }

    // 플레이어의 앞 카드들을 해당 플레이어에게 주고, 플레이어의 카드 덱에 추가
    for(int count = 0; count < game->join_num ; count++) {
        if(game->players[count]->id != player->id) {
            putCardToDeck(player->cardDeck, game->players[count]->cardDeckOnTable); //문제가 있음....
        }
    }

    return 0;
}

int takeCardFromTable(Game* game, Player* player) {
    // 게임 상태가 시작 상태가 아니면 실패
    if(game->status != GAME_START) {
        perror("gameStatus is not GAME_START");
        return -1;
    }

    // 플레이어의 상태가 게임 중이 아니면 실패
    if(player->info != PLAYER_GAMING) {
        perror("playerStatus is not PLAYER_GAMING");
        return -1;
    }

    // 플레이어의 앞 카드들을 해당 플레이어에게 주고, 플레이어의 카드 덱에 추가
    putCardDeckToDeck(player->cardDeck, game->cardDeckOnTable);

    return 0;
}
