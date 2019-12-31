#include <iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>

int main(int argc, char* argv[]){
	if(argc != 3){
		return -1;
	}

	int fd = open(argv[1], O_RDWR);
	int fd_new = open(argv[2], O_RDWR|O_CREAT);
	char buf[1024] = {0};
	int ret = sizeof(buf);
	do{
		ret = read(fd, buf, sizeof(buf));
		write(fd_new, buf, sizeof(buf));
		memset(buf, 0, 1024);
	}while(ret == sizeof(buf));
	close(fd);
	close(fd_new);
	return 0;
}
