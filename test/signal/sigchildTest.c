/*************************************************************************
  > File Name: sigchildTest.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Fri 18 Sep 2020 06:31:03 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

void waitchild(int signo){
	while(1){
		pid_t wpid = waitpid(-1, NULL, WNOHANG);

		if(wpid > 0){
			printf("child is quit, wpid == [%d]\n", wpid);
		}else if(wpid == 0){
			//printf();
			break;
		}else if(wpid == -1){
			printf("no child is living, wpid == [%d]\n", wpid);
			break;
		}
	}
}
int main(int argc, char* argv[]){

	//process i
	int i=0;

	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);
	sigprocmask(SIG_BLOCK, &mask, NULL);

	for(i=0; i<3; ++i){

		pid_t pid = fork();
		if(pid < 0){
			perror("fork error");
			return -1;
		}else if(pid > 0){
			printf("father: pid == [%d], ppid == [%d]\n", getpid(), getppid());
		}else if(pid == 0){//children process but zombie
			printf("children: pid == [%d], ppid == [%d]\n", getpid(), getppid());
			break;//to make sure not create another grandchildren process
		}
	}

	if(i==0){
		printf("[%d]--[%d]: chlid\n", i, getpid());
	}

	if(i==1){
		printf("[%d]--[%d]: chlid\n", i, getpid());
	}

	if(i==2){
		printf("[%d]--[%d]: chlid\n", i, getpid());
	}

	if(i==3){
		printf("[%d]--[%d]: father\n", i, getpid());
		struct sigaction act;
		act.sa_handler = waitchild;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		sleep(5);
		sigaction(SIGCHLD, &act, NULL);

		sigprocmask(SIG_UNBLOCK, &mask, NULL);

	}

	return 0;
}
