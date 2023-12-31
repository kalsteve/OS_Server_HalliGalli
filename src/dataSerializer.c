
#include "dataSerializer.h"


int deserializePlayerAction(char *data) {
    int temp;
    json_object *action;
    json_tokener *tok = json_tokener_new();
    json_object *jobj = json_tokener_parse_ex(tok, data, 1024);

    action = json_object_object_get(jobj, "player_action");
    temp = json_object_get_int(action);

    

    return temp;
}



char* serializeSendData(Game* game, Player* player, int size) {
    char* data = (char*)calloc(size, sizeof(char));  // 메모리 할당 및 초기화
    memset(data, 0, size);  // 메모리 할당 및 초기화
    json_object *jobj = json_object_new_object();
    json_object *jarray = json_object_new_array();

    json_object_object_add(jobj, "player_turn", json_object_new_int(game->player_turn));

    for (int i = 0; i < game->join_num; i++) {
        json_object *jplayer = json_object_new_object();
        json_object_object_add(jplayer, "player_id", json_object_new_int(game->players[i].id));
        json_object_object_add(jplayer, "cardDeckOnTable_volume", json_object_new_int(game->players[i].cardDeckOnTable->cards[0].volume));
        json_object_object_add(jplayer, "cardDeckOnTable_type", json_object_new_int(game->players[i].cardDeckOnTable->cards[0].type));
        json_object_array_add(jarray, jplayer);
    }

    json_object_object_add(jobj, "all_players_data", jarray);

    strncpy(data, json_object_to_json_string(jobj), size); // 문자열 복사

    return data;
}



char* serializeSendAction(int player_id, int player_turn,int player_action, int size) {
    char* data = (char*)calloc(size, sizeof(char));
    memset(data, 0, size);  // 메모리 할당 및 초기화
    
    json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "player_id", json_object_new_int(player_id));
    json_object_object_add(jobj, "player_turn", json_object_new_int(player_turn));
    json_object_object_add(jobj, "player_action", json_object_new_int(player_action));

    strncpy(data, json_object_to_json_string(jobj), size); // 문자열 복사

    return data;
}