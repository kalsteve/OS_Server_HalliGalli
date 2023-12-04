/**
 * @file player.c
*/
#include "player.h"


Player* initPlayer() {
    Player* player = (Player*)malloc(sizeof(Player));
    player->id = 0;
    player->cardNum = 0;
    player->info = PLAYER_INIT;
    player->cardDeck = initCardDeck();
    player->cardDeckOnTable = initCardDeck();
    return player;
}

Player* createPlayer(int id) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->id = id;
    player->cardNum = 0;
    player->info = PLAYER_INIT;
    player->cardDeck = initCardDeck();
    player->cardDeckOnTable = initCardDeck();
    return player;
}

Player* addPlayer(Player* players, Player* player) {
    players = (Player*)realloc(players, sizeof(Player) * (player->id + 1));
    players[player->id] = *player;
    return players;
}

void destroyPlayer(Player* player) {
    destroyCardDeck(player->cardDeck);
    destroyCardDeck(player->cardDeckOnTable);
    free(player);
}