#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <netinet/in.h> // for sockaddr_in

#include "card.h"
#include "player.h"
#include "game.h"
#include "dataSerializer.h"
#include "server.h"


void* wait_Player(void* socket);
void* getPlayerAction(void* socket);
void* playerJoinGame(void* player);
void* sendALLPlayerAction(void* player);
void* sendPlayerAction(void* player);
void* sendPlayerData(void* player);
void systemMessage(char* message);
#endif

