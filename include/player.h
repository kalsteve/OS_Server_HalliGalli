#ifndef __PLAYER_H__
#define __PLAYER_H__

/**
 * @file player.h
 * @brief 플레이어의 정보를 담고 있는 구조체를 정의한 헤더 파일입니다.
 * 
 */

#include "card.h"

typedef struct _Player{
    int id;
    int cardNum;
    int info;
    CardDeck* cardDeck;        // 플레이어가 가지고 있는 카드 덱
    CardDeck* cardDeckOnTable; // 테이블에 내려놓은 카드 덱
} Player;

Player* initPlayer();
Player* createPlayer(int id);
Player* addPlayer(Player* players, Player* player);
void destroyPlayer(Player* player);

#endif