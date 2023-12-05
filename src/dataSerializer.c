
#include "dataSerializer.h"

int deserializePlayerAction(char *data) {
    json_object *action;
    json_object *jobj = json_tokener_parse(data);


    action = json_object_object_get(jobj, "player_action");

    return json_object_get_int(action);
}

char* serializeSendData(Game* game, Player* player, int size) {
    char* data = (char*)malloc(sizeof(char) * size);
    json_object *jarray = json_object_new_array();

    for (int i = 0; i < game->join_num; i++) {
        json_object *jplayer = json_object_new_object();
        json_object_object_add(jplayer, "player_id", json_object_new_int(game->players[i].id));
        json_object_object_add(jplayer, "cardDeckOnTable_volume", json_object_new_int(game->players[i].cardDeckOnTable->cards[0].volume));
        json_object_object_add(jplayer, "cardDeckOnTable_type", json_object_new_int(game->players[i].cardDeckOnTable->cards[0].type));
        json_object_object_add(jplayer, "cardDeck_volume", json_object_new_int(game->players[i].cardDeck->cards[0].volume));
        json_object_object_add(jplayer, "cardDeck_type", json_object_new_int(game->players[i].cardDeck->cards[0].type));
        json_object_array_add(jarray, jplayer);
    }

    
    strcat(data, json_object_to_json_string(jarray)); // 문자열 복사

    json_object_put(jarray); // JSON 객체 메모리 해제

    return data;
}

char* serializeSendAction(int player_id, int player_action, int size) {
    char* data = (char*)malloc(sizeof(char) * size);
    json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "player_id", json_object_new_int(player_id));
    json_object_object_add(jobj, "player_action", json_object_new_int(player_action));

    strcat(data, json_object_to_json_string(jobj)); // 문자열 복사

    return data;
}