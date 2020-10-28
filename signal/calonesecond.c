/*************************************************************************
	> File Name: claonesecond.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Fri 18 Sep 2020 04:06:17 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

int main(int argc, char* argv[]){
	alarm(1);
	int i=0;
	while(1){
		printf("[%d]\n", ++i);
	}
	return 0;
}
