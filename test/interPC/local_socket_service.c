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

#define MAX_CON_WAIT_QUEUE 128
int main(int argc, char *argv[]){

	int lfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(lfd < 0){

		perror("socket error");
		return -1;
	}

	struct sockaddr_un serv;
	bzero(&serv, sizeof(serv));
	serv.sun_family = AF_UNIX;
	strcpy(serv.sun_path,"./serv.sock");
	
	unlink("./serv.sock");
	bind(lfd, (struct sockaddr *)&serv, sizeof(serv));

	listen(lfd, MAX_CON_WAIT_QUEUE);


	struct sockaddr_un client;
	socklen_t len = sizeof(client);
	int cfd = accept(lfd, (struct sockaddr *)&client, &len);

	if(cfd < 0){
	
		perror("accept error");
		return -1;
	}

	int n;
	char buf[1024];
	while(1){

		memset(buf, 0x00, sizeof(buf));
		n = read(cfd, buf, sizeof(buf));
		printf("n == [%d], buf == %s\n", n, buf);
		if(n <= 0){

			printf("connect closed or read error\n");
			break;
		}

		for(int i=0;i<n;++i){

			buf[i] = toupper(buf[i]);

		}

		write(cfd, buf, n);

	}
	close(cfd);
	close(lfd);
	return 0;
}

