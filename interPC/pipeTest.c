/*************************************************************************
  > File Name: pipeTest.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Wed 16 Sep 2020 07:08:27 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include <signal.h>

void sighandler(int signo){
	printf("signo == [%d]\n", signo);
}


int main(int argc, char* argv[]){
	//create pipe
	int fd[2];
	int ret = pipe(fd);
	if(ret < 0){
		perror("pipe error");
		return -1;
	}
	
	pid_t pid = fork();
	if(pid < 0){
		perror("fork error");
		return -1;
	}else if(pid > 0){
		//start write and close read first
		signal(SIGPIPE, sighandler);
		close(fd[0]);
		write(fd[1], "hello world", strlen("hello world"));
		printf("write over\n");
		wait(NULL);
	}else if(pid == 0){
		//start read and close write first!!!notice the read is hang function when it use in pipe,if write nothing it will hang in the read;

		sleep(2);
		close(fd[1]);
		char buf[64];
		memset(buf, 0x00, sizeof(buf));
		int n = read(fd[0], buf, sizeof(buf));
		printf("read over ,n == [%d], buf == [%s]\n", n, buf);
	}

	return 0;
}
