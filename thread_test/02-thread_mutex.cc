#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>

int main(){
    pthread_rwlock_t mutex;
    pthread_rwlock_init(&mutex, NULL);
    // pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
    pthread_rwlock_rdlock(&mutex);
    std::cout << "locked" << std::endl;
    return 0;
}