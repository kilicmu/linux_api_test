#include<iostream>
#include<sys/stat.h>
#include<unistd.h>
#include<signal.h>
using namespace std;

void action(int signal){
    cout << "catch a" << signal << endl;
    sleep(2);
    cout << "catch endl" <<endl;
}

int main(){

    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = action;
    
    sigaction(SIGINT, &act, NULL);
    while(1){
        cout << "how to kill me" << endl;
        sleep(1);
    }
}