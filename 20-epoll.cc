#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <cstring>
#include <memory>
#include <vector>
#include <fcntl.h>
using namespace std;

class Epoll
{
private:
    /* data */
    int lfd;
    sockaddr_in localaddr;
    int epfd;
    epoll_event levent;
    epoll_event client_events[200] = {0};
    int init_addr(char *ip, int port);

public:
    Epoll(char *ip, int port);
    ~Epoll();
    int start_listen();
    int run();
};

Epoll::Epoll(char *ip, int port)
{
    this->lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (init_addr(ip, port))
    {
        cout << "error" << endl;
        exit(1);
    }
    bind(lfd, (sockaddr *)&this->localaddr, sizeof(this->localaddr));
}

Epoll::~Epoll()
{
}

int Epoll::init_addr(char *ip, int port)
{
    try
    {
        memset(&this->localaddr, 0, sizeof(this->localaddr));
        this->localaddr.sin_family = AF_INET;
        this->localaddr.sin_addr.s_addr = inet_addr(ip);
        this->localaddr.sin_port = htons(port);
    }
    catch (...)
    {
        return -1;
    }
    return 0;
}

int Epoll::start_listen()
{

    if (-1 == listen(this->lfd, 128))
    {
        perror("listen error");
        return 0;
    }
    return 1;
}

int Epoll::run()
{
    this->epfd = epoll_create(3000);
    this->levent.events = EPOLLIN | EPOLLET;
    this->levent.data.fd = this->lfd;
    epoll_ctl(this->epfd, EPOLL_CTL_ADD, this->lfd, &this->levent);

    for (;;)
    {
        int ret = epoll_wait(this->epfd, this->client_events, sizeof(this->client_events), -1);

        for (int i = 0; i < ret; i++)
        {
            sockaddr_in client_addr = {0};
            socklen_t client_length = sizeof(client_addr);
            if (this->client_events[i].data.fd == this->lfd)
            {
                int client_fd = accept(this->client_events[i].data.fd, (sockaddr *)&client_addr, &client_length);
                int flag = fcntl(client_fd, F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(client_fd, F_SETFL, flag);
                epoll_event cevent = {0};
                cevent.events = EPOLLIN | EPOLLET;
                cevent.data.fd = client_fd;
                epoll_ctl(this->epfd, EPOLL_CTL_ADD, client_fd, &cevent);
                char IP[64] = {0};
                inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, IP, sizeof(IP));
                cout << "ip: " << IP << " PORT: " << ntohs(client_addr.sin_port) << endl;
            }
            else
            {
                cout << "data accept" << endl;
                char buff[8] = {0};
                int len;
                for (; 0 < (len = recv(this->client_events[i].data.fd, buff, sizeof(buff), 0));)
                {
                    write(1, buff, sizeof(buff));
                    
                    memset(buff, 0, sizeof(buff));
                }
                if (len == -1)
                {
                    if (errno == EAGAIN)
                    {
                        cout << "recv over" << endl;
                        send(this->client_events[i].data.fd, "已接受\n", sizeof("已接受\n"), 0);
                    }
                    else
                    {
                        perror("recv error:");
                        exit(1);
                    }
                }
                if (len == 0)
                {
                    close(this->client_events[i].data.fd);
                    cout << "链接 中断" << endl;
                    epoll_ctl(this->epfd, EPOLL_CTL_DEL, this->client_events[i].data.fd, NULL);
                }
                memset(this->client_events, 0, sizeof(this->client_events));
            }
        }
    }
}

void test()
{
    char ip[64] = {0};
    strcat(ip, "127.0.0.1");
    auto test = make_shared<Epoll>(ip, 8888);
    test->start_listen();
    test->run();
}

int main()
{
    test();
}