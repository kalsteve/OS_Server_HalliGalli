/**
 * 게임 관련 함수들을 정의한 소스 파일
*/
#include "game.h"

// 게임 초기화 함수
Game* initGame() {
    // 카드 덱 초기화
    CardDeck* cardDeck = initCardDeck(MAX_CARD_NUM);
    // 플레이어 초기화
    Player* player = initPlayer(0, MAX_CARD_NUM);


    // 게임 상태 초기화
    Game* game;
    game = (Game *)malloc(sizeof(Game));
    game->status = GAME_INIT;
    game->join_num = 0;
    game->player_turn = 0;
    game->cardDeck = cardDeck;
    game->players = player;

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
    game->players = addPlayer(game->players, player);

    player->info = PLAYER_INIT;
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
    if(game->join_num >= MAX_PLAYER_NUM) {
        perror("joinNum is over MAX_PLAYER_NUM");
        return -1;
    }

    // 플레이어의 준비 상태 변경
    for(int count = 0; count < game->join_num ; count++) {

        if(game->players[count].id == player->id) {
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

    if (game->join_num < 1) {
        return 0;
    }
    
    //test
    return 1;

    for(int count = 0; count < game->join_num ; count++) {

        if(game->players[count].info != PLAYER_READY) {
            return 0;
        }
    }
    
    return 1;
}


// 게임 시작 함수
void startGame(Game* game) {
    // 게임 상태 변경
    game->status = GAME_START;

    for(int count = 0; count < game->join_num ; count++) {
        // 플레이어의 상태 변경
        game->players[count].info = PLAYER_GAMING;
    }

    // 플레이어에게 카드 배분
    distributeCard(game);

}

// 플레이어의 턴을 종료하는 함수
int playerTurnEnd(Game* game, Player* player) {

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

    // 플레이어의 턴이 아니면 실패
    if(game->player_turn != player->id) {
        perror("playerTurn is not player");
        return -1;
    }

    // n번 플레이어의 턴
    game->turn++;
    game->player_turn = game->players[game->turn].id;
    game->turn %= game->join_num;

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

    return 0;
}

int distributeCard(Game* game) {
    int index = 0;
    int card_num = MAX_CARD_NUM / game->join_num;

    // 게임 상태가 시작 상태가 아니면 실패
    if(game->status != GAME_START) {
        perror("gameStatus is not GAME_START");
        return -1;
    }

    for(int count = 0; count < game->join_num ; count++) {
        splitCardDeck(game->players[count++].cardDeck, game->cardDeck, index, card_num);
        index += card_num;
    }

    return 0;

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
        if(game->players[count].id != player->id) {
            putCardToDeck(player->cardDeck, drawCard(game->players[count].cardDeckOnTable));
        }
    }

    return 0;
}

int giveCardToPlayersDeck(Game* game, Player* player) {
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

    // 플레이어의 카드 덱의 카드들을 해당 플레이어의 앞 카드에 추가
    for(int count = 0; count < game->join_num; count++) {
        if(game->players[count].id != player->id) {
            putCardToDeck(game->players[count].cardDeck, drawCard(player->cardDeck));
        }
    }

    return 0;
}

void endGame(Game* game) {
    // 게임 상태 변경
    game->status = GAME_END;

    destroyGame(game);
}

int isPlayerDeckEmpty(Player* player) {
    if(player->cardDeck->card_num == 0) {
        return 1;
    }
    return 0;
}

int defeadPlayer(Game* game, Player* player) {
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

    // 플레이어의 상태 변경
    player->info = PLAYER_LOSE;

    return 0;
}


Card readCardFromPlayersDeckOnTable(Player* player) {
    // 플레이어의 앞 카드를 반환
    return player->cardDeckOnTable->cards[0];
}


int isValidBell(Game* game, Player* player) {
    int count[MAX_CARD_TYPE] = {0,};
    int valid = 0;

    for(int i = 0; i < game->join_num; i++) {
        Card card = readCardFromPlayersDeckOnTable(&game->players[i]);
        count[card.type] += card.volume;
    }

    for(int i = 0; i < MAX_CARD_TYPE; i++) {
        if(count[i] == 5) {
            valid = 1;
        }
    }
    
    return valid;
}

int ringBell(Game* game, Player* player) {
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

    // 울린 벨이 유효한 벨이면
    if(isValidBell(game, player)) {
        // 테이블에 있는 가드를 자신의 덱으로 가져옴
        takeCardFromPlayersDeck(game, player);
        return 0;
    }

    // 유요한 벨이 아니면
    // 플레이어의 덱을 상대방의 덱에 추가
    giveCardToPlayersDeck(game, player);


    return 0;
}


int checkGameState(Game* game, GAME_STATUS requiredState) {
    if(game->status != requiredState) {
        perror("Invalid game state");
        return -1;
    }
    return 0;
}

int checkPlayerState(Player* player, PLAYER_STATUS requiredState) {
    if(player->info != requiredState) {
        perror("Invalid player state");
        return -1;
    }
    return 0;
}

void destroyGame(Game* game) {
    // 게임에 참여한 플레이어들의 메모리 해제
    for(int count = 0; count < game->join_num ; count++) {
        destroyPlayer(&game->players[count]);
    }

    // 게임에 사용된 카드 덱의 메모리 해제
    destroyCardDeck(game->cardDeck);

    // 게임의 메모리 해제
    free(game);
}
