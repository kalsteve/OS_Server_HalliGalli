/**
 * 카드 관련 함수
*/
#include "card.h"


CardDeck initCardDeck() {
    int card_num = 0;
    Card *cardDeck;
    cardDeck = (Card *)malloc(sizeof(Card) * MAX_CARD_NUM);

    // 카드 덱 초기화
    for(int volume = 0; volume < MAX_CARD_VOLUME; volume++) {
        for(int repeat = 0; repeat < CARD_VOLUMES[volume]; repeat++) {
            for(int type = 0; type < MAX_CARD_TYPE; type++) {
                cardDeck[card_num] = createCard(type, volume);
                card_num++;
            }
        }
    }

    // 카드 덱 섞기
    shuffleCardDeck(cardDeck, card_num);
    
    return cardDeck;
}

Card createCard(CARD_TYPE type, CARD_VOLUME volume) {
    Card card;
    card.type = type;
    card.volume = volume;
    return card;
}

void destroyCardDeck(CardDeck cardDeck) {
    free(cardDeck);
}

void shuffleCardDeck(CardDeck cardDeck, int card_num) {
    srand(time(NULL));

    for(int i = 0; i < card_num; i++) {
        int rand_num = rand() % card_num;
        Card temp = cardDeck[i];
        cardDeck[i] = cardDeck[rand_num];
        cardDeck[rand_num] = temp;
    }
}

int splitCardDeck(CardDeck des, CardDeck src, int index, int max_index, int card_num) {
    int end_index = index + card_num;
    des = (CardDeck)malloc(sizeof(Card) * card_num);

    if(des == NULL || src == NULL) {
        return -1;  // 메모리 할당 실패
    }

    if(index < 0 || end_index > max_index) {
        free(des);
        return -2;  // 인덱스 범위 초과
    }

    for(int i = 0; i < card_num; i++) {
        des[i] = src[index + i];
    }

    return end_index; // 다음 카드 덱의 시작 인덱스 반환
}