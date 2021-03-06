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
#include <dirent.h>
#define PORTNO 16500

void getContentDir(){
	char *fname;
	DIR *d;
	FILE *f;
	int i=1;
	int k,n;
	struct dirent *dir;
	d = opendir(".");
	if(d){
		while((dir=readdir(d))!=NULL){
			printf("%d.%s\n",i,dir->d_name);
			i++;
		}
	}
	closedir(d);
}

int main()
{
	int len, result, sockfd, n = 1;
	struct sockaddr_in address;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("10.87.2.75");
	address.sin_port = htons(PORTNO);
	len = sizeof(address);
	printf("Choose an option\n1. Compile file\n2. Exit\n");
	int opt;

	scanf("%d", &opt);
	switch(opt){
		case 1:
			{
				char fileName[20];
				char fName[20];
				printf("Choose file to Compile\n");
				getContentDir();
				printf("Provide a file name\n");
				scanf("%s",fName);
				printf("File Name:%s\n",fName);
				strcpy(fileName, fName);
				result = connect(sockfd,(struct sockaddr *)&address,len);
				
				if (result==-1){
					perror("\nClient Error\n");
					exit(1);
				}
				n = write(sockfd, fileName, sizeof(fileName));
				uploadClientFile(sockfd, fileName);
				printf("Uploaded file.\n");
				char *statusFileName = strtok(fileName, ".");
				strcat(statusFileName, ".txt");
				int status = downloadStatusFile(sockfd, statusFileName);
				printf("Got status file.\n");
				n = write(sockfd, "ACK", sizeof("ACK"));
				if(n){
					char *execFileName = strtok(fileName, ".");
					strcat(execFileName, ".out");
					//printf("Inside downloadExecFile\n");
					downloadExecFile(sockfd, execFileName);
					char executable[100];
					sprintf(executable, "./%s",execFileName);
					system(executable);
				}
				else{
					int fd = open(statusFileName, O_RDONLY);
					char buf[5000];
					write(2, buf, sizeof(buf));
				}
				
				break;
			}
		case 2: 
			{
				printf("Disconeecting from server...\n");
				exit(1);
				break;
			}
	}
	return 0;
}