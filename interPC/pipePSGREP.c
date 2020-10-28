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
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execlp("ps", "ps", "aux", NULL);
		perror("father process execlp error");

	}else if(pid == 0){
		//start read and close write first!!!notice the read is hang function when it use in pipe,if write nothing it will hang in the read;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execlp("grep", "grep", "bash", NULL);
		perror("child process execlp error");
	}

	return 0;
}
