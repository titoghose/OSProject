/* Function to get the contents of the current directory */
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
void getContentsDir(){
	char *fname;
	DIR *d;
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
