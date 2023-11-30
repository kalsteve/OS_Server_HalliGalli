/**
 * 카드 관련 함수
*/
#include "card.h"



CardDeck initCardDeck(const int card_num) {
    Card *cards
    cards = (Card *)malloc(sizeof(Card) * card_num);
    
    // 카드 생성
    // CARD_TYPE type = STRAWBERRY ~ PINEAPPLE
    for(CARD_TYPE type = CARD_TYPE.STRAWBERRY ; type <= ; type++) {
        // CARD_VOLUME volume = ONE ~ TWELVE
        for(CARD_VOLUME volume = ONE; volume <= TWELVE; volume++) {
            cards[(type - 1) * 12 + (volume - 1)] = createCard(type, volume);
        }
    }
    return cardDeck;
}

Card createCard(CARD_TYPE type, CARD_VOLUME volume);
void destroyCard(Card card[]);
void destroyCardDeck(Card card[]);
CardDeck shuffleCardDeck(CardDeck cardDeck);
CardDeck splitCardDeck(CardDeck cardDeck, int num);