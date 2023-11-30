/**
 * 할리갈리 게임을 진행하는 함수들을 정의한 헤더 파일입니다. 
*/

#ifndef _GAME_H_
#define _GAME_H_

#include "card.h"
#include "player.h"
#include "communication.h"

#define MAX_PLAYER_NUM 6

typedef enum {
    GAME_START,
    GAME_END
} GAME_STATUS;

typedef struct _Game{
    int playerNum;
    Player* players;
    CardDeck cardDeck;
    int turn;
    GAME_STATUS gameStatus;
} Game;

Game initGame();

/**
 * 게임을 시작하는 함수입니다.
 * @param playerNum 플레이어의 수
 * @return 생성된 게임 정보
*/
Game startGame();
void endGame();
void destroyGame(Game game);

Game readyGame(Game game);



#endif