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
// Use this function to upload the source code on the client side
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
//Use this function to upload file on the server side
void uploadFile(int sockfd,char *fileName[2]){
	int filePointer,bytesRdWr;
	char msg[10];
	char msg1[] = {"NO ERROR."};
	char msg2[] = {"INVALID FILETYPE."};
	void *buf1 = (void *)calloc(BUFFER_SIZE,sizeof(void));
	void *buf2 = (char *)calloc(BUFFER_SIZE,sizeof(char));
	filePointer = open(fileName[1],O_RDWR);
	bytesRdWr = read(filePointer,buf2,BUFFER_SIZE);	
	if(bytesRdWr == -1){
		printf("Error occurred while reading compilation output file\n");
		return;
	}
	bytesRdWr = write(sockfd,buf2,bytesRdWr);
	if(bytesRdWr == -1){
		printf("Error occurred while sending the compilation output\n");
		return;
	}
	//Ack msg from the client side.
	read(sockfd,msg,sizeof(msg));
	if(strcmp(msg1,buf2) && strcmp(msg2,buf2)){
		buf1 = (void *)calloc(BUFFER_SIZE,sizeof(void));
		filePointer = open(fileName[2],O_RDWR);
		bytesRdWr = read(filePointer,buf1,BUFFER_SIZE);	
		if(bytesRdWr == -1){
			printf("Error occurred while reading  output file\n");
			return;
		}
		bytesRdWr = write(sockfd,buf1,bytesRdWr);
		if(bytesRdWr == -1){
			printf("Error occurred while uploading output file\n");
			return;
		}
		free(buf1);
	}
	free(buf2);
}