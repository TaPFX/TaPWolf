#include "TaPWolfServer.h"
#define DEFAULTPORT 6666
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t mutexRun;
int run;

void *myThread(){
	while(1){
		
//	printf("Kind run:%d\n");
		pthread_mutex_lock(&mutexRun);
		printf("run:%d\n",run);
		if(run){
//		setLED(1,0xFFFFFF);
//		usleep(200000);
//		setLED(1,0);
			usleep(200000);
			printf("Kind: toggel\n");
		}
		pthread_mutex_unlock(&mutexRun);
			
		usleep(10000);
	}
	return;
}

int main(int argc, char*argv[]){
	int i,rc;
	char recvmsg[BUFSIZE];
	int port = DEFAULTPORT;	
	int endexit = 1;
	pthread_t thread1;

	if(initUDPServer(port) != 0){
		printf("ERROR whil init UDP-Server\n");
		return -1;
	}	
	initLEDs(10);
	
	pthread_mutex_init(&mutexRun, NULL);
	
	bzero(recvmsg, BUFSIZE);
	printf("wait for Connection\n");
	waitForClient(recvmsg);
	
	rc = pthread_create( &thread1, NULL, &myThread, NULL );
	if( rc != 0 ) {
		printf("Konnte Thread 1 nicht erzeugen\n");
		return -1;
  }

	while(!(strcmp(recvmsg,"TaPMagnet;endexit") == 0)){
		bzero(recvmsg, BUFSIZE);
		printf("wait for Connection\n");
		waitForClient(recvmsg);
		pthread_mutex_lock(&mutexRun);
		if(run == 1)
			run = 0;
		else
			run = 1;
		
		printf("eltern run:%d\n",run);
		
		pthread_mutex_unlock(&mutexRun);
	}
	
	endexit = 0;
	
	pthread_join( thread1, NULL );
	return 0;
}
