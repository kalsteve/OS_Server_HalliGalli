/**
 * 카드 관련 함수
*/


#include "card.h"

//카드 종류별 갯수의 배열
const int CARD_VOLUMES[] = {
    ONE_FRUIT, 
    TWO_FRUIT, 
    THREE_FRUIT, 
    FOUR_FRUIT, 
    FIVE_FRUIT
};

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
    int des_index = des->card_num;
    int des_end_index = des_index + card_num;
    int des_card_num = des->card_num + card_num;
    Card tempDeck[MAX_CARD_NUM];
    
    if(des == NULL || src == NULL) {
        return -1;  // 메모리 할당 실패
    }

    if(index < 0 || end_index > src->card_num) {
        free(des);
        return -2;  // 인덱스 범위 초과
    }

    // 카드 덱 복사
    for(int i = 0; i < des->card_num; i++) {
        tempDeck[i] = des->cards[i];
    }

    // 카드 덱 붙이기
    for(int i = index; i < end_index; i++) {
        tempDeck[i+des_index] = src->cards[i];
    }

    // 카드 덱 복사
    for(int i = 0; i < des_end_index; i++) {
        des->cards[i] = tempDeck[i];
    }

    des->card_num = des_card_num;
    
    return end_index; // 다음 카드 덱의 시작 인덱스 반환
}

// 카드 덱에서 카드를 뽑는 함수
Card drawCard(CardDeck* cardDeck) {
    Card card = cardDeck->cards[cardDeck->card_num - 1];
    cardDeck->cards[cardDeck->card_num - 1];
    cardDeck->card_num--;
    return card;
}

// 카드 덱에 카드를 넣는 함수
void putCardToDeck(CardDeck* cardDeck, Card card) {
    Card temp[MAX_CARD_NUM];
    int card_num = cardDeck->card_num + 1;

    temp[0] = card;

    // 카드 덱 복사
    for(int i = 0; i < cardDeck->card_num; i++) {
        temp[i+1] = cardDeck->cards[i];
    }

    for(int i = 0; i < card_num; i++) {
        cardDeck->cards[i] = temp[i];
    }

    cardDeck->card_num = card_num;
}

// 카드 덱을 카드 덱에 붙이는 함수
void putCardDeckToDeck(CardDeck* des, CardDeck* src) {
    int total = des->card_num + src->card_num;
    Card temp[MAX_CARD_NUM];

    // 카드 덱 복사
    for(int i = 0; i < des->card_num; i++) {
        temp[i] = des->cards[i];
    }

    // 카드 덱 붙이기
    for(int i = 0; i < src->card_num; i++) {
        temp[i+des->card_num] = src->cards[i];
    }

    // 카드 덱 복사
    for(int i = 0; i < total; i++) {
        des->cards[i] = temp[i];
    }

    des->card_num = total;
}


