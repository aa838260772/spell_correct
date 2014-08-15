#include "mycache.h"
#include <fstream>
#include <sstream>
#include <assert.h>
using namespace std;
using std::unordered_map;
void mycache::read_cache(const string &cachefile, int size)
{
    cachesize(size);
    ifstream is(cachefile.c_str());
    string line;
    while(getline(is, line) > 0)
    {
        string word1;
        string word2;
        istringstream sstream(line);
        sstream >> word1;
        sstream >> word2;
        lru_put(word1);
        cachemap_[word1] = word2;
    }
    is.close();
}

string mycache::query_cache(const string &word)
{

    if(isbusy() == true)
        return "";
    isbusy_ = true;
    unordered_map<string, string>::const_iterator it;
    //    for(it = cachemap_.begin(); it != cachemap_.end(); it++)
    //   cout << it->first <<" " << it->second << endl;
    it = cachemap_.find(word);
    isbusy_ = false;
    if(it != cachemap_.end())
    {
        cout << word << " " << it->second << endl;
        return it->second;
    }
    else
        return "";
}

void mycache::add_cache(const string &key, const string &value)
{
    if(isbusy() == true)
        return;
    isbusy_ = true;
    lru_put(key);
    cachemap_[key ] = value;
    isbusy_ = false;
}

void mycache::write_to_file(const string &cachefile)//把cache内容写进文件
{
    if(isbusy() == true)
        return;
    isbusy_ = true;
    ofstream os(cachefile);
    unordered_map<string, string>::iterator it;
    for(it = cachemap_.begin(); it != cachemap_.end(); it++)
    {
        os << it->first << " " << it->second << "\r\n";
     
    }
    os.close();
    isbusy_ = false;
}

void mycache::write_cache_to_cache(mycache &rhs)
{
    isbusy_ = true;
    unordered_map<string, string>::iterator it;
    for(it = cachemap_.begin(); it != cachemap_.end(); it++)
    {
        rhs.add_cache(it->first, it->second);
    }
    isbusy_ = false;
}

void mycache::lru_put(const string &s)
{
    unordered_map<string, string>::iterator it;
    it = cachemap_.find(s);
    if(it != cachemap_.end())
    {
        list_.remove(s);
    }else
    {
     if(list_.size() >= size_)
     {
         cachemap_.erase(*(--list_.end()));
         list_.erase( --list_.end());
     }
    }
        list_.push_front(s);
}

