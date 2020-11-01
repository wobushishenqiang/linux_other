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

	printf("child thread [%d], pid == [%d], tid == [%ld]\n",*(int*)arg, getpid(), pthread_self());
}

int main(int argc, char* argv[]){

	int i = 0;
	int n = 5;
	int arr[5];
	pthread_t thread[5];
	int ret;
	for(i = 0; i < n; ++i){
		arr[i] = i;
		ret = pthread_create(&thread[i], NULL, mythread, &arr[i]);
		if(ret != 0){
			printf("pthread_create error, [%s]\n", strerror(ret));
			return -1;
		}
	}

	printf("main thread, pid == [%d], tid == [%ld]\n", getpid(), pthread_self());
	getchar();
	return 0;
}
