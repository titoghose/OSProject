#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
	This function invokes a shell script to compile the client code and write errors into a file.
	
	Input:
		Source code file name to compile.

	It generates two files:
		1. executable in case of successful compilation
		2. txt file that contains errors or NO ERROR message.

	Returns: 
		Array containing executable and txt file names 
*/

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
		
		memcpy(compiledFileNames[1], p, strlen(p));
		strcat(compiledFileNames[1], ".out\0");
		memcpy(compiledFileNames[0], p, strlen(p));
		strcat(compiledFileNames[0], ".txt\0");
	}
	return compiledFileNames;
}