#include "player.h"

Player* initPlayer(int id, int card_num) {
    Player* player = createPlayer(id, card_num);
    return player;
}

Player* createPlayer(int id, int card_num) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->id = id;
    player->cardNum = 0;
    player->info = PLAYER_INIT;
    player->cardDeck = initCardDeck(MAX_CARD_NUM);
    player->cardDeckOnTable = initCardDeck(MAX_CARD_NUM);
    return player;
}

Player* setPlayerId(Player* player, int id) {
    player->id = id;
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