/*************************************************************************
	> File Name: execlTest1.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Tue 15 Sep 2020 02:33:39 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int i=0;
	for(i=0; i<argc; ++i){
		printf("[%d];[%s]\n",i ,argv[i]);
	}
	return 0;
}
