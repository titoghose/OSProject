#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "osproject.h"
#define PORTNO 19500
int main()
{
	/*set up connection to the server*/	
	int len,result,sockfd,n=1;
	struct sockaddr_in address;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("10.92.2.50");
	address.sin_port=htons(PORTNO);
	len=sizeof(address);
				
	char fileName[20];
	strcpy(fileName,"test.c");
	
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if (result==-1)
	{
		perror("\nClient Error: ");
		exit(1);
	}
	
	n=write(sockfd,fileName,sizeof(fileName));
	uploadClientFile(sockfd,fileName);
	printf("File uploaded.\n");
	char *statusFileName=strtok(fileName,".");
	statusFileName=strcat(statusFileName,".txt");
	int status = downloadStatusFile(sockfd, statusFileName);
	printf("Status file received.\n");
	n = write(sockfd, "ACK", sizeof("ACK"));
	
	if(n)
	{
		char *execFileName = strtok(fileName, ".");
		strcat(execFileName, ".out");
		downloadExecFile(sockfd, execFileName);
		printf("Executable file received\n");
		char executable[100];
		sprintf(executable, "./%s",execFileName);
		system(executable);
	}
	else
	{
		printf("Error in compiling file\n");					
		int fd = open(statusFileName, O_RDONLY);
		char buf[5000];
		write(2, buf, sizeof(buf));
		printf("%s",buf);
	}
}