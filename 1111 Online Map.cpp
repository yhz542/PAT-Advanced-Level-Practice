// 没什么好说的，两次dijkstra算法计算路径最短和时间最短。
#pragma warning(disable:4996)
#include <iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<algorithm>
#define INFINITE 65535
using namespace std;
class pta1111
{
    enum TYPE
    {
        Shortest,
        Fastest
    };
    struct WayData
    {
        int length = INFINITE;
        int time = INFINITE;
    };
    short N,source,destination;
    int M;
    vector<vector<WayData>> map;
    vector<int> shortestPath,       fastestPath     , passPath;
    vector<short> indexOfShortest, indexOfFastest;
    vector<short> predShortest,      predFastest;
    short FindMin(TYPE type)
    {
        vector<short> &index = (type == Shortest ? indexOfShortest : indexOfFastest);
        vector<int> &path  = (type == Shortest ? shortestPath : fastestPath);
        short min = index[0], mindex=0;
        short cur;
        for (size_t i = 1; i < index.size(); ++i)
        {
            cur = index[i];
            if (path[min] > path[cur])
            {
                min = cur;
                mindex = i;
            }
        }
        index[mindex] = index[index.size() - 1];
        index.pop_back();
        return min;
    }
    void output(TYPE type, short index)
    {
        vector<short>& pred = (type == Shortest ? predShortest : predFastest);
        if (index != source)
        {
            output(type, pred[index]);
        }
        else
        {
            return;
        }
        printf(" -> %d", index);
    }
    void Dijkstra(TYPE type)
    {
        vector<short>&pred = (type == Shortest ? predShortest : predFastest);
        short curNode = source;
        while (curNode != destination)
        {
            curNode = FindMin(type);
            for (short adjNode = 0; adjNode < N; ++adjNode)
            {
                if (type == Shortest)
                {
                    if (shortestPath[adjNode] > shortestPath[curNode] + map[curNode][adjNode].length)
                    {
                        shortestPath[adjNode] = shortestPath[curNode] + map[curNode][adjNode].length;
                        fastestPath[adjNode] = fastestPath[curNode] + map[curNode][adjNode].time;
                        pred[adjNode] = curNode;
                    }
                    else if (shortestPath[adjNode] == shortestPath[curNode] + map[curNode][adjNode].length)
                    {
                        if (fastestPath[adjNode] > fastestPath[curNode] + map[curNode][adjNode].time)//如果路径长度相同，选最快的
                        {
                            fastestPath[adjNode] = fastestPath[curNode] + map[curNode][adjNode].time;
                            pred[adjNode] = curNode;
                        }
                    }
                }
                else
                {
                    if (fastestPath[adjNode] > fastestPath[curNode] + map[curNode][adjNode].time)
                    {
                        fastestPath[adjNode] = fastestPath[curNode] + map[curNode][adjNode].time;
                        passPath[adjNode] = passPath[curNode] + 1;
                        pred[adjNode] = curNode;
                    }
                    else if (fastestPath[adjNode] == fastestPath[curNode] + map[curNode][adjNode].time)//如果时间相同，选经过路口最少的
                    {
                        if (passPath[adjNode] > passPath[curNode] + 1)
                        {
                            passPath[adjNode] = passPath[curNode] + 1;
                            pred[adjNode] = curNode;
                        }
                    }
                }
            }
        }
    }
public:
    pta1111()
    {
        short V1, V2;
        short one_way;
        int length,time;
        scanf("%hd %d", &N, &M);
        map.resize(N, vector<WayData>(N));
        shortestPath.resize(N, INFINITE);
        fastestPath.resize(N, INFINITE);
        passPath.resize(N, INFINITE);
        indexOfFastest.reserve(N);
        indexOfShortest.reserve(N);
        predFastest.resize(N);
        predShortest.resize(N);
        for (int i = 0; i < M; ++i)
        {
            scanf("%hd %hd %hd %d %d",&V1,&V2,&one_way,&length,&time);
            if (one_way)
            {
                map[V1][V2].length = length;
                map[V1][V2].time    = time;
            }
            else
            {
                map[V1][V2].length = map[V2][V1].length = length;
                map[V1][V2].time    = map[V2][V1].time    = time;
            }
        }
        scanf("%hd %hd", &source, &destination);
    }
    void Solve()
    {
        shortestPath[source] = fastestPath[source] = passPath[source] =  0;
        for (short i = 0; i < N; ++i)
        {
            indexOfFastest.push_back(i);
            indexOfShortest.push_back(i);
            map[i][i].length = map[i][i].time = 0;
        }
        Dijkstra(Shortest);
        Dijkstra(Fastest);
    }
    void Print()
    {
        bool equal = true;
        short i = destination;
        while (predShortest[i] != source)
        {
            if (predShortest[i] != predFastest[i])
            {
                equal = false;
                break;
            }
            i = predShortest[i];
        }
        printf("Distance = %d", shortestPath[destination]);
        if (equal)
        {
            printf("; Time = %d", fastestPath[destination]);
        }
        else
        {
            printf(": %d", source);
            output(Shortest, destination);
            printf("\nTime = %d", fastestPath[destination]);
        }
        printf(": %d", source);
        output(Fastest, destination);
    }
    ~pta1111()
    {

    }
};
int main()
{
    pta1111* question = (pta1111*)malloc(sizeof(pta1111));
    new(question) pta1111();
    question->Solve();
    question->Print();
    question->~pta1111();
    free(question);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
