/**
 * 카드 관련 함수
*/
#include "card.h"


CardDeck* initCardDeck(int card_num) {
    int card_id = 0;
    CardDeck *cardDeck;

    // 카드 덱 생성
    cardDeck = createCardDeck(card_num);

    // 카드 초기 설정 알고리즘
    for(int volume = 0; volume < MAX_CARD_VOLUME; volume++) {          // 카드의 과일 갯수
        for(int repeat = 0; repeat < CARD_VOLUMES[volume]; repeat++) { // 카드의 과일 개수만큼 반복
            for(int type = 0; type < MAX_CARD_TYPE; type++) {           // 카드의 종류
                setCard(&cardDeck->cards[card_num], card_id, type, volume);
                card_id++;
            }
        }
    }

    // 카드 덱 섞기
    shuffleCardDeck(cardDeck, card_num);
    
    return cardDeck;
}

CardDeck* createCardDeck(int card_num) {
    // 카드, 덱 공간 할당
    CardDeck *cardDeck = (CardDeck *)malloc(sizeof(CardDeck));
    Card *new_cards = (Card *)malloc(sizeof(Card) * card_num);
    
    
    // 카드 덱 생성
    cardDeck->card_num = card_num;
    cardDeck->cards = new_cards;
    
    return cardDeck;
}

void setCard(Card* card, int id,  CARD_TYPE type, CARD_VOLUME volume) {
    card->id = id;
    card->type = type;
    card->volume = volume;
}

void destroyCardDeck(CardDeck* cardDeck) {
    free(cardDeck->cards);
    free(cardDeck);
}

void shuffleCardDeck(CardDeck* cardDeck, int card_num) {
    srand(time(NULL));

    for(int i = 0; i < card_num; i++) {
        int rand_num = rand() % card_num;
        Card temp = cardDeck->cards[i];
        cardDeck->cards[i] = cardDeck->cards[rand_num];
        cardDeck->cards[rand_num] = temp;
    }
}

int splitCardDeck(CardDeck* des, CardDeck* src, int index, int card_num) {
    int end_index = index + card_num;
    CardDeck *new_des = createCardDeck(des->card_num + card_num);

    if(des == NULL || src == NULL) {
        return -1;  // 메모리 할당 실패
    }

    if(index < 0 || end_index > src->card_num) {
        free(des);
        return -2;  // 인덱스 범위 초과
    }

    // 카드 덱 복사
    for(int i = 0; i < des->card_num; i++) {
        new_des->cards[i] = des->cards[i];
    }

    for(int i = 0; i < card_num; i++) {
        new_des->cards[des->card_num + i] = src->cards[index + i];
    }
    
    // 카드 덱 교체
    des = new_des;
    free(des);
    
    return end_index; // 다음 카드 덱의 시작 인덱스 반환
}

// 카드 덱에서 카드를 뽑는 함수
Card drawCard(CardDeck* cardDeck) {
    Card card = cardDeck->cards[cardDeck->card_num - 1];
    cardDeck->card_num--;
    return card;
}