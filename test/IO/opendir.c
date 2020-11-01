/*************************************************************************
	> File Name: opendir.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 14 Sep 2020 06:14:20 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]){
	//open dir
	DIR *pDir=opendir(argv[1]);
	if(pDir==NULL){
		perror("opendir error");
		return -1;
	}

	//read dir item
	struct dirent *pDent=NULL;
	while((pDent = readdir(pDir))!=NULL){
		printf("[%s]\n",pDent->d_name);
		//file type
		switch(pDent->d_type){

			case DT_REG:
				printf("normal file");
			    break;

			case DT_DIR:
				printf("dir");
				break;

			case DT_LNK:
				printf("link file");
				break;

			default:
				printf("unkonw");
		}
		printf("\n");
	}
	//close dir
	closedir(pDir);
	return 0;
}
