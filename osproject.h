#ifndef OS_Project
#define OS_Project

char **compileCode(char *fileName);
void downloadFile(int sockfd,char *fileName);
void uploadClientFile(int sockfd,char *fileName);
void uploadFile(int sockfd,char *fileName[2])

#endif