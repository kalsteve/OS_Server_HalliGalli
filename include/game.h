/**
 * 할리갈리 게임을 진행하는 함수들을 정의한 헤더 파일입니다. 
*/

#ifndef _GAME_H_
#define _GAME_H_

#include "card.h"
#include "player.h"
#include "dataSerializer.h"

#define MAX_PLAYER_NUM 6

typedef enum {
    GAME_INIT,
    GAME_READY,
    GAME_START,    
    GAME_END
} GAME_STATUS;

typedef enum {
    PLAYER_INIT,
    PLAYER_READY,
    PLAYER_GAMING,
    PLAYER_LOSE,
    PLAYER_WIN,
    PLAYER_DRAW,
    PLAYER_BELL

} PLAYER_STATUS;

/**
 * 할리 갈리 게임의 정보를 담고 있는 구조체입니다.
 * @param playerNum 게임에 참여할 수 있는 플레이어의 수
 * @param joinNum 현재 게임에 참여한 플레이어의 수
 * @param players 게임에 참여한 플레이어들의 정보를 담고 있는 구조체의 배열
 * @param cardDeck 게임에 사용되는 카드 덱
 * @param turn 현재 게임의 턴
 * @param gameStatus 현재 게임의 상태
 * 
*/
typedef struct _Gameinfo{
    int player_num;
    int join_num;
    Player* players;
    CardDeck* cardDeck;
    int player_turn;
    int turn;
    GAME_STATUS status;
} Game;

/**
 * 할리갈리게임을 초기화하는 함수
 * @return 게임의 정보를 담고 있는 구조체
*/
Game* initGame();

/**
 * 플레이어를 게임에 참여시키는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임에 참여시킬 플레이어
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int joinPlayer(Game* game, Player* player);

/**
 * 플레이어의 준비 상태를 변경하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임을 시작할 플레이어
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int readyPlayer(Game* game, Player* player);

/**
 * 게임이 준비가 됬는지 확인하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
*/
int isReady(Game* game);

/**
 * 할리갈리 게임을 시작하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int startGame(Game* game);

/**
 * 플레이어에게 카드를 배분하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int distributeCard(Game* game);

/**
 * 플레이어의 턴을 진행하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임을 진행할 플레이어
*/
void pLayerTurn(Game* game, Player* player);


/**
 * 플레이어가 종을 쳤을 때
 * @param game 게임의 정보를 담고 있는 구조체
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int ringBell(Game* game, Player* player);

/**
 * 플레이어가 종을 친 것이 유효한지 확인하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 종을 친 플레이어
*/
int isValidBell(Game** game, Player* player);

/**
 * 플레이어가 종을 친 것이 유효하지 않을 때
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 종을 친 플레이어
*/
void invalidBell(Game* game, Player* player);

/**
 * 플레이어가 종을 친 것이 유효할 때
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 종을 친 플레이어
*/
void validBell(Game* game, Player* player);

/**
 * 플레이어의 카드를 다른 플레이어에게 나눠주는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 카드를 나눠줄 플레이어
 * @param target 카드를 받을 플레이어
 * @param cardNum 카드를 나눠줄 개수
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int giveCard(Game* game, Player* player, Player* target, int cardNum);

/**
 * 플레이어가 자신의 턴에서 카드를 가져오는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 카드를 가져올 플레이어
 * @param target 카드를 가져올 플레이어
*/
int giveCardToPlayersDeck(Game* game, Player* player);

/**
 * 플레이어가 자신의 턴에서 카드를 가져오는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 카드를 가져올 플레이어
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int takeCardOnTable(Game* game, Player* player);

/**
 * 플레이어가 자신의 턴에서 카드를 자신의 테이블 위에 놓는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 카드를 놓을 플레이어
*/
int putCardOnTable(Game* game, Player* player);

/**
 * 앞에 놓인 카드의 정보를 확인하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 카드를 확인할 플레이어
 * @return card 앞에 놓인 카드
*/
Card* checkCard(Game* game, Player* player);

/**
 * 플레이어가 게임을 나갈 때
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임을 나갈 플레이어
 * @return 실행 결과 (0: 성공, -1: 실패)
 */
int leaveGame(Game* game, Player* player);

/**
 * 플레이어가 졌을 때
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임에서 졌을 플레이어
*/
void loseGame(Game* game, Player* player);

/**
 * 게임을 종료하는 함수
*/
void endGame();

/**
 * 게임을 삭제하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
*/
void destroyGame(Game* game);

#endif