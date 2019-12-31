#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <cstring>
#include<sys/wait.h>
int main()
{
    sockaddr_un servaddr;
    servaddr.sun_family = AF_UNIX;
    memset(servaddr.sun_path, 0, sizeof(servaddr.sun_path));
    strcpy(servaddr.sun_path, "server.socket");
    socklen_t servlen = sizeof(servaddr);
    pid_t pid = fork();
    if (pid != 0)
    {
        int servfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (servfd == -1)
        {
            perror("socket");
            return -1;
        }
        int ret = bind(servfd, (sockaddr *)&servaddr, sizeof(servaddr));
        if(ret == -1){
           perror("bind");
           exit(-1);
        }
        listen(servfd, 128);
        sockaddr_un cliaddr;
        socklen_t clilen;
        int clifd = accept(servfd, (sockaddr *)&cliaddr, &clilen);
        if (clifd == -1)
        {
            perror("accept");
            return -1;
        }
        while (1)
        {
            char buff[1024] = {0};
            recv(clifd, buff, sizeof(buff), 0);
            send(clifd, "收到", sizeof("收到"), 0);
            std :: cout << buff << std::endl;
            sleep(1);
        }
        wait(0);
    }
    if (pid == 0)
    {
        int clifd = socket(AF_UNIX, SOCK_STREAM, 0);
        sockaddr_un cliaddr;
        cliaddr.sun_family = AF_UNIX;
        memset(cliaddr.sun_path, 0, sizeof(cliaddr.sun_path));
        strcpy(cliaddr.sun_path, "client.socket");
        bind(clifd, (sockaddr *)&cliaddr, sizeof(cliaddr));
        connect(clifd, (sockaddr *)&servaddr, servlen);
        while (1)
        {
            char buff[1024] = {0};
            strcpy(buff, "发送数据");
            send(clifd, buff, sizeof(buff), 0);
            char buf[1024] = {0};
            recv(clifd, buf, sizeof(buf), 0);
            std::cout << buf << std::endl;
            sleep(1);
        }
    }
}