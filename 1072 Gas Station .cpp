#include <iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<cstdarg>
#include<vector>
#include<set>
#include<algorithm>
#define INFINITE 65535
using namespace std;
class pta1072
{
    int N;
    int M;
    int K;
    int Ds;
    int ans;
    float averageDistance;
    float minDistance;
    vector<vector<int>> distance;
    vector<int> shortest;
    set<int> housePlaces;
    void initialize(void)
    {
        fill(shortest.begin(), shortest.end(), INFINITE);
        for (int i = 0; i < N; ++i)
        {
            housePlaces.insert(i);
        }
    }
    int findMin(vector<int>& index)
    {
        int minIndex = 0;
        int minPlace;
        for (int i = 0; i < index.size(); ++i)
        {
            if (shortest[index[minIndex]] > shortest[index[i]])
            {
                minIndex = i;
            }
        }
        minPlace = index[minIndex];
        index[minIndex] = index[index.size() - 1];
        index.pop_back();
        return minPlace;
    }
public:
    pta1072():averageDistance(0),minDistance(0),ans(-1)
    {
        cin >> N >> M >> K >> Ds;
        shortest.resize(N + M);
        distance.resize(N + M, vector<int> (N+M,INFINITE));
        for (int i = 0; i < N + M; ++i)
        {
            distance[i][i] = 0;
        }
        string P1, P2;
        int Dist;
        int p1, p2;
        for (int i = 0; i < K; ++i)
        {
            cin >> P1 >> P2 >> Dist;
            if (P1[0] == 'G')
            {
                P1 = P1.substr(1);
                p1 = stoi(P1) + N ;
            }
            else
                p1 = stoi(P1);
            if (P2[0] == 'G')
            { 
                P2 = P2.substr(1);
                p2 = stoi(P2) + N;
            }
            else
                p2 = stoi(P2);
            //cout << "P1 = "<< P1 <<" P2 = "<< P2 <<" p1 = " << p1 <<"p2 = "<< p2 << endl;
            distance[p1-1][p2-1] = Dist;
            distance[p2-1][p1-1] = Dist;
        }
    }
    void solve()
    {
        int currentPlace;
        for (int i = N; i < N + M; ++i)//对所有候选位置一次调用dijkstra算法
        {
            initialize();
            vector<int> index(N + M);
            bool yon = true;
            shortest[i] = 0;
            for (int j = 0; j < N + M; ++j)
                index[j] = j;
            while (!housePlaces.empty())//如果到各个居民房的距离都已经算完，就没有必要继续计算了
            {
                currentPlace = findMin(index);
                for (int k = 0; k < N + M; ++k)
                {
                    if (shortest[currentPlace ] + distance[currentPlace ][k] < shortest[k])
                    {
                        shortest[k] = shortest[currentPlace] + distance[currentPlace][k];
                    }
                }
                if (housePlaces.find(currentPlace) != housePlaces.end())
                {
                    housePlaces.erase(currentPlace);
                    if (shortest[currentPlace] > Ds)//如果候选位置到居民区的距离大于限制距离 则认为这个候选位置不满足条件
                    {
                        yon = false;
                        break;
                    }
                }
            }
            if (yon)//如果候选位置到所有居民房的距离都小于限制距离
            {
                int sum = 0;
                int min = 0;
                for (int x = 0; x < N; x++)//遍历选出最小距离
                {
                    if (shortest[min] > shortest[x])
                        min = x;
                    sum += shortest[x];
                }
                if (shortest[min] > minDistance)//如果本候选位置的最小距离比之前的候选位置的最小距离要大
                {
                    averageDistance = (float)sum / N;
                    minDistance = (float)shortest[min];
                    ans = i;
                }
                else if (shortest[min] == minDistance && (float)sum / N < averageDistance)//如果最小距离一样，但是平均距离更小
                {
                    averageDistance = (float)sum / N;
                    ans = i;
                }
            }
        }
    }
    void Print()
    {
        if (ans != -1)
        {
            printf("G%d\n%.1f %.1f", ans - N+1, minDistance, averageDistance);
        }
        else
        {
            printf("No Solution");
        }
    }
    ~pta1072()
    {}
};
int main()
{
    pta1072* question = (pta1072*)malloc(sizeof(pta1072));
    new(question) pta1072();
    question->solve();
    question->Print();
    question->~pta1072();//显示调用析构函数
}
//思路 由于只求部分节点到部分节点的最短路径 所以不需要使用floyed算法。
//使用dijkstra算法对候选位置调用即可。
//注意 题目条件是居民区在离加油站一定范围的同时的确保最近距离要尽可能远.
//同时 如果最近距离一样的场景下，就要平均距离尽可能近。
//如果平均距离也一致的情况下，选择编号小的那个
