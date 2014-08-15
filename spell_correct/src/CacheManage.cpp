#include "CacheManage.h"
#include <iostream>
using namespace std;

void CacheManage::cachestart(int cacheSize)
{
    cacheSize_ = cacheSize;
    for(size_t i = 0; i < cacheSize_; i++)
    {
        mycache ch;
        cachevec.push_back(ch);
    }
}

string  CacheManage::query(const string &word)
{
    size_t i;
    for(i = 0; i < cacheSize_; i++)
    {
        if(cachevec[i].isbusy() == false)
        {
            break;
        }
    }
    if(i != cacheSize_)
    {
        MutexLockGuard(&mutex_);
        return cachevec[i].query_cache(word);
    }
    else
        return string("cache are busy\r\n");
}

void CacheManage::write_to_cache(mycache &cache)
{
    size_t i;
    //        cout << "write to cachevec[i]" << endl;
    MutexLockGuard(&mutex_);
    for(i = 0; i < cacheSize_; ++i)
    {
        if(cachevec[i].isbusy() == false)
        {
            cachevec[i].clear_cache();
            cache.write_cache_to_cache(cachevec[i]);
        }
    }
}
