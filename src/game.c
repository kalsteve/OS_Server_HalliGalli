/**
 * 게임 관련 함수들을 정의한 소스 파일
*/
#include "game.h"

// 게임 초기화 함수
Game initGame() {
    // 카드 덱 초기화
    cardDeck = initCardDeck();
    // 플레이어 초기화
    player = initPlayer();
    // 게임 상태 초기화
    Game *game;
    game = (Game *)malloc(sizeof(Game));
    game->status = GAME_STATUS_READY;

    return game;
}

// 게임 시작 함수
void startGame(Game *game) {
    // 게임 상태 변경
    game->status = GAME_STATUS_START;
    // 플레이어에게 카드 배분
    splitCardDeck(player->cardDeck, cardDeck, 0, CARD_NUM_MAX, PLAYER_CARD_NUM);
}