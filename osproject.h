#ifndef OS_Project
#define OS_Project

#include <semaphore.h>

char **compileCode(char *fileName);
void downloadFile(int sockfd,char *fileName);
void uploadClientFile(int sockfd,char *fileName);
void uploadFile(int sockfd,char *fileName[2]);
void writeLogs(char fileName[], sem_t *write);
int downloadStatusFile(int sockfd,char *fileName);
void downloadExecFile(int sockfd, char *fileName);

#endif
