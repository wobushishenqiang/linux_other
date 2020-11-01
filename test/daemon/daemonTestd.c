/*************************************************************************
  > File Name: daemonTestd.c
  > Author: xyx
  > Mail:719660015@qq.com 
  > Created Time: Fri 18 Sep 2020 07:07:40 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<signal.h>
#include<fcntl.h>
#include<time.h>

int fd;
int openFlag;
const char *filename = "./time.log";
int openflag = 0;
void mysighandle(int signo){

	if(openflag == 0){
		fd = open(filename, O_RDWR | O_CREAT |O_APPEND, 0755);
		if(fd < 0){
			perror("open error");
			return; 
		}
		openflag = 1;
	}
	time_t t;
	time(&t);

	char *ct = ctime(&t);

	write(fd, ct, strlen(ct));

	return;
}

int main(int argc, char* argv[]){

	pid_t pid = fork();

	if(pid < 0){
		perror("fork error");
		exit(0);
	}else if(pid > 0){
		exit(0);
	}

	setsid();

	chdir("/home/xyx/Documents/SourceCode/cpptest/daemonTest");

	umask(0000);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	struct sigaction act;
	act.sa_handler = mysighandle;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, NULL);

	struct itimerval tm;
	tm.it_interval.tv_sec = 1;
	tm.it_interval.tv_usec = 0;

	tm.it_value.tv_sec = 1;
	tm.it_value.tv_usec = 0;

	int n = setitimer(ITIMER_REAL, &tm, NULL);

	struct stat st;
	while(1){
		stat(filename, &st);
		if(st.st_size > 1024){

			close(fd);

			time_t t;
			time(&t);

			char *ct = ctime(&t);
			ct[strlen(ct)-1] = '\0';

			char *newfilename = (char*)malloc( sizeof(char) * (strlen(ct) + 10) );

			int j = 0;

			char cj[10] = {0};

			sprintf(cj, "%d", j);
			sprintf(cj, "%.10s", cj);

			sprintf(newfilename, "time_%s_%s.log", ct, cj);

			while(0 == access(newfilename, F_OK)){
				j++;

				char cj[10] = {0};

				sprintf(cj, "%d", j);
				sprintf(cj, "%.10s", cj);
				sprintf(newfilename, "time_%s_%s.log", ct, cj);
			}
			rename(filename, newfilename);

			free(newfilename);

			openflag = 0;

		}
		sleep(1);
	}
	return 0;
}
