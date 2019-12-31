#include<unistd.h>
#include <sys/stat.h>
#include<sys/types.h>
#include<iostream>
#include<wait.h>



int main(){
    
    int p_fp[2];
    pipe(p_fp);
    pid_t pid = fork();
    if(pid == 0){       
        close(p_fp[0]);
        dup2(p_fp[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
    }
    if(pid > 0){       
        close(p_fp[1]);
        dup2(p_fp[0], STDIN_FILENO);
        execlp("grep", "grep", "zsh", NULL);        
        wait(NULL);       
    }
    
    return 0;
}