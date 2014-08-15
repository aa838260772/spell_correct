#include "configture.h"
#include <sstream>
#include <stdio.h>
using namespace std;

 configture *configture::pinstance = NULL;
 std::string configture::filename_ = "config.txt";

static void process(string &);

void configture::start(const string &filename)
{
    filename_ = filename;
    int port;
    int val, interval;
    string libcnfile, cachefile;
    string libenfile;

    ifstream is(filename_);

    string line;

    string portstring;
    getline(is, line);//从第一行读出端口号
    process(line);
    istringstream istream(line);
    istream >> portstring;
    istream >> port;

    string valstring, intervalstring;//读出时钟间隔设置
    getline(is, line);
    process(line);
    istringstream istream1(line);
    istream1 >> valstring;
    istream1 >> val;
    istream1 >> intervalstring;
    istream1 >> interval;

    string libenstring;//读出英文词典位置
    getline(is, line);
    process(line);
    istringstream istream2(line);
    istream2 >> libenstring;
    istream2 >> libenfile;

    string libcnstring;//读出中文词典位置
    getline(is, line);
    process(line);
    istringstream istream3(line);
    istream3 >> libcnstring;
    istream3 >> libcnfile;

    string cachestring;//读出cache
    getline(is, line);
    process(line);
    istringstream istream4(line);
    istream4 >> cachestring;
    istream4 >> cachefile;

    server_.reset( new EchoServer(InetAddress(port)));
    server_->settime(val, interval);
    server_->start(libenfile, libcnfile, cachefile);
}

void process(string &s)
{
    size_t i;
    for(i = 0; i < s.size(); ++i)
    {
        if(s[i]== '='|| s[i] == ';' )
            s[i] = ' ';  
    }
}

