/*************************************************************************
	> File Name: rwlock.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Mon 21 Sep 2020 07:25:23 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

int number = 0;

pthread_rwlock_t rwlock;

void *thread_write(void *arg){
	int i = *(int*)arg;
	int cur;
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		cur = number;
		cur++;
		number = cur;
		printf("[%d]-W: [%d]\n",i ,cur);
		pthread_rwlock_unlock(&rwlock);
		usleep(500);
	}
}

void *thread_read(void *arg){
	int i = *(int*)arg;
	int cur;
	while(1){
		pthread_rwlock_rdlock(&rwlock);
		cur = number;
		printf("[%d]-R: [%d]\n",i ,cur);
		pthread_rwlock_unlock(&rwlock);
		usleep(400);
	}
}

int main(int argc, char* argv[]){

	int n = 8;
	int i = 0;
	int arr[8];
	pthread_t thread[8];

	pthread_rwlock_init(&rwlock, NULL);
	for(i = 0; i < 3; ++i){

		arr[i] = i;
		pthread_create(&thread[i], NULL, thread_write, &arr[i]);
	}

	for(i = 3; i < n; ++i){
		arr[i]=i;
		pthread_create(&thread[i], NULL, thread_read, &arr[i]);
	}

	for(i = 0;i < n; ++i){
		pthread_join(thread[i], NULL);
	}

	pthread_rwlock_destroy(&rwlock);
	return 0;
}
