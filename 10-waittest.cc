#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>


int main(){
    pid_t pid = fork();
    int statu = 0;
    if(pid == 0){
        std::cout << "child pid: " << getpid() << "ppid:" << getppid() << std::endl;
        sleep(3);
        exit(1);
    }else{
        std::cout << "father pid: " << getpid() << "ppid:" << getppid() << std::endl;
        pid_t pid2 = waitpid(-1, &statu, WNOHANG);
        std::cout << "pid2" << pid2 << std::endl;
        if(WIFEXITED(statu)){
            std::cout << "is stop by " << WEXITSTATUS(statu) << std::endl;
        }
        if(WIFSIGNALED(statu)){
            std::cout << "signal stop by " << WTERMSIG(statu) << std::endl;
        }
        
        std::cout<< statu << std::endl;
        // sleep(4);
        pid_t pid3 = waitpid(-1, &statu, WNOHANG);
        std::cout << "pid3:" <<pid3 << std::endl;
        while (true);
    }
}