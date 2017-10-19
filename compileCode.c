#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **compileCode(char fileName[]){
	int compilePID = fork();
	char **compiledFileNames = (char**) malloc(sizeof(char*) * 2);
	if(compilePID < 0){
		perror("compileCode(): Error in forking. Attempting again.\n");
		//compileCode(fileName);
	}
	else if(compilePID == 0){
		execlp("sh", "sh", "compile.sh", fileName, (char*)NULL);	
		//execlp("sh", "sh", "temp.sh", "/Users/upamanyughose/Desktop", (char*)NULL);	
	}
	else{
		/* Waiting for child process to finish compiling */
		waitpid(compilePID, NULL, 0);

		/* Creating string arrays to hold output filename and error file name */
		compiledFileNames[0] = (char*) malloc(sizeof(char) * (strlen(fileName) + 3));
		compiledFileNames[1] = (char*) malloc(sizeof(char) * (strlen(fileName) + 3));	

		/* Setting file names by appending .out(executable) and .txt(error) */
		char *p = strtok(fileName, ".");
		
		memcpy(compiledFileNames[0], p, strlen(p));
		strcat(compiledFileNames[0], ".out\0");
		memcpy(compiledFileNames[1], p, strlen(p));
		strcat(compiledFileNames[1], ".txt\0");
	}
	return compiledFileNames;
}
/*
int main()
{
	char temp[] = {"temp.c"};
	char **compiledFileNames = compileCode(temp);
	printf("%s\n", compiledFileNames[0]);
	printf("%s\n", compiledFileNames[1]);
	return 0;
}*/