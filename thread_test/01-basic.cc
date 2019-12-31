#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<iostream>
#include<cstring>

void * thread1(void * argv){
    for(int i = 0; i < 100; i++){
        sleep(1);
        std::cout << pthread_self() <<" :thread1......" << i << std::endl;
    }
    pthread_exit((void *)100);
}

int main(){
    pthread_t ptid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&ptid, &attr, thread1, NULL);
    int ret;
    if((ret = pthread_join(ptid, NULL))>0){
        std::cout << "join error:" << ret << "," << strerror(ret) << std::endl;
    }
    // pthread_join(ptid, &trouble);
    // perror("thread error");
    
    pthread_attr_destroy(&attr);
    pthread_exit((void *)1); 
}