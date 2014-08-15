#include "EchoServer.h"
#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
using namespace placeholders;

EchoServer::EchoServer(const InetAddress &addr)
    :server_(addr),
    pool_(1000, 4)
{
    server_.setConnection(bind(&EchoServer::onConnection, 
                            this, 
                            _1));
    server_.setMessage(bind(&EchoServer::onMessage, 
                        this, 
                        _1));
    server_.setClose(bind(&EchoServer::onClose, 
                        this, 
                        _1));
}

void EchoServer::start(const string &libenfile, 
                       const string &libcnfile,
                        const string  &cachefile)
{
    text_.start(libenfile, libcnfile, cachefile, 4);
    text_.read_file();
    text_.writefile();
    pool_.start();
    server_.start();
}

void EchoServer::settime(int val, int interval)
{
    timerthread_.setTimer(val, interval);
    timerthread_.setTimerCallback(bind(&textquery::writefile,
                                       &text_));
    timerthread_.startTimerThread();
    //timerthread_.cancelTimerThread();
}

void EchoServer::onConnection(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << endl;
    conn->send("Hello, welcome to Echo Server!!!\r\n");
}

void EchoServer::onMessage(const TcpConnectionPtr &conn)
{
    string s(conn->receive());
    pool_.addTask(bind(&EchoServer::compute, this, s, conn));
}

//把计算任务和tcp回发做成一个函数，交给线程池
void EchoServer::compute(const std::string &word, const TcpConnectionPtr &conn)
{
    string s;
    s = text_.run_query(word);
    conn->send(s);
}

void EchoServer::onClose(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port: "
        << conn->getPeerAddr().toPort() << " close" << endl;
    conn->shutdown();
}

