#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<wait.h>
#include<iostream>

void action(int signal){
    pid_t wpid ;
    while((wpid = waitpid(-1, NULL, WNOHANG) <= 0 ));
    std::cout << "kill okey" << std::endl;
    
    
}


int main(){
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = action;
    sigaction(SIGCHLD, &act, NULL);
    int i = 0;
    for(; i<10; i++){
        pid_t pid = fork();
        if(pid == 0){
            break;
        }
    }

    if(i != 10){
        sleep(i);
        exit(1);
    }
    while(1){
        std::cout << "keeping...." << std::endl;
        sleep(1);
    };
}