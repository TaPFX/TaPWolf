#ifndef _TAPWOLFSERVER_H_
#define _TAPWOLFSERVER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "UDPServer.h"
#include "ledString.h"

#define DEFAULTPORT 6666
#define LEDANZ 36

int debug;
char* Mode;


pthread_mutex_t mutexRun,mutexStarRun;
int WolfRun;
int StarRun;

int parseCommand(char command[BUFSIZE]);

#endif
