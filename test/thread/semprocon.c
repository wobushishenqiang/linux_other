/*************************************************************************
	> File Name: procon.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Mon 21 Sep 2020 07:50:45 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
typedef struct node{
	int data;
	struct node *next;
}NODE;

NODE *head = NULL;

sem_t sem_producer;
sem_t sem_consumer;

void *producer(void *arg){
	NODE* pNode = NULL;
	while(1){
		pNode = (NODE*)malloc(sizeof(NODE));
		if(pNode == NULL){
			perror("malloc error");
			exit(-1);
		}

		pNode->data = rand() % 1000;
		printf("P:[%d]\n", pNode->data);
		
		sem_wait(&sem_producer);
		pNode->next = head;
		head = pNode;
		sem_post(&sem_consumer);

		sleep(rand() % 3);
	}
}

void *consumer(void *arg){
	NODE *pNode=NULL;
	while(1){

		sem_wait(&sem_consumer);
		printf("C:[%d]\n", head->data);
		pNode = head;
		head = head->next;
		free(pNode);
		pNode = NULL;
		sem_post(&sem_producer);
		sleep(rand() % 3);
	}
}

int main(int argc, char* argv[]){
	int ret;
	pthread_t producer_thread;
	pthread_t consumer_thread;

	sem_init(&sem_producer, 0, 5);
	sem_init(&sem_consumer, 0, 0);

	ret = pthread_create(&producer_thread, NULL, producer, NULL);
	if(ret != 0){
		printf("pthread_create error, [%s]\n",strerror(ret));
		return -1;
	}

	ret = pthread_create(&consumer_thread, NULL, consumer, NULL);
	if(ret != 0){
		printf("pthread_create error, [%s]\n",strerror(ret));
		return -1;
	}

	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);

	sem_destroy(&sem_producer);
	sem_destroy(&sem_consumer);
	return 0;
}
