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
#define NUM 5000
int number = 0;

pthread_mutex_t mutex;


void *mythread(void *arg){
	int i = 0;
	int n;
	for(i = 0;i < NUM;++i){
		pthread_mutex_lock(&mutex);
		n = number;
		n++;
		number = n;
		pthread_mutex_unlock(&mutex);
		printf("number == [%d], tid == [%ld]\n", number, pthread_self());
	}
}


int main(int argc, char* argv[]){

	pthread_mutex_init(&mutex,NULL);
	pthread_t thread1;
	pthread_t thread2;

	int ret = pthread_create(&thread1, NULL, mythread, NULL);
	if(ret != 0){
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	ret = pthread_create(&thread2, NULL, mythread, NULL);
	if(ret != 0){
		printf("pthread_create error, [%s]\n", strerror(ret));
		return -1;
	}

	printf("main thread, pid == [%d], tid == [%ld]\n", getpid(), pthread_self());
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&mutex);
	return 0;
}
