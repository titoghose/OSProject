#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

/*
	Function to write compiling logs into a file.
	
	Input:
		1. Name of file
		2. semaphore pointer to provide lock on the log file
*/

void writeLogs(char fileName[], sem_t *write){
	sem_wait(write);
	FILE *logFilePointer = fopen("compileLog.txt", "a");
	time_t rawtime;
  	struct tm * timeinfo;
	time(&rawtime);
  	timeinfo = localtime ( &rawtime );
  	char *timeBuffer;
  	timeBuffer = asctime(timeinfo);
  	strtok(timeBuffer, "\n");
  	fprintf(logFilePointer, "%s %s\n", fileName, timeBuffer);
  	fclose(logFilePointer);
  	sem_post(write);
}
