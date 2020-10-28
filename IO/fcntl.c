/*************************************************************************
	> File Name: dup.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Mon 14 Sep 2020 06:36:31 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
	//open file
	int fd = open(argv[1], O_RDWR);
	if(fd<0){
		perror("open error");
		return -1;
	}

	//dup copy the file description
	//int newfd = dup(fd);
	int newfd = fcntl(fd, F_DUPFD, 0);
	printf("newfd:[%d], fd:[%d]\n", newfd, fd);

	//use fd to write file
	write(fd, "hello world", strlen("hello world"));

	//use lseek function to move the file pointer
	lseek(fd, 0, SEEK_SET);

	//use newfd to read file
	char buf[64];
	memset(buf, 0x00, sizeof(buf));
	int n=read(newfd, buf, sizeof(buf));
	printf("read over: n==[%d], buf==[%s]\n", n, buf);

	//close file
	close(fd);
	close(newfd);
	return 0;
}
