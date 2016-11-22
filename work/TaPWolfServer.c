#include "TaPWolfServer.h"

//WolfON -> WolfRun=1; Wölfe blinzeln
//WolfOFF -> WolfRun=0; Wölfe aus

void *wolfThread(){
	int i;
	int color[3] = {0xFF1F05,0xAF2A00,0xDF3800};
	int setcolor;
	int lednum = 0;
	int ledcolor = 0;
	int sleeptime = 1;
	int sleepmin = 2000000;
	int sleepmax = 3000000;
	
	for(i=0;i<(LEDANZ-1);i=i+2){
		setcolor = color[rand()%3];
		setLED(i,setcolor);
		setLED(i+1,setcolor);
		printf("led:%d,%d color:%d\n",i,i+1,setcolor);}
			
	
	while(1){	
		while(sleeptime < sleepmin)
			sleeptime = rand()%sleepmax;

		usleep(sleeptime);

		lednum=rand() % (LEDANZ-1);
		if(lednum%2 != 0)
			lednum++;
		
		ledcolor = getLEDcolor(lednum);
		setLED(lednum,0);
		setLED(lednum+1,0);
		printf("lednum:%d,%d\n",lednum,lednum+1);
		usleep(100000);
		setLED(lednum,ledcolor);
		setLED(lednum+1,ledcolor);
		pthread_mutex_lock(&mutexRun);
		if(!WolfRun) {
			pthread_mutex_unlock(&mutexRun);
			break;}
		pthread_mutex_unlock(&mutexRun);
		
		usleep(1000);
	}
	setLEDsOFF();
	return;
}

void *starThread(){
	int i;
	int color[3] = {0xFFFFA5,0xCFFAFF,0x9FFFFF};
	int setcolor;
	int lednum = 0;
	int ledcolor = 0;
	int sleeptime = 1;
	int sleepmin = 2000000;
	int sleepmax = 3000000;
	
	for(i=0;i<(LEDANZ-1);i=i+2){
		setcolor = color[rand()%3];
		setLED(i,setcolor);
		printf("led:%d,%d color:%d\n",i,i+1,setcolor);}
	
	setLED(22,0);
	setLED(8,0);
	while(1){
		pthread_mutex_lock(&mutexStarRun);
		if(!StarRun) {
			pthread_mutex_unlock(&mutexStarRun);
			break;}
		pthread_mutex_unlock(&mutexStarRun);
		
		usleep(500000);
	}
	setLEDsOFF();
	return;
}

int main(int argc, char*argv[]){
	int i,rc;
	int brt=50;
	int opt;
	char recvmsg[BUFSIZE];
	int port = DEFAULTPORT;	
	int endexit = 1;
	
	pthread_t wolfPThread,starPThread;
	pthread_mutex_init(&mutexRun, NULL);
	pthread_mutex_init(&mutexStarRun, NULL);
	WolfRun = 1;
	StarRun = 1;

	if(initLEDs(LEDANZ)){
		printf("ERROR: initLED\n");
		return -1;}
		
	while ((opt = getopt(argc, argv, "p:dhb:")) != -1) {
		switch (opt) {
		case 'p':
			if(optarg != NULL)
				port = atoi(optarg);
			break;
		case 'd':
			debug = 1;
			break;		
		case 'b':
			if(optarg != NULL)
				brt = atoi(optarg);
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
	
	if(setBrightness(brt)){
		printf("ERROR setBrightnes\n");
		return -1;}

	if(setLEDsOFF()){
		printf("ERROR setLEDsOFF\n");
		return -1;}


	if(initUDPServer(port) != 0){
		printf("ERROR whil init UDP-Server\n");
		return -1;
	}	
	
	while(!(strcmp(recvmsg,"TaPWolf;exit") == 0)){
		
		bzero(recvmsg, BUFSIZE);
		printf("wait for Connection\n");
		waitForClient(recvmsg);
		
		if(parseCommand(recvmsg) != 0){
			printf("ERROR wrong Syntax\n");
			continue;
		}

		if(strcmp(Mode, "WolfON") == 0){
			WolfRun = 1;
			rc = pthread_create( &wolfPThread, NULL, &wolfThread, NULL );
			if( rc != 0 ) {
				printf("Konnte WolfThread  nicht erzeugen\n");
				return -1;
			}
		}
			
		if(strcmp(Mode, "WolfOFF") == 0){
			pthread_mutex_lock(&mutexRun);
			WolfRun = 0;
			pthread_mutex_unlock(&mutexRun);}
			
		
		
		if(strcmp(Mode, "StarON") == 0){
			StarRun = 1;
			rc = pthread_create( &starPThread, NULL, &starThread, NULL );
			if( rc != 0 ) {
				printf("Konnte StarThread  nicht erzeugen\n");
				return -1;
			}
		}
			
		if(strcmp(Mode, "StarOFF") == 0){
			pthread_mutex_lock(&mutexRun);
			StarRun = 0;
			pthread_mutex_unlock(&mutexRun);}
			
	}

	endexit = 0;
	
	if(setLEDsOFF()){
		printf("ERROR setLEDsOFF\n");
		return -1;}

	pthread_join( wolfPThread, NULL );
	pthread_join( starPThread, NULL );

	ws2811_fini(&myledstring);
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
	if(strcmp(splitCommand, "WolfON") == 0 || strcmp(splitCommand, "WolfOFF") == 0 || strcmp(splitCommand, "StarON") == 0 || strcmp(splitCommand, "StarOFF") == 0 || strcmp(splitCommand, "exit") == 0)
		Mode = splitCommand;
	else
		return -1;
	
	return 0;
}

