#ifndef __DATA_SERIALIZER_H__
#define __DATA_SERIALIZER_H__

/**
 * @file communication.h
 * @brief 게임 진행에 필요한 데이터 양식인 json 형식의 문자열을 생성하는 함수들을 정의한 헤더 파일입니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#include "server.h"
#include "game.h"
#include "player.h"
#include "card.h"

/**
 * @brief 게임 시작을 알리는 json 형식의 문자열을 생성하는 함수입니다.
 * @param game 게임 정보
 * @return json 형식의 문자열
 */
char* makeGameStartJson(Game *game);

/**
 * @brief 플레이어의 턴을 알리는 json 형식의 문자열을 생성하는 함수입니다.
 * @param game 게임 정보
 * @return json 형식의 문자열
 */



#endif