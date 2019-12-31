#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdlib.h>

class Select
{
private:
    int fd;
    int max_fd;
    fd_set readfds;
    sockaddr_in addr;
    sockaddr_in client_addr;
    socklen_t client_len;

public:
    Select(int port);
    ~Select();
    bool start_listen();
    void select_accpet();
};

Select::Select(int port)
{
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    this->max_fd = this->fd;
    memset(&this->addr, 0, sizeof(this->addr));
    this->addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    //绑定本地ip端口
    this->client_len = sizeof(this->client_addr);
    bind(this->fd, (sockaddr *)&this->addr, sizeof(this->addr));
    FD_ZERO(&(this->readfds));
    FD_SET(this->fd, &(this->readfds));
}

bool Select::start_listen()
{
    if (0 != listen(this->fd, 128))
        return false;
    else
        return true;
}

void Select::select_accpet()
{
    for (;;)
    {
        fd_set _readfds = this->readfds;

        int ret = select(this->max_fd + 1, &_readfds, NULL, NULL, NULL);

        if (ret == -1)
        {
            perror("select error");
            exit(1);
        }

        if (FD_ISSET(this->fd, &_readfds))
        {
            int client_fd = accept(this->fd, (sockaddr *)&(this->client_addr), &this->client_len);
            if (client_fd == -1)
            {
                perror("accept error");
                exit(1);
            }
            char IP[64] = {0};
            std::cout << "IP: " << inet_ntop(AF_INET, &this->client_addr.sin_addr.s_addr, IP, sizeof(IP)) << " PORT: " << ntohs(client_addr.sin_port) << "已连接" << std::endl;
            FD_SET(client_fd, &(this->readfds));
            this->max_fd = this->max_fd < client_fd ? client_fd : this->max_fd;
        }

        for (int i = this->fd + 1; i <= this->max_fd; ++i)
        {

            if (FD_ISSET(i, &_readfds))
            {
                char buff[2048] = {0};
                int len = recv(i, &buff, sizeof(buff), 0);
                if (len == -1)
                {
                    perror("read error");
                }
                if (len == 0)
                {
                    std::cout << "已断开链接" << std::endl;
                    close(i);
                    FD_CLR(i, &readfds);
                }
                else
                {
                    std::cout << buff;
                    memset(buff, 0, sizeof(buff));
                    send(i, "已接收\n", sizeof("已接收\n"), 0);
                }
            }
        }
    }
}

Select::~Select()
{
}

int main(int argc, char *argv[])
{
    Select *sel = new Select(atoi(argv[1]));
    if (sel->start_listen())
        sel->select_accpet();
    else
        std::cout << "error" << std::endl;

    delete sel;
}
