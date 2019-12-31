#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

void listen_cb(struct evconnlistener *listener,
               evutil_socket_t fd,
               struct sockaddr *addr,
               int socklen, void *ptr)
{
    bufferevent *bev = bufferevent_socket_new((event_base *)ptr, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, [](struct bufferevent *bev, void *ctx) {
        char buff[1024] = {0};
        size_t len = bufferevent_read(bev, buff, sizeof(buff));
        if(len <=0){
            if(len == 0){
                
            }
            if(len < -1){
                perror("bufferevent_read");
            }
        }
        cout << buff;
        bufferevent_write(bev, "已接受", sizeof("已接受")); }, [](struct bufferevent *bev, void *ctx) { cout << "已发送回述数据" << endl; }, [](struct bufferevent *bev, short what, void *ctx) {
        if(what & BEV_EVENT_EOF){
            cout << "connect close" << endl;
        }
        if(what & BEV_EVENT_ERROR){
            cout << "error" << endl;
        }

        bufferevent_free(bev); }, NULL);
    bufferevent_enable(bev, EV_READ);
}

int main()
{
    event_base *base = event_base_new();
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    bufferevent *sockevent = bufferevent_socket_new(base, sfd, BEV_OPT_CLOSE_ON_FREE);
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8888);

    struct evconnlistener *listener = NULL;
    listener = evconnlistener_new_bind(base, listen_cb, (void *)base, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1, (sockaddr *)&servaddr, sizeof(servaddr));

    event_base_dispatch(base);

    event_base_free(base);
    evconnlistener_free(listener);
    return 0;
}