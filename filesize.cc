#include<iostream>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
	if(argc <= 1){
		return -1;
	}
	int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
	int ret = lseek(fd, 1024, SEEK_END);
	write(fd, "a", 1);
	close(fd);
	return 0;
}
