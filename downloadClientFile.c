#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 5000
/*
	Used to download status/error file returned from server. 
	Input:
		1. socket file descriptor to read from
		2. fileName of the status/error file

	Returns:
		0 - executable file doesn't exist(error occurred)
		1 - executable file exists
*/
int downloadStatusFile(int sockfd,char *fileName){
	int filePointer, bytesRdWr, executable = 0;
	char *buf = (char *)calloc(BUFFER_SIZE,sizeof(char));
	
	filePointer = open(fileName,O_RDWR);
	bytesRdWr = read(sockfd,buf,BUFFER_SIZE);
	
	if(bytesRdWr == -1)
		perror("Error occurred while downloading file\n");
	
	bytesRdWr = write(filePointer,buf,strlen(buf));
	
	if(bytesRdWr == -1)
		perror("Error occurred while writing to the file\n");
	
	if(strcmp(buf, "NO ERROR.") == 0)
		executable = 1;
	
	free(buf);

	return executable;
}

void downloadExecFile(int sockfd, char *fileName){
	int fileFD, n = 1;
	void *buf = (void*) malloc(sizeof(void) * BUFFER_SIZE);

	fileFD = open(fileName, O_RDWR);
	n = read(sockfd, buf, sizeof(buf));
	if(n == -1)
		perror("Error occurred while reading executable file\n");
	n = write(fileFD, buf, sizeof(buf));
	if(n == -1)
		perror("Error occurred while writing executable file\n");
}