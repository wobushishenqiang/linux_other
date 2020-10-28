/*************************************************************************
  > File Name: sigactionTest.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Fri 18 Sep 2020 04:57:31 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

void mysighandle(int signo){
	printf("signo == [%d]\n", signo);
}

int main(int argc, char* argv[]){
	//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	//struct sigaction {
	//	void     (*sa_handler)(int);
	//	void     (*sa_sigaction)(int, siginfo_t *, void *);
	//	sigset_t   sa_mask;
	//	int        sa_flags;
	//	void     (*sa_restorer)(void);
	//};
	struct sigaction act;
	act.sa_handler = mysighandle;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, NULL);

	while(1){
		sleep(1);
	}

	return 0;
}
