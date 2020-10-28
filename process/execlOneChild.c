/*************************************************************************
	> File Name: forkOneChildren.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Mon 14 Sep 2020 11:29:11 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char* argv[]){

	//create children process
	pid_t pid=fork();
	if(pid<0){
		perror("fork error");
		return -1;
	}else if(pid > 0){//father process
		printf("father: pid == [%d], fpid == [%d]\n", getpid(), getppid());
		sleep(1);
	}else if(pid == 0){//children process but zombie
		printf("children: pid ==[%d], fpid == [%d]\n", getpid(), getppid());
		//execl("/usr/bin/ls", "ls", "-l", NULL);
		//execl("./execlTest1", "test", "hello", "world", NULL);
		execlp("ls", "ls", "-l", NULL);
		perror("execl error");
	}

	return 0;
}
