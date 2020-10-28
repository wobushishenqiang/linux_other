/*************************************************************************
	> File Name: signal.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Thu 17 Sep 2020 07:17:10 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include <signal.h>

void mysighandle(int signo){
	printf("signo == [%d]\n", signo);
}

int main(int argc, char* argv[]){
	
	int fd[2];
	int ret = pipe(fd);
	if(ret < 0){
		perror("pipe error");
		return -1;
	}


	signal(SIGPIPE, mysighandle);
	close(fd[0]);
	write(fd[1], "hello world", strlen("hello world"));

	return 0;
}
