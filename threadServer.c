#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<pthread.h>
#include "osproject.h"
#define PORTNO 19500
typedef struct mystruct{
	int clientSockFd;
	sem_t *write;
}THREAD_PARAM;

THREAD_PARAM *initNode(int clientSockFd,sem_t *write){
	THREAD_PARAM *temp = (THREAD_PARAM *)malloc(sizeof(THREAD_PARAM));
	temp->clientSockFd = clientSockFd;
	temp->write = write;
	return temp;
}

void *thread_compile(void *param){
	int n,filePointer;
	char fileName[500];
	THREAD_PARAM *para = (THREAD_PARAM *)param;
	n = read(para->clientSockFd,fileName,sizeof(fileName));
	downloadFile(para->clientSockFd,fileName);
	char **compiledFileNames = compileCode(fileName);
	uploadFile(para->clientSockFd,compiledFileNames);
	close(para->clientSockFd);
	writeLogs(fileName, para->write);
}

int main(){
	int serverSockFd, clientSockFd, n = 1;
	THREAD_PARAM *param = NULL;
	sem_t *write = sem_open("writing",O_CREAT,0644,1);
	struct sockaddr_in serverAddr, clientAddr;
	serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_port = htons(PORTNO);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("10.92.2.50");
	n = bind(serverSockFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	n = listen(serverSockFd,5);
	pthread_t thread;
	while(1){
		int len = sizeof(clientAddr);
		clientSockFd = accept(serverSockFd, (struct sockaddr*)&clientAddr, (socklen_t*)&len);
		param = initNode(clientSockFd,write);
		pthread_create(&thread,0,&thread_compile,(void *)param);
	}
	close(serverSockFd);
	return 0;
}
