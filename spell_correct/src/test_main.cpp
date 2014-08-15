#include "textquery.h"
#include <iostream>
#include "configture.h"
using namespace std;

int main(int argc, const char *argv[])
{
    configture *config = configture::getInstance();
    config->start("/home/syswj/document/spell_correct4/config/config.txt");
    return 0;
}
