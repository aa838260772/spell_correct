#ifndef ECHO_TCP_SERVER_H
#define ECHO_TCP_SERVER_H 

#include <echo/TcpServer.h>
#include <echo/ThreadPool.h>
#include <echo/NonCopyable.h>
#include <echo/TimerThread.h>
#include "textquery.h"
#include <fstream>
#include <iostream>

class EchoServer : private NonCopyable
{
    public:
        EchoServer(const InetAddress &addr);
        void start(const std::string&, 
                   const std::string&,
                   const std::string&);
        void settime(int val, int interval);
        void writefile();
    private:
        void onConnection(const TcpConnectionPtr &conn);
        void onMessage(const TcpConnectionPtr &conn);
        void onClose(const TcpConnectionPtr &conn);
        void compute(const std::string &, 
                     const TcpConnectionPtr &);

        TcpServer server_;
        ThreadPool pool_;
        textquery text_;
        TimerThread timerthread_;
};


#endif  /*ECHO_TCP_SERVER_H*/
