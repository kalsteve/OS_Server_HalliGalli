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
    GAME_INIT,
    GAME_READY,
    GAME_START,    
    GAME_END
} GAME_STATUS;

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
    int playerNum;
    int joinNum;
    Player* players;
    CardDeck cardDeck;
    int turn;
    GAME_STATUS gameStatus;
} GameInfo;

typedef GameInfo* Game;

/**
 * 할리갈리게임을 초기화하는 함수
 * @return 게임의 정보를 담고 있는 구조체
*/
Game initGame();

/**
 * 플레이어를 게임에 참여시키는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임에 참여시킬 플레이어
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int joinPlayer(Game game, Player player);

/**
 * 플레이어의 준비 상태를 변경하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임을 시작할 플레이어
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int readyPlayer(Game game, Player player);

/**
 * 할리갈리 게임을 시작하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int startGame(Game game);

/**
 * 플레이어에게 카드를 배분하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
int distributeCard(Game game);

/**
 * 플레이어의 턴을 진행하는 함수
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임을 진행할 플레이어
*/
void pLayerTurn(Game game, Player player);


/**
 * 플레이어가 종을 쳤을 때
 * @param game 게임의 정보를 담고 있는 구조체
 * @return 실행 결과 (0: 성공, -1: 실패)
*/
void ringBell(Game game, Player player);

/**
 * 플레이어가 게임을 나갈 때
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임을 나갈 플레이어
 * @return 실행 결과 (0: 성공, -1: 실패)
 */
int leaveGame(Game game, Player player);

/**
 * 플레이어가 졌을 때
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 게임에서 졌을 플레이어
*/
void loseGame(Game game, Player player);


void endGame();
void destroyGame(Game game);

#endif