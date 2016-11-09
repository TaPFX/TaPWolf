#include "UDPServer.h"


signed char initUDPServer(int port){
	serverCrated = 0;
	
	portno = port;
	
	//socket: create the parent socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0){
		printf("ERROR opening socket\n");
		return -1;}
	
	/* setsockopt: Handy debugging trick that lets 
	 * us rerun the server immediately after we kill it; 
	 * otherwise we have to wait about 20 secs. 
	 * Eliminates "ERROR on binding: Address already in use" error. 
	 */
	optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(int));
	
	//build the server's Internet address
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)portno);
	
	//bind: associate the parent socket with a port 
	if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) 
		printf("ERROR on binding\n");
	
	clientlen = sizeof(clientaddr);
	serverCrated = 1;
	return 0;
}

signed char waitForClient(char recvmsg[BUFSIZE]){
	int i;

	if(serverCrated == 0){
		printf("ERROR: execute initUDPServer first\n");
		return -1;}
		
		
	bzero(buf, BUFSIZE);
    n = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *) &clientaddr, &clientlen);
    if (n < 0)
      printf("ERROR in recvfrom");
	

	//gethostbyaddr: determine who sent the datagram
/*	hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if(hostp == NULL){
		printf("ERROR on gethostbyaddr\n");
		return -1;}
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if(hostaddrp == NULL){
		printf("ERROR on inet_ntoa\n");
		return -1;}
    printf("server received datagram from %s (%s)\n", hostp->h_name, hostaddrp);
*/
	if(serverCrated == 0){
		printf("ERROR: execute initUDPServer first\n");
		return -1;}
		

/*	//gethostbyaddr: determine who sent the datagram
	hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL){
		printf("ERROR on gethostbyaddr\n");
		return -1;}
  
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL){
		printf("ERROR on inet_ntoa\n");
		return -1;}
*/		
	for(i=0;i<BUFSIZE;i++)
		recvmsg[i]=buf[i];
		
	return 0;
}


signed char sendBack(){
	if(serverCrated == 0){
		printf("ERROR: execute initUDPServer first\n");
		return -1;}
	
	n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &clientaddr, clientlen);
    if (n < 0) {
		printf("ERROR in sendto\n");
		return -1;}
	
}

