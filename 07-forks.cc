#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i = 0;
    for (; i < 5; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
            break;
        }
    sleep(i);
    if (i < 5)
    {
        std::cout << "this is child   pid=" << getpid() << "ppid = " << getppid() << std::endl;
    }
    else
    {
        std::cout << "this is father   pid=" << getpid() << "ppid = " << getppid() << std::endl;
    }
    return 0;
}