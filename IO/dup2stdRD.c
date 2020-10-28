#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char* argv[]){
	//open file
	int fd = open(argv[1], O_RDWR | O_CREAT , 0755);
	if(fd<0){
		perror("open error");
		return -1;
	}
	
	//dup2 function file redirected
	dup2(fd, STDOUT_FILENO);
	//the printf function would not print the world in the terminal but in the file
	printf("hello world");
	close(fd);
	return 0;
}
