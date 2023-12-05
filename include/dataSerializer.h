#ifndef __DATA_SERIALIZER_H__
#define __DATA_SERIALIZER_H__

/**
 * @file dataSerializer.h
 * @brief 게임 진행에 필요한 데이터 양식인 json 형식의 문자열을 생성하는 함수들을 정의한 헤더 파일입니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>


#include "game.h"
#include "server.h"
#include "player.h"
#include "card.h"

typedef struct __ReceiveActionFormat
{
    int player_id;
    int player_action;
} ReceiveDataFormat;

typedef struct __SendDataFormat
{
    int player_id;
    int card_volume;
    int card_type;
} SendDataFormat;

typedef struct __SendActionFormat
{
    int player_id;
    int player_action;
} SendActionFormat;



/**
 * 플레이어의 행동을 json 형식의 문자열로 변환하는 함수입니다.
*/
int deserializePlayerAction(char *data);

/**
 * 보낼 데이터를 json 형식의 문자열로 변환하는 함수입니다.
 * @param game 게임의 정보를 담고 있는 구조체
 * @param player 플레이어의 정보를 담고 있는 구조체
*/
char* serializeSendData(Game* game, Player* player, int size);


char* serializeSendAction(int player_id, int player_action, int size);

#endif