#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <iostream>

int main()
{
    int i = 0;
    int stat = 0;
    for (; i < 5; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
            break;
    }
    if (i == 5)
    {
        while (1)
        {
            pid_t wpid = waitpid(-1, NULL, WNOHANG);
            if (wpid == -1)
                break;
            if (wpid > 0)
                std::cout << "process:" << wpid << "is killed" << std::endl;
        }
    }
    while (1)
    {

        std::cout << "running" << std::endl;
    }

    if (i < 5)
    {
        sleep(i);
        std::cout << getpid() << "created" << std::endl;
    }
}