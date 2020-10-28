#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char* argv[]){
	//get the file setting
	struct stat st;
	lstat(argv[1], &st);
	
	//get the file type
	if((st.st_mode & S_IFMT) == S_IFREG){
		printf("normal file\n");
	}else if((st.st_mode & S_IFMT) == S_IFDIR){
		printf("dir file\n");
	}else if((st.st_mode & S_IFMT) == S_IFLNK){
		printf("link file\n");
	}

	if(S_ISREG(st.st_mode)){
		printf("normal file\n");
	}else if(S_ISDIR(st.st_mode)){
		printf("dir file\n");
	}else if(S_ISLNK(st.st_mode)){
		printf("link file\n");
	}

	//file power
	if(st.st_mode & S_IROTH){
		printf("---R----");
	}

	if(st.st_mode & S_IWOTH){
		printf("---W----");
	}

	if(st.st_mode & S_IXOTH){
		printf("---X----");
	}
	printf("\n");
	return 0;
}     
     
