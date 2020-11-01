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

typedef struct node{
	int data;
	struct node *next;
}NODE;

NODE *head = NULL;

pthread_mutex_t mutex;

pthread_cond_t cond;
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

		pthread_mutex_lock(&mutex);
		pNode->next = head;
		head = pNode;
		pthread_mutex_unlock(&mutex);

		pthread_cond_signal(&cond);

		sleep(rand() % 3);
	}
}

void *consumer(void *arg){
	NODE *pNode=NULL;
	while(1){
		pthread_mutex_lock(&mutex);
		if(head == NULL){
			pthread_cond_wait(&cond, &mutex);
		}
		printf("C:[%d]\n", head->data);
		pNode = head;
		head = head->next;
		pthread_mutex_unlock(&mutex);
		free(pNode);
		pNode = NULL;
		
		sleep(rand() % 3);
	}
}

int main(int argc, char* argv[]){
	int ret;
	pthread_t producer_thread;
	pthread_t consumer_thread;

	pthread_mutex_init(&mutex, NULL);

	pthread_cond_init(&cond, NULL);

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

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}
