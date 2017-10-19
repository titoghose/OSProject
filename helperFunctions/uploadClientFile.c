#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 5000

/* Use this function to upload the source code on the client side */
void uploadClientFile(int sockfd,char *fileName){
	int filePointer,bytesRdWr;
	char *buf = (char *)calloc(BUFFER_SIZE,sizeof(char));
	filePointer = open(fileName,O_RDWR);
	bytesRdWr = read(filePointer,buf,BUFFER_SIZE);
	if(bytesRdWr == -1)
		printf("Error occurred while reading file\n");
	bytesRdWr = write(sockfd,buf,strlen(buf));
	if(bytesRdWr == -1)
		printf("Error occurred while uploading the file\n");
	free(buf);
}