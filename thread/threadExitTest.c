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

struct Test{
	int data;
	char name[64];
};

void *mythread(void *arg){

	struct Test t = *(struct Test*)arg;
	printf("Test data == [%d], Test name == [%s]\n", t.data, t.name);
	printf("child thread, pid == [%d], tid == [%ld]\n", getpid(), pthread_self());
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){

	struct Test t;
	t.data = 99;
	strcpy(t.name, "Test");
	pthread_t thread;
	int ret = pthread_create(&thread, NULL, mythread, &t);
	if(ret != 0){
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	printf("main thread, pid == [%d], tid == [%ld]\n", getpid(), pthread_self());
	getchar();
	return 0;
}
