#include<unistd.h>
#include<cstring>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<iostream>


int main(int argc, char* argv[]){
    char IP[64];
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    inet_pton(AF_INET, argv[1], &addr.sin_addr.s_addr);
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));
    std::cout << atoi(argv[2]) << std::endl;
    std::cout << "link...." << std::endl;
    if(-1 == connect(sockfd, (sockaddr *)&addr, sizeof(addr))){
        perror("connect error");
    }

    char buff[2048] = {0};
    for(;buff[0] != -1;){
        std::cin >> buff;
        write(sockfd, buff, sizeof(buff));
        memset(buff, 0, sizeof(buff));
    }
}