

#include "player.h"

Player* initPlayer(int id, int card_num) {
    Player* player = createPlayer(id, card_num);
    return player;
}

Player* createPlayer(int id, int card_num) {
    Player* player = (Player*)malloc(sizeof(Player));
    if(player == NULL) {
        perror("in Player malloc error");
        exit(1);
    }
    player->id = id;
    player->cardNum = 0;
    player->info = 0;
    player->cardDeck = initCardDeck(MAX_CARD_NUM);
    player->cardDeckOnTable = initCardDeck(MAX_CARD_NUM);
    return player;
}

Player* setPlayerId(Player* player, int id) {
    player->id = id;
    return player;
}

Player* addPlayer(Player* players, Player* player) {
    players = (Player*)realloc(players, sizeof(Player) * 2);
    setPlayerId(&players[player->id], player->id);
    return players;
}

void destroyPlayer(Player* player) {
    destroyCardDeck(player->cardDeck);
    destroyCardDeck(player->cardDeckOnTable);
    free(player);
}