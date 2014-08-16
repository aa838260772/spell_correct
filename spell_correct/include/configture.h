#ifndef _CONFIGTURE_H_
#define _CONFIGTURE_H_

#include "MutexLock.h"
#include "EchoServer.h"
#include <fstream>
#include <string>
#include <iostream>

class configture 
{
    public:
        static configture *getInstance() 
        {
            MutexLockGuard(mutex_);
            if(pinstance == NULL)
                pinstance = new configture;
            return pinstance;
        }

       void start(const std::string &);
    private:
        configture()
        {
        };
        static configture *pinstance;
        mutable MutexLock mutex_;
        static std::string filename_;
        std::unique_ptr<EchoServer> server_;
};
#endif /*CONFIG_H*/ 
