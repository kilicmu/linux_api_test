#include<unistd.h>
#include <sys/stat.h>
#include<sys/types.h>
#include<iostream>
#include<wait.h>



int main(){
    
    int pfd[2];
    pipe(pfd);
    int status = 0;
    pid_t pid = fork();
    if(pid == 0){
        close(pfd[0]);
        ssize_t size = write(pfd[1], "hello", 5);
    }else if(pid > 0){
        close(pfd[0]);
        close(pfd[1]);
        wait(&status);
        if(WIFSIGNALED(status)){
            std::cout << WTERMSIG(status) << std::endl;
        }
    }
    return 0;
}