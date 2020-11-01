/*************************************************************************
	> File Name: threadTest.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Sat 19 Sep 2020 01:18:35 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>


void *mythread(void *arg){

	printf("child thread, pid == [%d], tid == [%ld]\n", getpid(), pthread_self());
}

int main(int argc, char* argv[]){

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


	pthread_t thread;
	int ret = pthread_create(&thread, &attr, mythread, NULL);
	if(ret != 0){
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	pthread_attr_destroy(&attr);

	printf("main thread, pid == [%d], tid == [%ld]\n", getpid(), pthread_self());


	ret = pthread_join(thread, NULL);
	if(ret != 0){
		printf("pthread_join error: [%s]\n", strerror(ret));
	}

	sleep(1);
	return 0;
}
