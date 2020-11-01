/*************************************************************************
	> File Name: forkMoreChildren.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Mon 14 Sep 2020 11:40:14 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char *argv[]){
	//process i
	int i=0;

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
	}

	sleep(10);
	return 0;
	
}
