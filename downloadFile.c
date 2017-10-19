#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 5000
/*
	This header file is used for downloading the client source code and providing it to the server
	and also sending the compilation output along with the binary executable file back to the client.
*/
void downloadFile(int sockfd,char *fileName){
	int filePointer,bytesRdWr;
	char *buf = (char *)calloc(BUFFER_SIZE,sizeof(char));
	filePointer = open(fileName,O_RDWR);
	bytesRdWr = read(sockfd,buf,BUFFER_SIZE);
	if(bytesRdWr == -1)
		printf("Error occurred while downloading file\n");
	bytesRdWr = write(filePointer,buf,strlen(buf));
	if(bytesRdWr == -1)
		printf("Error occurred while writing to the file\n");
	free(buf);
}