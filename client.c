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
	address.sin_addr.s_addr=inet_addr("192.168.43.78");
	address.sin_port=htons(PORTNO);
	len=sizeof(address);
	/*int flag_skipper=0;*/
	//while(1)
	//{
	printf("Choose an option\n1. Compile file\n2. Exit\n");
	int opt;
	scanf("%d",&opt);
	switch(opt)
	{
		case 1: /*Display the list of files available in the current working directory*/
				printf("The files in the current directory are:\n");
				getContentsDir();
				printf("Enter the file to be compiled\n");
				char fileName[500];
				scanf("%s",fileName);
				/*Establish connection with the server

				if (!flag_skipper)
				{
				*/				
				result=connect(sockfd,(struct sockaddr *)&address,len);
				if (result==-1)
				{
					perror("\nClient Error: ");
					exit(1);
				}
				//}
				//flag_skipper=1;
				/*Send filename and file to the server*/
				n=write(sockfd,fileName,sizeof(fileName));
				uploadClientFile(sockfd,fileName);
				printf("File uploaded.\n");
				/*Download and acnowledge that the status file has been received*/
				char *statusFileName=strtok(fileName,".");
				statusFileName=strcat(statusFileName,".txt");
				int status = downloadStatusFile(sockfd, statusFileName);
				printf("Status file received.\n");
				n = write(sockfd, "ACK", sizeof("ACK"));
				/*Download and execute the compiled file after acknowledgement*/
				if(n){
					char *execFileName = strtok(fileName, ".");
					strcat(execFileName, ".out");
					//printf("Inside downloadExecFile\n");
					downloadExecFile(sockfd, execFileName);
					printf("Executable file received\n");
					printf("1.Execute\n2.Exit\n");//Add option 2 for recompilation
					scanf("%d",&opt);
					if (opt==1)
					{
					char executable[100];
					sprintf(executable, "./%s",execFileName);
					system(executable);
					}
					//else if (opt==2)
						//break;
					else if (opt==2)
					{
						printf("Disconnecting from server...\n");
						exit(1);
					}
					else
						printf("Invalid option chosen\n");
				}
				else{
					printf("Error in compiling file\n");					
					int fd = open(statusFileName, O_RDONLY);
					char buf[5000];
					write(2, buf, sizeof(buf));
					printf("%s",buf);
				}
				
				break;

			case 2: printf("Disconeecting from server...\n");
				exit(1);
				break;
	}
	//}
}
