/*************************************************************************
  > File Name: fifoTest.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Thu 17 Sep 2020 12:00:41 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
int main(int argc, char* argv[]){
	int ret = access("./myfifo", F_OK);
	if(ret != 0){
		ret = mkfifo("./myfifo", 0777);
		if(ret < 0){
			perror("mkfifo error");
			return -1;
		}
	}

	int fd = open("./myfifo", O_RDWR);
	if(fd < 0){
		perror("open error");
		return -1;
	}

	//write something
	write(fd, "hello world", strlen("hello world"));


	close(fd);

	getchar();
	return 0;
}
