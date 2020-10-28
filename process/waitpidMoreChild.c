/*************************************************************************
  > File Name: waitpidMoreChild.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Wed 16 Sep 2020 02:29:18 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv){

	int i = 0;
	for(i = 0; i < 3; ++i){

		pid_t pid = fork();
		if(pid < 0){
			perror("fork error");
			return -1;
		}else if(pid > 0){
			//wait pid
			printf("children [%d], pid == [%d], ppid == [%d]\n", i, getpid(), getppid());
		}else if(pid == 0){
			printf("children [%d], pid == [%d], ppid == [%d]\n", i, getpid(), getppid());
			break;
		}
	}

	if(i == 0){//child process 1
		execlp("ls", "ls" ,"-l", NULL);	
		perror("execl error");
		return -1;
	}

	if(i == 1){//child process 2
		execl("../IOtest/fileIOtest", "fileIOtest", "./test.log", NULL);
		perror("execl error");
		return -1;
	}

	if(i == 2){//child process 3
		execl("./segError", "segError", NULL);	
		perror("execl error");
		return -1;
	}

	if(i == 3){//father process 

		int status;

		while(1){
			pid_t wpid= waitpid(-1, &status, WNOHANG);
			if(wpid > 0){
				if(WIFEXITED(status)){
					printf("child normal exit, status == [%d]\n", WEXITSTATUS(status));
				}else if(WIFSIGNALED(status)){
					printf("child killed by signal, signo == [%d]\n", WTERMSIG(status));
				}
			}else if(wpid == 0){

			}else if(wpid == -1){
				printf("no child is living, wpid == [%d]\n", wpid);
				break;
			}
		}
	}
	return 0;
}
