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


int main(int argc, char* argv[]){
	

	
	raise(SIGKILL);
	return 0;
}
