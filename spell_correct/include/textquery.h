#ifndef _TEXT_QUERY_H_
#define _TEXT_QUERY_H_
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include "mycache.h"
#include <echo/MutexLock.h>
#include "CacheManage.h"
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
typedef struct qelem
{
    int x;//编辑距离
    int y;//频数
    std::string s;//字符串 
    bool operator<(const qelem &other )const
    {
    if(x != other.x)
        return x > other.x;
    return y < other.y;
    }
}qelem;

/*struct cmp
{
    bool operator()(const qelem &lhs, const qelem &rhs)
    {
        if(lhs.x < rhs.x)
            return lhs.x > rhs.x;
            return lhs.y < rhs.y;
    }
};//优先级队列中的比较函数
*/
class textquery
{
    public:
        textquery()
          :index(27)
        {
        }
        void start(const std::string &,//英文词典
                   const std::string &, //中文词典
                   const std::string &,//cache文件
                   int);
        typedef std::vector<std::string>::size_type line_no;
        std::string  run_query(const std::string &);
        void read_file();
        void writefile();
    private:
        void build_map(std::string &);
//        std::map<std::string, int>  index[26];
        std::string query_index_cn(const std::string &);
        std::string query_index_en(const std::string &);
        std::vector< std::map<std::string, int> > index;
        std::map< std::string, int > word_map;
        std::map<std::string, std::string> cache;
        std::string libfileen_;
        std::string libfilecn_;
        std::string cachefile_;
        mycache cache_;//负责将cache写入磁盘
        CacheManage cachemanage_;        
        int cachesize_;
        MutexLock libmutex_;
};

#endif /*TEXT_QUERY_H*/ 
