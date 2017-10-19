#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "osproject.h"

int main(){
	sem_t *write = sem_open("writing", O_CREAT, 0644, 1);
	int serverSockFd, clientSockFd, n = 1;
	struct sockaddr_in serverAddr, clientAddr;
	serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_port = htons(10000);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	n = bind(serverSockFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	n = listen(serverSockFd, 5);
	while(1){
		int len = sizeof(clientAddr);
		clientSockFd = accept(serverSockFd, (struct sockaddr*)&clientAddr, (socklen_t*)&len);
		int clientPID = fork();
		if(clientPID == 0){
			 char fileName[500];
			 n = read(clientSockFd, fileName, sizeof(fileName));
			 downloadFile(clientSockFd, fileName);
			 char **compiledFileNames = compileCode(fileName);
			 uploadFile(clientSockFd, compiledFileNames);
			 close(clientSockFd);
			 writeLogs(fileName, write);
		}
	}
	close(serverSockFd);
	sem_close(write);
	return 0;
}