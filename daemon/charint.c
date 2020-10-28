/*************************************************************************
	> File Name: charint.c
	> Author: xyx
	> Mail:719660015@qq.co 
	> Created Time: Fri 18 Sep 2020 08:39:02 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char* argv[]){
	time_t t;
	time(&t);
	char *ct = ctime(&t);
	ct[strlen(ct)-1] = '\0';
	int j = 0;

	char *newfilename = (char*)malloc(sizeof(char)*(strlen(ct)+10)) ;

	char cj[10] = {0};

	sprintf(cj, "%d", j);
	sprintf(cj, "%.10s",cj);

	sprintf(newfilename, "%s_%s", ct, cj);

	printf("res == [%s]\n", newfilename);

	free(newfilename);
	return 0;
}
