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


	//read
	char buf[1024];
	memset(buf,0x00,sizeof(buf));
	int n = read(fd, buf, sizeof(buf));
	printf("First:n==[%d],buf=[%s]\n", n, buf);

	//read again
	memset(buf,0x00,sizeof(buf));
	n = read(fd, buf, sizeof(buf));
	printf("Second:n==[%d],buf=[%s]\n", n, buf);
	
	//close
	close(fd);
	return 0;
}
