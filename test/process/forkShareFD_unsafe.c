/*************************************************************************
  > File Name: forkShareFD.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Wed 16 Sep 2020 01:53:33 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc, char* argv[]){
 
	//open file
	int fd = open(argv[1], O_RDWR | O_CREAT, 0755);
	if(fd < 0){
		perror("open error");
		return -1;
	}

	//fork
	pid_t pid = fork();
	if(pid < 0){
		perror("fork error");
		return -1;
	
	}else if(pid > 0){
		//write shomething
		printf("father: pid == [%d], fpid == [%d]\n", getpid(), getppid());
		write(fd, "hello world", strlen("hello world"));
		printf("write over\n");
		close(fd);
		int status;
		while(1){
			pid_t wpid = waitpid(-1, &status, WNOHANG);
			//printf("wpid == [%d]\n", wpid);
			if(wpid > 0){
				if(WIFEXITED(status)){
					printf("child normal exit, status == [%d]\n", WEXITSTATUS(status));
				}else if(WIFSIGNALED(status)){
					printf("child killed by signal, signo == [%d]\n", WTERMSIG(status));
				}
				
			}else if(wpid == 0){
				//printf("child is living, wpid == [%d]\n", wpid);
			
			}else if(wpid == -1){
				printf("no child is living, wpid == [%d]\n", wpid);
				break;
			}
		}
	}else if(pid == 0){
		printf("children: pid ==[%d], fpid == [%d]\n", getpid(), getppid());
		char buf[1024];
		memset(buf, 0x00, sizeof(buf));
		int n;
		sleep(1);
		lseek(fd, 0, SEEK_SET);
		n=read(fd, buf, sizeof(buf));
		printf("read over, n == [%d],buf == [%s]\n", n, buf);
		close(fd);

	}
	return 0;
}
