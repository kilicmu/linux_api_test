#include <iostream>
#include <unistd.h>
#include <cstring>
#include<sys/stat.h>
#include<sys/types.h>
using namespace std;

int main()
{
    char rootpath[64] = {0};
    strcat(rootpath, "./");
    if (-1 == chroot(rootpath))
    {
        perror("chroot error");
    }
    char now_path[64] = {0};
    getcwd(now_path, sizeof(now_path));
    cout << now_path;

    access("20-epoll", F_OK);
    
    int ret = chmod("/", S_IRWXO|S_IRWXG|S_IRWXU);
    cout << ret << endl;
    if (-1 == execlp("./20-epoll", NULL))
    {
        perror("execl error");
    }
}