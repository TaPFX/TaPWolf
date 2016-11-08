#ifndef _UDPSERVER_h_
#define _UDPSERVER_h_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>


#define BUFSIZE 1024


int sockfd; 		/* socket */
int portno; 		/* port to listen on */
int clientlen; 		/* byte size of client's address */
struct sockaddr_in serveraddr; /* server's addr */
struct sockaddr_in clientaddr; /* client addr */
struct hostent *hostp; 	/* client host info */
char buf[BUFSIZE]; 		/* message buf *a*/
char copybuf[BUFSIZE];
char *hostaddrp; 		/* dotted decimal host addr string */
int optval; 			/* flag value for setsockopt */
int n; 					/* message byte size */

int serverCrated;

signed char initUDPServer(int portno);

signed char waitForClient();

signed char sendBack();

#endif
