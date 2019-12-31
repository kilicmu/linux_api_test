#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct Node{
    int val ;
    Node * next;
    Node(int _val, Node* _next = NULL):val(_val), next(_next){}
};

Node * head = NULL;

int i = 100;


void * producter(void* argv){
    while(1){
        pthread_mutex_lock(&mutex);
        Node * newNode = new Node(i++);
        newNode->next = head;
        head = newNode;
        std::cout << "productor" << pthread_self() << ":" << head->val << std::endl;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        sleep(1);
    }
}

void * customer(void * argv){
    while(1){
        pthread_mutex_lock(&mutex);
        if(head == NULL){
            pthread_cond_wait(&cond, &mutex);
            if(head == NULL){
                pthread_mutex_lock(&mutex);
                pthread_cond_wait(&cond, &mutex);
                pthread_mutex_unlock(&mutex);
            }
        }
        Node *p = head;
        head = head->next;
        std::cout << "customer" << pthread_self() << ":" << p->val << std::endl;
        delete p;
        pthread_mutex_unlock(&mutex);
        sleep(2);

        
    }
}

int main(){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    /***初始化链表***/
    pthread_t pptd[5];
    pthread_t cptd[5];
    for(int i = 0;i <5; i++){
        pthread_create(&pptd[i], &attr, producter, NULL);
    }
    for(int i = 0;i <5; i++){
        pthread_create(&cptd[i], &attr, customer, NULL);
    }
    pthread_attr_destroy(&attr);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    pthread_exit((void* )1);
    

}