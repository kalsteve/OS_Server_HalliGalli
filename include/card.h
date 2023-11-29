#ifndef __CARD_H__
#define __CARD_H__

/**
 * 카드 덱을 구성하는 카드의 종류와 개수를 정의한 헤더 파일입니다.
 * @file card.h
 * @brief This file contains the declaration of the card struct and its functions.
*/

#define MAX_CARD_NUM 56

typedef enum _CARD_TYPE {
    NULL,
    STRAWBERRY,
    BANANA,
    LIME,
    PRUNE
} CARD_TYPE;

typedef enum _CARD_VOLUME {
    NULL,
    ONE_FRUIT = 5,
    TWO_FRUIT = 3,
    THREE_FRUIT = 3,
    FOUR_FRUIT = 2,
    FIVE_FRUIT = 1,
} CARD_VOLUME;

typedef struct _Card{
    int id;
    CARD_TYPE type;
    CARD_VOLUME volume;
} Card;

typedef Card* CardDeck;

CardDeck initCardDeck();
Card createCard(CARD_TYPE type, CARD_VOLUME volume);
void destroyCard(Card card[]);
void destroyCardDeck(Card card[]);
CardDeck shuffleCardDeck(CardDeck cardDeck);
CardDeck splitCardDeck(CardDeck cardDeck, int num);


#endif