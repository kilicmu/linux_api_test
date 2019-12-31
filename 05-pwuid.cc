#include<sys/stat.h>
#include<ctype.h>
#include<unistd.h>
#include<pwd.h>
#include <iostream>
#include<fcntl.h>

int main(){
    int fp = open("./test.txt", O_RDWR|O_CREAT, 0666);
    int tty = dup(1);
    std::cout << tty << std::endl;
    dup2(fp, 1);
    std :: cout << "hello" << std::endl;
     fflush(stdout);
    dup2(tty, 1);
    std :: cout << "???" << std::endl;
    close(tty);
    close(fp);
}