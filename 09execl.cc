#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(){
    execlp("ls", "-l", NULL);
    perror("execError");
    return 0;
}