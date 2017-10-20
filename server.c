#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "osproject.h"
#define PORTNO 19500
int main(){
	sem_t *write = sem_open("writing", O_CREAT, 0644, 1);
	int serverSockFd, clientSockFd, n = 1;
	struct sockaddr_in serverAddr, clientAddr;
	serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_port = htons(PORTNO);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("10.87.2.75");
	n = bind(serverSockFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	n = listen(serverSockFd, 5);
	while(1){
		int len = sizeof(clientAddr);
		clientSockFd = accept(serverSockFd, (struct sockaddr*)&clientAddr, (socklen_t*)&len);
		int clientPID = fork();
		if(clientPID == 0){
			 char fileName[500];
			 n = read(clientSockFd, fileName, sizeof(fileName));
			 printf("Received: %s\n", fileName);
			 downloadFile(clientSockFd, fileName);
			 printf("Downloaded: %s\n", fileName);
			 char **compiledFileNames = compileCode(fileName);
			 printf("Compiled: %s\n", fileName);
			 uploadFile(clientSockFd, compiledFileNames);
			 printf("Uploaded: %s\n", fileName);
			 close(clientSockFd);
			 writeLogs(fileName, write);
		}
	}
	close(serverSockFd);
	sem_close(write);
	return 0;
}
