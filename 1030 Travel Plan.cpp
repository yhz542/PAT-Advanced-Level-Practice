#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
#define INFINITE 65535
typedef unsigned int uint;
struct price
{
    uint distance = INFINITE;
    uint cost = INFINITE;
    price() = default;
};
class pta1030
{
    int N, M, S, D;
    vector<vector<price>> info;
    vector<price> shortest;
    vector<int> pred;
    uint FindMin(vector<price>& shortest, set<uint>& remainedCity)
    {
        uint minDistance = INFINITE;
        uint target = INFINITE;
        for (auto beg = remainedCity.begin(); beg != remainedCity.end(); ++beg)
        {
            if (minDistance > shortest[*beg].distance)
            {
                target = *beg;
                minDistance = shortest[*beg].distance;
            }
        }
        return target;
    }
public:
    pta1030(istream& in)
    {
        in >> N >> M >> S >> D;
        info.resize(N, vector<price>(N, price()));
        uint city1, city2, distance, cost;
        for (size_t i = 0; i < N; ++i)
        {
            info[i][i].distance = 0;
            info[i][i].cost = 0;
        }
        for (size_t i = 0; i < M; ++i)
        {
            cin >> city1 >> city2 >> distance >> cost;
            info[city1][city2].distance = distance;
            info[city1][city2].cost = cost;
            info[city2][city1].distance = distance;
            info[city2][city1].cost = cost;
        }
        pred.resize(N, -1);
    }
    void Solve()
    {
        shortest.resize(N);
        shortest[S].distance = 0;
        shortest[S].cost = 0;
        pred[S] = -1;
        set<uint> remainedCity;
        for (uint i = 0; i < N; ++i)
        {
            remainedCity.insert(i);
        }
        uint curCity;
        while (!remainedCity.empty())
        {
            curCity = FindMin(shortest, remainedCity);
            remainedCity.erase(curCity);
            for (auto beg = remainedCity.begin(); beg != remainedCity.end(); ++beg)
            {
                uint linkCity = *beg;
                if (info[curCity][linkCity].distance + shortest[curCity].distance < shortest[linkCity].distance)
                {
                    shortest[linkCity].distance = info[curCity][linkCity].distance + shortest[curCity].distance;
                    shortest[linkCity].cost = info[curCity][linkCity].cost + shortest[curCity].cost;
                    pred[linkCity] = curCity;
                }
                else if (info[curCity][linkCity].distance + shortest[curCity].distance == shortest[linkCity].distance
                    && info[curCity][linkCity].cost + shortest[curCity].cost < shortest[linkCity].cost)
                {
                    shortest[linkCity].cost = info[curCity][linkCity].cost + shortest[curCity].cost;
                    pred[linkCity] = curCity;
                }
            }
        }
    }
    void Print()
    {
        vector<uint> reversePath;
        reversePath.reserve(N);
        uint curCity = D;
        while (curCity != -1)
        {
            reversePath.push_back(curCity);
            curCity = pred[curCity];
        }
        bool flag = false;
        for (auto beg = reversePath.rbegin(); beg != reversePath.rend(); ++beg)
        {
            cout << *beg << " ";
        }
        cout << shortest[D].distance << " " << shortest[D].cost << endl;
    }
};
int main()
{
    pta1030 question(cin);
    question.Solve();
    question.Print();
    return 0;
}
