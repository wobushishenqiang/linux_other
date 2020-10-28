/*************************************************************************
	> File Name: alarmTest.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Fri 18 Sep 2020 03:59:44 AM PDT
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

	signal(SIGALRM, mysighandle);
	int n = alarm(5);
	printf("n == [%d]\n", n);
	n=alarm(2);
	printf("n == [%d]\n", n);

	getchar();
	return 0;
}
