#ifndef __PLAYER_H__
#define __PLAYER_H__

typedef struct _Player{
    int id;
    int cardNum;
    CardDeck cardDeck;
} Player;

typedef Player* PlayerData;

PlayerData initPlayer();
void destroyPlayer(PlayerData player);


#endif