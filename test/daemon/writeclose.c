/*************************************************************************
	> File Name: writeclose.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Fri 18 Sep 2020 08:21:30 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	int fd =open("./test.log", O_CREAT | O_RDWR, 0755);
	if(fd < 0){
		perror("open error");
		return -1;
	}

	close(fd);
	write(fd, "hello world", strlen("hello world"));
	printf("fd == [%d]\n",fd);
    
	if(fcntl(fd, F_GETFD, 0) == -1 )
	{
		perror("close error");
	}
	
	return 0;
}
