#include "textquery.h"
#include <iostream>
#include "configture.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main(int argc, const char *argv[])
{
    int pid;
    if((pid = fork()) == 0)
    {
    int fd = open("../log/log.txt", O_WRONLY | O_APPEND);
    dup2(fd, 1);
    configture *config = configture::getInstance();
    config->start("/home/syswj/document/spell_correct4/config/config.txt");
    }

    return 0;
}
