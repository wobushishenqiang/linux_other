#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	struct stat st;
	stat(argv[1], &st);
	printf("[%d], [%d], [%d]\n",st.st_size, st.st_uid, st.st_gid);
	
}
