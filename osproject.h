#ifndef OS_Project
#define OS_Project

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 5000

char **compileCode(char *fileName);
void downloadFile(int sockfd,char *fileName);
void uploadClientFile(int sockfd,char *fileName);
void uploadFile(int sockfd,char *fileName[2]);

#endif