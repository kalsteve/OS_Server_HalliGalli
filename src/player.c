

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

Player* addPlayer(Player* players, Player* player, int current_num) {
    Player* new_players = realloc(players, sizeof(Player) * (current_num + 1));
    if(new_players == NULL) {
        perror("realloc error in addPlayer");
        exit(EXIT_FAILURE);
    }
    new_players[current_num] = *player;
    return new_players;
}

void destroyPlayer(Player* player) {
    destroyCardDeck(player->cardDeck);
    destroyCardDeck(player->cardDeckOnTable);
}