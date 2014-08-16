#ifndef _CACHEMANAGE_H_
#define _CACHEMANAGE_H_

#include "mycache.h"
#include <vector>
#include "MutexLock.h"

class CacheManage
{
    public:
         void  cachestart(int );
         std::string query(const std::string &);
         void write_to_cache(mycache &);
    private:
      size_t  cacheSize_;//动态分配的 
      std::vector<mycache> cachevec; 
      MutexLock mutex_;
};

#endif /*CACHEMANAGE_H*/ 
