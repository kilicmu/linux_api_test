#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<iostream>
#include<cstring>
#include<wait.h>

void copy(char*ch1, int length1, char *ch2, int length2);

int main(){
    int fd = open("./test.mp4", O_RDWR|O_CREAT, 0666);
    int length = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    int fd_copy = open("./test_copy.mp4", O_RDWR|O_CREAT, 0666);
    ftruncate(fd_copy, length);
    char* map = (char* )mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd_copy, 0);
    if(map == MAP_FAILED){
        perror("map error");
        return -1;
    }
    
    memset(map, 0, length);
    int i = 0; //进程flag
    pid_t pid = fork();
    if(pid == 0){
        char buff[1024] = {0};
        while(read(fd, buff, sizeof(buff)-1) == 1023){
            buff[1023] = '\0';
            strcat(map, buff);
            std::cout << strlen(buff) << std::endl;
            // std::cout << sizeof(buff) << std::endl;
            memset(buff, 0x00, 1024);
            
        }
        strcat(map, buff);
        
        munmap(map, length);
        
        return 0;
    }
    
    if(pid > 0){
        wait(NULL);
        close(fd);
        close(fd_copy);
    }
        
    
    
    
}


