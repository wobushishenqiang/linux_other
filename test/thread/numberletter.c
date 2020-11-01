/*************************************************************************
	> File Name: numberletter.c
	> Author: xyx
	> Mail:719660015@qq.com 
	> Created Time: Tue 29 Sep 2020 06:13:58 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t lettermutex;
pthread_mutex_t numbermutex;
//pthread_mutex_t startmutex;

void *countnumber(void *arg){

	int number = 1;
	while(number <= 26){
		
		pthread_mutex_lock(&numbermutex);

		printf("number: [%d]\n", number);
		number++;
		//pthread_mutex_unlock(&startmutex);
		
		pthread_mutex_unlock(&lettermutex);

		
	}
}

void *countletter(void *arg){

	//pthread_mutex_lock(&startmutex);
	char letter = 'a';
	while(letter <= 'z'){

		pthread_mutex_lock(&lettermutex);
		printf("letter: [%c]\n", letter);
		letter++;
		pthread_mutex_unlock(&numbermutex);
	}
}

int main(int argc, char* argv[]){

	pthread_t numberthread;
	pthread_t letterthread;

	pthread_mutex_init(&lettermutex, NULL);
	pthread_mutex_init(&numbermutex, NULL);
	//pthread_mutex_init(&startmutex, NULL);

	pthread_mutex_lock(&lettermutex);

	int ret = pthread_create(&numberthread, NULL, countnumber, NULL);
	if(ret != 0){
		printf("pthread_create error, [%s]\n", strerror(ret));
	}

	ret = pthread_create(&letterthread, NULL, countletter, NULL);
	if(ret != 0){
		printf("pthread_create error, [%s]\n", strerror(ret));
	}

	pthread_join(numberthread, NULL);
	pthread_join(letterthread, NULL);

	//pthread_mutex_destroy(&startmutex);
	pthread_mutex_destroy(&lettermutex);
	pthread_mutex_destroy(&numbermutex);
	return 0;
}
