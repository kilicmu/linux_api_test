#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <cstring>

int count = 0;

void dir(char *dirname)
{
    DIR *dirp = nullptr;
    dirp = opendir(dirname);
    for (struct dirent *dirt = readdir(dirp); dirt != NULL; dirt = readdir(dirp))
    {
        if (dirt->d_type == DT_REG)
        {
            count++;
        }
        if (dirt->d_type == DT_DIR && strcmp(dirt->d_name, ".") !=0 &&strcmp(dirt->d_name, "..") !=0)
        {
            char nowpath[512] = {0};
            sprintf(nowpath, "%s/%s", dirname, dirt->d_name);
            std::cout << nowpath << std::endl;
            dir(nowpath);
        }
    }
}

int main(int argc, char *argv[])
{
    dir(argv[1]);
    std::cout << count << std::endl;
    return 0;
}