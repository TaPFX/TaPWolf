#include "TaPWolfServer.h"

//WolfON -> WolfRun=1; Wölfe blinzeln
//WolfOFF -> WolfRun=0; Wölfe aus

void *wolfThread(){
	int color[3] = {0xFF0000,0x00FF00,0x0000FF};
	
	while(1){	
		printf("WolfRun\n");
		usleep(200000);
		int setLEDS(colors[rand()%3]);
		pthread_mutex_lock(&mutexRun);
		if(!WolfRun)
			break;
		pthread_mutex_unlock(&mutexRun);
		
		usleep(1000);
	}
	int setLEDsOFF();
	return;
}

void *starThread(){
	int color[3] = {0xFF0000,0x00FF00,0x0000FF};
	
	while(1){	
		printf("WolfRun\n");
		usleep(100000);
		int setLEDS(colors[rand()%3]);
		pthread_mutex_lock(&mutexRun);
		if(!WolfRun)
			break;
		pthread_mutex_unlock(&mutexRun);
		
		usleep(1000);
	}
	int setLEDsOFF();
	return;
}

int main(int argc, char*argv[]){
	int i,rc;
	int opt;
	char recvmsg[BUFSIZE];
	int port = DEFAULTPORT;	
	int endexit = 1;
	
	pthread_t thread1;
	pthread_mutex_init(&mutexRun, NULL);
	WolfRun = 0;
	

	while ((opt = getopt(argc, argv, "p:dh")) != -1) {
		switch (opt) {
		case 'p':
			if(optarg != NULL)
				port = atoi(optarg);
			break;
		case 'd':
			debug = 1;
			break;		
		case 'h':
			printf("Help for TaPWolfServer\n");
			printf("Usage: %s [-p port number] [-d] debug mode [-h] show Help\n", argv[0]);
			return 0;
			break;
		default: /* '?' */
			printf("Usage: %s [-p portnumber] [-d] debug mode [-i] invert pwm output [-h] show Help\n", argv[0]);
			return -2;
		}
	}
	
	if(initUDPServer(port) != 0){
		printf("ERROR whil init UDP-Server\n");
		return -1;
	}	
	
	
	bzero(recvmsg, BUFSIZE);
	printf("wait for Connection\n");
	waitForClient(recvmsg);
	
	if(parseCommand(recvmsg) != 0){
		printf("ERROR wrong Syntax\n");
		continue;
	}
	
	rc = pthread_create( &thread1, NULL, &wolfThread, NULL );
	if( rc != 0 ) {
		printf("Konnte Thread 1 nicht erzeugen\n");
		return -1;
	}

	while(!(strcmp(recvmsg,"TaPWolf;exit") == 0)){
		bzero(recvmsg, BUFSIZE);
		printf("wait for Connection\n");
		waitForClient(recvmsg);
		
		if(strcmp(Mode, "WolfON") == 0){
			rc = pthread_create( &thread1, NULL, &wolfThread, NULL );
			if( rc != 0 ) {
				printf("Konnte Thread 1 nicht erzeugen\n");
				return -1;
			}
		}
			
		if(strcmp(Mode, "WolfOFF") == 0){
			pthread_mutex_lock(&mutexRun);
			WolfRun = 0;
			pthread_mutex_unlock(&mutexRun);}
			
		if(strcmp(Mode, "StarON") == 0){
			rc = pthread_create( &thread1, NULL, &starThread, NULL );
			if( rc != 0 ) {
				printf("Konnte Thread 1 nicht erzeugen\n");
				return -1;
			}
		}
			
		if(strcmp(Mode, "StarOFF") == 0){
			pthread_mutex_lock(&mutexRun);
			StarRun = 0;
			pthread_mutex_unlock(&mutexRun);}
			
	}
	
	endexit = 0;
	
	pthread_join( thread1, NULL );
	return 0;
}

int parseCommand(char command[BUFSIZE]){
	int i;
	char copycommand[BUFSIZE];
	char *splitCommand;

	for(i=0;i<BUFSIZE;i++)
		copycommand[i] = command[i];
	
	splitCommand=strtok(copycommand,";");
	if(strcmp(splitCommand, "TaPWolf") != 0)
		return -1;
	
	
	splitCommand=strtok(NULL,";");
	if(strcmp(splitCommand, "ON") == 0 || strcmp(splitCommand, "OFF") == 0)
		Mode = splitCommand;
	else
		return -1;
	
	return 0;
}

