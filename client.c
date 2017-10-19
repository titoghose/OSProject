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
#define PORTNO 10000
void getContentsDir(){
	char *fname;
	DIR *d;
	char msg[] = {"STOP"};
	FILE *f;
	int k,n;
	struct dirent *dir;
	d = opendir(".");
	if(d){
		while((dir=readdir(d))!=NULL){
			fname = (char *)calloc(100,sizeof(char));
			printf("%s\n",dir->d_name);
			strcpy(fname,dir->d_name);
			fname[strlen(fname)] = '\n';
			fname[strlen(fname)+1] = '\0';
			free(fname);
		}
	}
	closedir(d);
}
int main()
{
	int len,result,sockfd,n=1;
	struct sockaddr_in address;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.0");
	address.sin_port=htons(PORTNO);
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if (result==-1)
	{
		perror("\nClient Error\n");
		exit(1);
	}
	while(1)
	{
		printf("Choose an option\n1. Compile file\n2. Exit\n");
		int opt;
		scanf("%d",&opt);
		switch(opt)
		{
			case 1: printf("The files in the current directory are:\n");
					getContentsDir();
					printf("Enter the file to be compiled\n");
					char fileName[500];
					scanf("%s",fileName);
					n=write(sockfd,fileName,sizeof(fileName));
					uploadClientFile(sockfd,fileName);
					downloadFile(sockfd,fileName);
					char executable[2];
					executable[0]='.';
					executable[1]='/';
					char *executes=strcat(executable,fileName);
					char returnmsg[]={"Received file"};
					n=write(sockfd,returnmsg,sizof(returnmsg));
					char txt[500];
					n=read(sockfd,txt,sizeof(txt);
					printf("The compild file is available\nDo you want to execute?\n");
					int choice;
					scanf("%d",&choice);
					if (choice)
					{
						system(executes);
					}
					break;

			case 2: printf("Disconeecting from server...\n");
					exit(1);
					break;
		}
	}
}
