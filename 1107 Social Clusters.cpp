//并查集 加 路径压缩   题意是将有共同爱好的人设为一个集合 a 和 b有共同爱好 b和c有共同爱好 则abc为一个集合，且ac之间可以没有共同爱好
#include <iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<algorithm>
#define INFINITE 65535
using namespace std;
class pta1107
{
    short N;
    vector<short> data;
    short FindRoot(short index)//需找节点的根节点
    {
        short root = index;
        if(data[index]>0)
        {
            root = FindRoot(data[index]);//路径压缩
            data[index] = root;
        }
        return root;
    }
    void Add(short target, short source)//将两个节点合成一个集合
    {
        short indexOfSrc = FindRoot(source);
        short indexOfTar = FindRoot(target);
        if (data[indexOfSrc] < data[indexOfTar])
        {
            data[indexOfSrc] += data[indexOfTar];
            data[indexOfTar] = indexOfSrc;
        }
        else
        {
            data[indexOfTar] += data[indexOfSrc];
            data[indexOfSrc] = indexOfTar;
        }
    }
public:
    pta1107()
    {
        scanf("%hd", &N);
        short K,root;
        short firstHobby,otherHobby;
        data.resize(1001, 0);
        for (short i = 0; i < N; ++i)
        {
            scanf("%hd:", &K);
            scanf("%hd", &firstHobby);
            root = FindRoot(firstHobby);
            --data[root];
            for (short j = 1; j < K; ++j)
            {
                scanf("%hd", &otherHobby);
                Add(firstHobby, otherHobby);
            }
        }
    }
    void Solve()
    {
        sort(data.begin(), data.end());
        short cnt = 0;
        for (auto i : data)
        {
            if (i >= 0)
                break;
            ++cnt;
        }
        printf("%hd\n%hd", cnt,-data[0]);
        for (short i = 1; i < cnt; ++i)
        {
            printf(" %hd", -data[i]);
        }
    }
    ~pta1107()
    {

    }
};
int main()
{
    pta1107* question = (pta1107*)malloc(sizeof(pta1107));
    new(question) pta1107();
    question->Solve();
    question->~pta1107();
    free(question);
}
