/*************************************************************************
  > File Name: sigsetTest.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Fri 18 Sep 2020 04:29:58 AM PDT
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
	//	int sigemptyset(sigset_t *set);
	//
	//	int sigfillset(sigset_t *set);
	//
	//	int sigaddset(sigset_t *set, int signum);
	//  sigaddset(&set, SIGINT);
	//	int sigdelset(sigset_t *set, int signum);
	//
	//	int sigismember(const sigset_t *set, int signum);
	//
	//	int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
	//
	//	int sigpending(sigset_t *set);
	signal(SIGINT, mysighandle);
	signal(SIGQUIT, mysighandle);
	sigset_t ss;
	sigemptyset(&ss);

	sigaddset(&ss, SIGQUIT);
	sigaddset(&ss, SIGINT);

	sigprocmask(SIG_BLOCK, &ss, NULL);
	int i=0;
	int j=0;
	sigset_t pend;
	while(1){
		sigemptyset(&pend);
		sigpending(&pend);
		for(i = 1; i < 32; ++i){
			if(sigismember(&pend, i) == 1){
				printf("1");
			}else{
				printf("0");
			}

		}
		printf("\n");
		if(j % 10 == 0){
			sigprocmask(SIG_UNBLOCK, &ss, NULL);
			j = 0;
		}else{
			sigprocmask(SIG_BLOCK, &ss, NULL);
		}
		++j;
		sleep(1);
	}

	return 0;
}
