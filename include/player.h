#ifndef __PLAYER_H__
#define __PLAYER_H__

typedef struct _Player{
    int id;
    int cardNum;
    int info;
    CardDeck cardDeck;        // 플레이어가 가지고 있는 카드 덱
    CardDeck cardDeckOnTable; // 테이블에 내려놓은 카드 덱
} Player;

typedef Player* PlayersData;

PlayersData initPlayer();
PlayersData createPlayer(int id);
PlayersData addPlayersData(PlayersData players, Player player);
void destroyPlayer(PlayersData player);

#endif