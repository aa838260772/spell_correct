#ifndef _CACHE_H_
#define _CACHE_H_

#include <map>
#include <string>
#include <iostream>
#include <unordered_map>
#include <list>

class mycache
{
    public:
         mycache()
             :isbusy_(false)
         {}
        void read_cache(const std::string&, int);
        std::string query_cache(const std::string&);
        void write_to_file(const std::string&);
        void add_cache(const std::string&, const std::string&);
        void cachesize(int size )
        {
        size_ = size;
        }
        void write_cache_to_cache(mycache &);
        bool isbusy()
        {
        return isbusy_;
        }
        void clear_cache()
        {
        cachemap_.clear();
        }
        void lru_put(const std::string &);
    private:
        std::unordered_map<std::string, std::string> cachemap_;
        bool isbusy_;
        std::list<std::string> list_;
        int size_;//链表长度
};

#endif /*CACHE_H*/ 
