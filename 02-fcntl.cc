#include<iostream>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]){
	int fd = open("/dev/tty", O_RDONLY);
	char buf[1024] = {0};
	int flags = fcntl(fd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
	while(1){
		int ret = read(fd, buf, sizeof(buf));
		std::cout << "running" << std::endl;		
		if(ret){
			std::cout << "buff is" <<buf << std::endl;
			//memset(buf, 0, 1024);
		}

	}
	return 0;
}
