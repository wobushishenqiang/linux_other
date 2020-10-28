/*************************************************************************
  > File Name: setitimerTest.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Fri 18 Sep 2020 04:10:14 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/time.h>
#include<signal.h>
void mysighandle(int signo){
	printf("signo == [%d]\n", signo);
}
int main(int argc, char* argv[]){
	signal(SIGALRM, mysighandle);

	struct itimerval itv;
	//struct itimerval {
	//	struct timeval it_interval; /* Interval for periodic timer */
	//	struct timeval it_value;    /* Time until next expiration */
	//};

	//struct timeval {
	//	time_t      tv_sec;         /* seconds */
	//	suseconds_t tv_usec;        /* microseconds */
	//};	
	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;

	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;

	//	int setitimer(int which, const struct itimerval *new_value,
	//                     struct itimerval *old_value);
	int n = setitimer(ITIMER_REAL, &itv, NULL);
		

	getchar();
	return 0;
}
