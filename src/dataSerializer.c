#include "dataSerializer.h"

int deserializePlayerAction(char *data) {
    int action;
    json_object *jobj = json_tokener_parse(data);
    

    json_object_object_get_ex(jobj, "player_id", &player_action);
    json_object_object_get_ex(jobj, "player_action", &player_action);

    int action = json_object_get_int(player_id);

    return action;
}

char* serializeSendData(Game* game, Player* player) {
    json_object *jobj = json_object_new_object();
    json_object *jarray = json_object_new_array();


    for(int i=0; i<game->join_num; i++) {
        json_object *jobj = json_object_new_object();
        json_object_object_add(jobj, "player_id", json_object_new_int(game->players[i]->id));
        json_object_object_add(jobj, "cardDeckOnTable_volume", json_object_new_int(game->players[i]->cardDeckOnTable->cards[0]->volume));
        json_object_object_add(jobj, "cardDeckOnTable_type", json_object_new_int(game->players[i]->cardDeckOnTable->cards[0]->type));
        json_object_object_add(jobj, "cardDeck_volume", json_object_new_int(game->players[i]->cardDeck->cards[0]->volume));
         json_object_object_add(jobj, "cardDeck_volume", json_object_new_int(game->players[i]->cardDeck->cards[0]->type));
        json_object_array_add(jarray, jobj);
    }

    return json_object_to_json_string(jobj);
}