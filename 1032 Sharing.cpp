#include<iostream>
#include<unordered_map>
#include<cstdio>
using namespace std;
#define INFINITE 65535
typedef unsigned int uint;
typedef int Address ;
struct info
{
        uint visitedTimes = 0;
        Address next = 0;
};
class pta1032
{
        uint N;
        Address addressOfFirstWord;
        Address addressOfsecondWord;
        unordered_map<Address,info> record;
        Address targetAdr;
public:
        pta1032(istream &in):targetAdr(-1)
        {
                Address temAdr,nextAdr;
                char data;
                in >> addressOfFirstWord >> addressOfsecondWord >> N;
                for(uint i = 0 ; i < N; ++i )
                {
                        in >> temAdr >> data >> nextAdr ;
                        record[ temAdr ].next = nextAdr ;
                }
        }
        void Solve()
        {
                Address curAdr = addressOfFirstWord;
                while(curAdr != -1)
                {
                        record[curAdr].visitedTimes++;
                        curAdr = record[curAdr].next;
                }
                curAdr = addressOfsecondWord;
                while(curAdr != -1)
                {
                        if(++(record[curAdr].visitedTimes)==2)
                        {
                                targetAdr=curAdr;
                                break;
                        }
                        curAdr = record[curAdr].next;
                }
        }
        void Print()
        {
                if(targetAdr==-1)
                        printf("%d",-1);
                else
                        printf("%05d",targetAdr);
        }
};
int main()
{
        pta1032 question(cin);
        question.Solve();
        question.Print();
        return 0;
}
