#include "TaPWolfServer.h"
#define DEFAULTPORT 6666


int main(int argc, char*argv[]){
	int i,j;
	char recvmsg[BUFSIZE];
	int port = DEFAULTPORT;	
	int run = 1;
	int exit = 1;
	pid_t pid;
	int pipefd[2];
	char buf;

	if(initUDPServer(port) != 0){
		printf("ERROR whil init UDP-Server\n");
		return -1;
	}	
	initLEDs(10);
		
		bzero(recvmsg, BUFSIZE);
		printf("wait for Connection\n");
		waitForClient(recvmsg);
		
		pipe(pipefd);
		buf=0;
		write(pipefd[0],&buf,1);

		pid = fork();
		if (pid == 0)
   {	//KindProzess
      printf ("Kindprozess: (PID: %d)\n", getpid());
			while(exit){
				read(pipefd[0],&buf,1);
				printf("buf:%d\n",buf);
	
				if( buf == 1){
					setLED(1,0xFFFFFF);
					usleep(200000);
					setLED(1,0);
					usleep(200000);
				
					printf("Kind: toggel\n");
					
					write(pipefd[1],&buf,1);
				}
				
				usleep(100);
			}
			
			
			return(0);
   }
   else if (pid > 0)
   {
      // Elternprozess
			printf ("Elternprozess: (PID: %d)\n", getpid());
			printf("Eltern: run=%d\n",run);
	 }
   else
   {
      /* Wird ein negativer Wert zurückgegeben, ist ein Fehler aufgetreten */
      fprintf (stderr, "Fehler");
      return(-1);
   }

	while(!(strcmp(recvmsg,"TaPMagnet;exit") == 0)){
		bzero(recvmsg, BUFSIZE);
		printf("wait for Connection\n");
		waitForClient(recvmsg);
		
		printf ("Elternprozess:(PID: %d)\n",  getpid());
		
		if(buf == 0)
			buf=1;
		else
			buf =0;
		printf("buf:%d\n",buf);
		write(pipefd[1],&buf,1);
	}
	exit = 0;

	return 0;
}
