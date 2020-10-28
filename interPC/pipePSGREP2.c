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
		perror("pipe error\n");
		return -1;
	}

	int i = 0;
	for(i = 0; i < 2; ++i){

		pid_t pid = fork();
		if(pid < 0){
			perror("fork error\n");
			return -1;
		}else if(pid > 0){
			//start write and close read first
			//close(fd[0]);
			//dup2(fd[1], STDOUT_FILENO);
			//execlp("ps", "ps", "aux", NULL);
			//perror("father process execlp error");

			printf("father [%d], pid == [%d], ppid == [%d]\n", i, getpid(), getppid());
		}else if(pid == 0){
			//start read and close write first!!!notice the read is hang function when it use in pipe,if write nothing it will hang in the read;
			//close(fd[1]);
			//dup2(fd[0], STDIN_FILENO);
			//execlp("grep", "grep", "bash", NULL);
			//perror("child process execlp error");
			printf("child [%d], pid == [%d], ppid == [%d]\n", i, getpid(), getppid());
			break;
		}
	}
	if(i == 0){
		//child 1 start write
		printf("start write\n");
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		
		execlp("ps", "ps", "aux", NULL);

		perror("child 1 execlp error\n");
		return -1;
	}
	if(i == 1){
		//child 2 start read
		printf("start read\n");
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);

		execlp("grep", "grep", "bash", NULL);

		perror("child 2 execlp error\n");
		return -1;
	}
	if(i == 2){
		close(fd[0]);
		close(fd[1]);
		int status;
		while(1){
			pid_t wpid = waitpid(-1, &status, WNOHANG);
			if(wpid > 0){
				if(WIFEXITED(status)){
					printf("child normal exit, status == [%d]\n", WEXITSTATUS(status));
				}else if(WIFSIGNALED(status)){
					printf("child killed by signal, signo == [%d]\n", WTERMSIG(status));
				}
			}else if(wpid == 0){
			

			}else if(wpid == -1){
				printf("no child is living\n");
				break;
			}
		}
	}
	return 0;
}
