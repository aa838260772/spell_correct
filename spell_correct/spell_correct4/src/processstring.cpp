#include "processstring.h"
using namespace std;

namespace processstring{
    int is_in_string(char c, const string &s)
    {
        size_t i;
        for(i = 0; i < s.size(); i++)
        {
            if(c == s[i])
                break;
        }
        if(i != s.size())
            return 1;
        else
            return 0;
    }

    int Edit_Distenceen(const string &s1, 
                        const string &s2)
    {
        int cnt[s1.size() + 1 ][s2.size() + 1] ;
        size_t i, j;
        for(i = 0; i <= s1.size(); i++)
            for(j = 0; j <= s2.size(); j++)
            {
                if(i == 0)
                {
                    cnt[i][j] = j;
                    continue;
                }
                if(j == 0)
                {
                    cnt[i][j] = i;
                    continue;
                }
                if(s1[i-1] == s2[j-1])
                {
                    cnt[i][j] = cnt[i-1][j-1];
                }
                else
                {
                    int t1 = cnt[i-1][j-1] + 1;
                    int t2 = cnt[i][j-1] + 1;
                    int t3 = cnt[i-1][j] + 1;
                    cnt[i][j] = (t1 <= (t2 <= t3 ? t2 : t3 ) ? 
                            t1 : (t2 <= t3 ? t2 : t3));
                }
            }
        return cnt[s1.size()][s2.size()];
    }
    //把每个汉字转化成一个uint32_t无符号32位整型    
    static void str_to_vec(const string &, vector<uint32_t> &);
    static int getlen(unsigned char c)
    {
        int cnt = 0;
        while(c & (1 << (7-cnt)))
            ++cnt;
        return cnt;
    }//返回前面有多少个连续的1，汉字的utf-8含3个字节1110xxxx  10xxxxxx 10xxxxxx

    int Edit_Distencecn(const string &str1, 
            const string &str2)
    {
        vector<uint32_t> s1;
        vector<uint32_t> s2;
            str_to_vec(str1, s1);
        str_to_vec(str2, s2);

        int cnt[s1.size() + 1 ][s2.size() + 1] ;
        size_t i, j;
        for(i = 0; i <= s1.size(); i++)
            for(j = 0; j <= s2.size(); j++)
            {
                if(i == 0)
                {
                    cnt[i][j] = j;
                    continue;
                }
                if(j == 0)
                {
                    cnt[i][j] = i;
                    continue;
                }
                if(s1[i-1] == s2[j-1])
                {
                    cnt[i][j] = cnt[i-1][j-1];
                }
                else
                {
                    int t1 = cnt[i-1][j-1] + 1;
                    int t2 = cnt[i][j-1] + 1;
                    int t3 = cnt[i-1][j] + 1;
                    cnt[i][j] = (t1 <= (t2 <= t3 ? t2 : t3 ) ? 
                            t1 : (t2 <= t3 ? t2 : t3));
                }
            }
        return cnt[s1.size()][s2.size()];
    }

    void str_to_vec(const string &s, vector<uint32_t> &vec)
    {
        vec.clear();
        for(string::size_type ix = 0; ix != s.size(); ix++)
        {
            int len = getlen(s[ix]);
            if(len > 1)
            {
                uint32_t t = (unsigned char)s[ix];
                while(len > 1)
                {
                    len--;
                    t = (t << 8) + (unsigned char)s[++ix];
                }
                vec.push_back(t);
            }
        }
    }
}
