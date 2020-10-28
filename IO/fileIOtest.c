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

	//write something
	write(fd, "hello world", strlen("hello world"));

	//move the file pointer
	lseek(fd, 0, SEEK_SET);
	//read
	char buf[1024];
	memset(buf,0x00,sizeof(buf));
	int n = read(fd, buf, sizeof(buf));
	printf("n==[%d],buf=[%s]\n", n, buf);

	//close
	close(fd);
	return 0;
}
