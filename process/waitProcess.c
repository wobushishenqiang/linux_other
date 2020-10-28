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
		int status;
		pid_t wpid = wait(&status);
		printf("wpid == [%d]\n", wpid);
		
		if(WIFEXITED(status)){
			
			printf("child normal exit, status == [%d]\n", WEXITSTATUS(status));

		}else if(WIFSIGNALED(status)){
				
			printf("child killed by signal, signo == [%d]\n", WTERMSIG(status));
		}

	}else if(pid == 0){//children process but zombie
		
		printf("children: pid ==[%d], fpid == [%d]\n", getpid(), getppid());
		sleep(5);
		return 9;
	}

	return 0;
}
