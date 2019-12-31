#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstdlib>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<iostream>
#include<signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include<error.h>
using namespace std;

void gc(int flag){
    
    while(1 < waitpid(-1, NULL, WNOHANG));  
    cout << "gc" << endl;  
}

int main(int argc, char*argv[]){
    int port = atoi(argv[1]);
    //初始化sigaction
    struct sigaction action;
    action.sa_flags=0;
    sigemptyset(&action.sa_mask);
    action.sa_handler=gc;
    //定义进程回收的信号捕捉
    sigaction(SIGCHLD, &action, NULL);
    //定义监听主进程
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //初始化进程的sockaddr_in参数,注意,传参要转换为sockaddr*
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    
    //绑定sockaddr信息
    bind(sockfd, (sockaddr*) &addr, sizeof(addr));
    //设置监听socket
    listen(sockfd, 128);
    //定义客户端sockaddr
    struct sockaddr_in client_addr;
    socklen_t socklen = sizeof(client_addr);
    
    for(; ; ){
        //接受TCP请求
        int csockfd = accept(sockfd, (sockaddr *)&client_addr, &socklen);
        //错误处理
        if(csockfd == -1){
            //非预期信号处理导致的中断跳过->重新接收
            if(errno == EINTR){
                continue;
            }
            //其他错误,退出
            exit(1);
        }
        pid_t pid = fork();
        //创建进程错误
        if(pid == -1){
            perror("fork error");
            //关闭子进程套接字
            close(sockfd);
        }
        //子进程处理链接
        if(pid == 0){
            //关闭父进程监听套接字->节约资源
            close(sockfd);
            //获取此链接的client的IP地址
            char IP[64] = {0};
            inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, IP, socklen);
            //定义缓冲区,存储传输内容
            char buff[4096];
            memset(buff, 0, sizeof(buff));
            //读取套接字缓冲区内容
            for(ssize_t readsize; 0 < (readsize = read(csockfd, buff, sizeof(buff)));){
                //断开链接处理
                if(readsize == 0){
                    cout << "断开链接" << endl;
                    close(csockfd);
                    break;
                }
                //读取信息错误处理
                if(readsize == -1){   
                    perror("read error: ");  
                }
                //内容输出与初始化缓冲区
                cout << "IP: " << IP << " PORT: " << client_addr.sin_port << " : " <<buff << endl;
                memset(buff, 0, sizeof(buff));
            }
        }
    }
    
}