#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/time.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>

void dosomthing(int num){
    std::cout << "alarm" << std::endl;
}

int main(){
    struct sigaction action;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    action.sa_handler = dosomthing;
  
    itimerval itm = {{3,0},{5,0}};
    setitimer(ITIMER_REAL, &itm, NULL);
    sigaction(SIGALRM, &action, NULL);
    while (1)
    {
        std::cout << "...." << std::endl;
        sleep(1);
    }
    
}