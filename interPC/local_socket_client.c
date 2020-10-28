/*************************************************************************
	> File Name: local_socket.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Wed 14 Oct 2020 05:47:54 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/socket.h>
#include<sys/un.h>

int main(int argc, char *argv[]){

	int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(cfd < 0){

		perror("socket error");
		return -1;
	}

	struct sockaddr_un serv;
	bzero(&serv, sizeof(serv));
	serv.sun_family = AF_UNIX;
	strcpy(serv.sun_path,"./serv.sock");

	int ret = connect(cfd,(struct sockaddr *)&serv,sizeof(serv));
	if(ret < 0){

		perror("connect error");
		return -1;
	}
	
	int n;
	char buf[1024];
	while(1){


		memset(buf, 0x00, sizeof(buf));
		n = read(STDIN_FILENO, buf, sizeof(buf));
		
		write(cfd, buf, n);

		
		memset(buf, 0x00,sizeof(buf));
		n = read(cfd, buf, sizeof(buf));
		if(n <= 0){

			printf("connect closed or read error\n");
			break;
		}
		printf("n == [%d], buf == %s\n", n, buf);

	}
	close(cfd);
	return 0;
}

