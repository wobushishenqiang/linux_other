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
int main(int argc, char* argv[]){

//	int ret = mkfifo("./myfifo", 0777);
//	if(ret < 0){
//		perror("mkfifo error");
//		return -1;
//	}

	int fd = open("./myfifo", O_RDWR);
	if(fd < 0){
		perror("open error");
		return -1;
	}
	char buf[1024];
	//read something
	memset(buf, 0x00, sizeof(buf));
    int n =	read(fd, buf, sizeof(buf));
	printf("n == [%d], buf == [%s]\n", n, buf);

	close(fd);

	getchar();
	return 0;
}
