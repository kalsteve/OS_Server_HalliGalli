

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
    player->cardDeck = createCardDeck(card_num);
    player->cardDeckOnTable = createCardDeck(card_num);
    player->cardDeckOnTable->card_num = 0;
    player->cardDeck->card_num = 0;
    player->info = 0;
    return player;
}

Player* setPlayerId(Player* player, int id) {
    player->id = id;
    return player;
}

Player* addPlayer(Player* players, Player* player) {
    static int player_num = 1;
    players = (Player*)realloc(players, sizeof(Player) * player_num);
    players[player_num - 1] = *player;
    free(player);
    player_num++;
    return players;
}

void destroyPlayer(Player* player) {
    destroyCardDeck(player->cardDeck);
    destroyCardDeck(player->cardDeckOnTable);
    free(player);
}