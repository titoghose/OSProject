#include <stdlib.h>
#define NUM 5
typedef struct mystruct{
	int clientSockFd;
	sem_t *write;
	int index;
}THREAD_PARAM;


typedef struct{
	pthread_t *thread_array[NUM];
	int status[NUM];
}THREAD_POOL;
	
THREAD_POOL *pool;

void *thread_compile(void *param){
	int n,filePointer;
	char fileName[500];
	THREAD_PARAM *para = (THREAD_PARAM *)param;
	n = read(para->clientSockFd,fileName,sizeof(fileName));
	downloadFile(para->clientSockFd,fileName);
	char **compiledFileNames = compileCode(fileName);
	uploadFile(para->clientSockFd,compiledFileNames);
	close(para->clientSockFd);
	writeLogs(fileName, para->write);
	pool->status[para->index] = 0;
}


void init_thread_pool(){
	int i;
	for(i=0;i<NUM;i++){
		pool->status[i] = 0;
	}
}

int current_index(THREAD_POOL *pool){
	int i;
	for(i=0;i<NUM;i++){
		if(!status[i])
			return i;
	}
	return -1;
}

int invoke_thread(THREAD_PARAM *param){
	int index;
	pthread_t thread;
	pool = (THREAD_POOL *)malloc(sizeof(THREAD_POOL));
	if((index = current_index(pool))!=-1){
		param->index = index;
		pool->thread_array[index] = pthread_create(&thread,0,&thread_compile,(void *)param);
		pool->status[index] = 1;
	}
	return index;
}