#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char* argv[]){
	//open file
	int fd = open(argv[1], O_RDWR );
	if(fd<0){
		perror("open error");
		return -1;
	}
	
	//get the file size
	int len = lseek(fd, 0, SEEK_END);
	printf("file size:[%d]\n", len);

	close(fd);
	return 0;
}
