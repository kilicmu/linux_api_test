#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        return -1;
    }

    struct stat sb;
    stat(argv[1], &sb);
    return 0;
}