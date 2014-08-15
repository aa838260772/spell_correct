#include "textquery.h"
#include <sstream>
#include <ctype.h>
#include "processstring.h"
using namespace std;
using namespace processstring;

void textquery::start(const string &libfileen, 
        const string &libfilecn, 
        const string &cachefile,
        int cachesize) 
{
    libfileen_ = libfileen;
    libfilecn_ = libfilecn;
    cachefile_ = cachefile;
    read_file();
    cachesize_ = cachesize;
}

void textquery::read_file()
{
    string word;
    ifstream is(libfileen_);//载入英文词库
    while(getline(is, word) > 0)
    {
        build_map(word);
    }//把每行的内容读入vector
    is.close();

    ifstream is1(libfilecn_);//载入中文词库
    while(getline(is1, word) > 0)
    {
        build_map(word);
    }
    is1.close();

    cache_.read_cache(cachefile_, 5);//载入cache词库
    cachemanage_.cachestart(cachesize_);
    cachemanage_.write_to_cache(cache_);
}

void textquery::build_map(string &line)
{
    string word;
    int frequen;
    istringstream sstream(line);
    sstream >> word;
    sstream >>frequen; 
    word_map[word] = frequen;
    if( !( word[0] & (1 << 7) ) )    
    {
        for(int i = 0; i < 26; ++i) 
        {
            if(is_in_string(i+97, word))
                index[i][word] = frequen;
        }
    }
    else
        index[26][word] = frequen;
    //  cout << word << " " << frequen << endl;
}

string textquery::run_query(const string& s) 
{//记住此时要用const迭代器，否则会出现错误,以及返回的这个set类型
    string word = s;
    word.erase(word.size()-2, 2);
    //   std::priority_queue<qelem, std::vector<qelem>, cmp>que;
    string ret;
    ret = cachemanage_.query(word);
    if(ret.size() > 0)     
    { 
        if(ret != string("cache are busy\r\n"))
        {
            MutexLockGuard(libmutex_);
            ++word_map[ret];
            return "cache:" + ret + "\r\n";
        }
        else
            return ret;
    }
    cout << word << endl;
    if(word[0] & (1 << 7))
        ret = query_index_cn(word);
    else
        ret = query_index_en(word);
    return ret;
}

void textquery::writefile()
{
    /*  ofstream os(libfile_);
        map<string, int>::iterator it;
        for(it = word_map.begin(); it != word_map.end(); it++)
        {
        os << it->first << " " << it->second << "\r\n";
        }
        os.close();
        */
    cachemanage_.write_to_cache(cache_);
    cache_.write_to_file(cachefile_);
}

string textquery::query_index_en(const string &word)
{
    priority_queue<qelem>que;
    map<string, int>::const_iterator it;
    qelem q;
    for(int i = 0; i < 26; ++i)//在索引查找
    {
        it = index[i].find(word);
        if(it != index[i].end())
        {
            MutexLockGuard(libmutex_);
            ++word_map[word];
            return ("exist:" + it->first + "\r\n"); 
        }else if(is_in_string(i+97, word)) //
        {
            for( it = index[i].begin(); 
                    it != index[i].end(); 
                    it++)
            {
                int tmp;
                tmp = Edit_Distenceen(word, it->first);
                if(tmp < 3)
                {
                    q.x = tmp;
                    q.y = it->second;
                    q.s = it->first;
                    que.push(q);
                }
            }
        }
    }

    if(!que.empty())
    {
        MutexLockGuard(libmutex_);
        cache_.add_cache(word, que.top().s);
        ++word_map[que.top().s];
        return ("the nearest :" + que.top().s + "\r\n");
    }
    else
        return string("try other word\r\n");
}

string textquery::query_index_cn(const string &word)
{
    priority_queue<qelem> que;
    map<string, int>::const_iterator it;
    qelem q;
    int i = 26;
    it = index[i].find(word);
    if(it != index[i].end())
    {
        MutexLockGuard(libmutex_);
        ++word_map[word];
        return ("exist:" + it->first + "\r\n"); 
    }
    for(it = index[i].begin(); 
            it != index[i].end(); 
            it++)
    {
        int tmp;
        tmp = Edit_Distencecn(word, it->first);
        if(tmp < 3)
        {
            q.x = tmp;
            q.y = it->second;
            q.s = it->first;
            que.push(q);
        }
    }
    if(!que.empty())
    {
        MutexLockGuard(libmutex_);
        cache_.add_cache(word, que.top().s);
        ++word_map[que.top().s];
        return ("the nearest :" + que.top().s + "\r\n");
    }
    else
        return string("try other word\r\n");
}
