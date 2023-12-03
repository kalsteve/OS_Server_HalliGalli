#ifndef __CARD_H__
#define __CARD_H__

/**
 * 카드 덱을 구성하는 카드의 종류와 개수를 정의한 헤더 파일입니다.
 * @file card.h
 * @brief This file contains the declaration of the card struct and its functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CARD_NUM 56
#define MAX_CARD_TYPE 4
#define MAX_CARD_VOLUME 5

//카드 종류 정의
typedef enum {
    STRAWBERRY,
    BANANA,
    LIME,
    PRUNE
} CARD_TYPE;

//카드 종류별 갯수의 정의
typedef enum {
    ONE_FRUIT = 5,
    TWO_FRUIT = 3,
    THREE_FRUIT = 3,
    FOUR_FRUIT = 2,
    FIVE_FRUIT = 1
} CARD_VOLUME;

//카드 종류별 갯수의 배열
const int CARD_VOLUMES[] = {
    ONE_FRUIT, 
    TWO_FRUIT, 
    THREE_FRUIT, 
    FOUR_FRUIT, 
    FIVE_FRUIT
};

typedef struct _Card{
    int id; //카드의 고유번호
    CARD_TYPE type; //카드의 과일 종류
    CARD_VOLUME volume; //카드의 과일 갯수
} Card;

typedef struct _CardDeck{
    int card_num;   //카드 덱의 크기
    Card *cards;     //카드 덱
} CardDeck;

/**
 * 카드 덱을 생성하는 함수입니다.
 * @param cardNum 카드 덱의 크기
 * @return 생성된 카드 덱
*/
CardDeck* initCardDeck(int card_num);

/**
 * 카드 덱을 생성하는 함수입니다.
 * @param cardNum 카드 덱의 크기
 * @return 생성된 카드 덱
*/
CardDeck* createCardDeck(int card_num);

/**
 * 카드를 설정하는 함수입니다.
 * @param card 카드 구조체
 * @param id 카드의 고유번호
 * @param type 카드의 종류
 * @param volume 카드의 과일 갯수
*/
void setCard(Card* card, int id,  CARD_TYPE type, CARD_VOLUME volume)

/**
 * 카드 덱을 파괴하는 함수입니다.
 * @param cardDeck 카드 덱
*/
void destroyCardDeck(CardDeck cardDeck);

/**
 * 카드 덱을 섞는 함수입니다.
 * @param cardDeck 카드 덱
 * @param card_num 카드 갯수
*/
void shuffleCardDeck(CardDeck cardDeck, int card_num);

/**
 * 카드 덱을 섞는 함수입니다.
 * @param des 저장할 카드 덱
 * @param src 대상 카드 덱
 * @param index 카드 덱의 시작 인덱스
 * @param max_index 카드 덱의 마지막 인덱스
 * @param cardNum 카드 갯수
 * @return 성공 시 마지막 인덱스, 실패 시 < 0
*/
int splitCardDeck(CardDeck des, CardDeck src, int index, int max_index, int card_num);

/**
 * 카드 덱으로부터 카드를 뽑는 함수입니다.
 * @param cardDeck 카드 덱
 * @return 뽑은 카드
*/
Card* drawCard(CardDeck cardDeck);

/**
 * 카드를 덱에 넣는 함수입니다.
 * @param card 카드
 * @param cardDeck 카드 덱
*/
void putCardToDeck(Card card, CardDeck cardDeck);

/**
 * 카드 덱을 카드 덱에 넣는 함수입니다.
 * @param src 대상 카드 덱
 * @param des 저장할 카드 덱
*/
void putCardDeckToDeck(CardDeck src, CardDeck des);




#endif