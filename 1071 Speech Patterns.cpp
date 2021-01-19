#include<cstdio>
#include<iostream>
#include<cctype>
#include<map>
#include<string>
using namespace std;
class pta1071
{
    string sentence;
    map<string, int> words;
public:
    pta1071()
    {
        getline(cin, sentence);
    }
    void solve()
    {
        string tem;
        for (auto elem : sentence)
        {
            if (isalnum(elem))
            {
                tem += tolower(elem);
            }
            else
            {
                if (tem.size())
                {
                    if (words.find(tem) != words.end())
                    {
                        words[tem]++;
                    }
                    else
                    {
                        words[tem] = 1;
                    }
                }
                tem = "";
            }
        }
        if (isalnum(sentence[sentence.size() - 1]))
        {
            words[tem]++;
        }
    }
    void print()
    {
        int maxCnt = 0;
        string answer;
        for (auto beg = words.begin(); beg != words.end(); ++beg)
        {
            if (maxCnt < beg->second)
            {
                maxCnt = beg->second;
                answer = beg->first;
            }
        }
        printf("%s %d", answer.c_str(), maxCnt);
    }
    ~pta1071() {}
};
int main()
{
    pta1071* ptr = (pta1071 *)malloc(sizeof(pta1071));
    new(ptr) pta1071();
    ptr->solve();
    ptr->print();
}
