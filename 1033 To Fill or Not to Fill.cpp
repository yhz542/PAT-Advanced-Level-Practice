#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<cstdio>
using namespace std;
#define Des -1
typedef unsigned int uint;
struct station
{
    double gasPrice;
    uint distance;
    bool operator<(station other) const
    {
            return this->distance < other.distance;
    }
    station(double g,int d):gasPrice(g),distance(d)
    {}
};
class pta1033
{
    uint Cmax, D, N;
    double Davg;
    vector<station> info;
    double maxTravelDistance;
    bool arrive;
    double allPrice;
public:
    pta1033(istream& in):maxTravelDistance(-1),allPrice(0),arrive(false)
    {
        in >> Cmax >> D >> Davg >> N;
        info.reserve(N+1);
        double gasPrice;
        uint distance;
        for (size_t i = 0; i < N; ++i)
        {
            in >> gasPrice >> distance;
            info.push_back(station(gasPrice, distance));
        }
        info.push_back(station(0, D));
    }
    void Solve()
    {
        stable_sort(info.begin(), info.end());
        arrive = false;
        if (info[0].distance)
        {
            maxTravelDistance = 0;
            return;
        }
        double curOil = 0;
        double maxDistanceFullOil = Cmax * Davg;
        double curDistance = 0;
        double curPrice = 0;
        uint i = 0;
        while( i < N+1)
        {
            if (info[i].distance == D)
            {
                arrive = true;
                break;
            }
            curOil -= (info[i].distance - curDistance) / (float)Davg;
            curDistance = info[i].distance;
            curPrice = info[i].gasPrice;
            for(uint j = i+1;j<N+1;++j)
            {
                if (info[j].distance < curDistance + maxDistanceFullOil)//如果下一站在抵达范围内
                {
                    if (D == info[j].distance|| info[j].gasPrice < curPrice)//如果这一战之前就抵达终点了
                    {
                        double needOil = (info[j].distance - curDistance) / Davg;
                        if (needOil > curOil)
                        {
                            allPrice += (needOil - curOil) * curPrice;
                            curOil = needOil;
                        }
                        i = j;
                        break;
                    }
                }
                else//如果下一站不在抵达范围内
                {
                    if (curDistance + maxDistanceFullOil < info[i + 1].distance)
                    {
                        arrive = false;
                        maxTravelDistance = curDistance + maxDistanceFullOil;
                        return;
                    }
                    allPrice += (Cmax - curOil) * curPrice;
                    curOil = Cmax;
                    ++i;
                    break;
                }
            }
        }
    }
    void Print()
    {
        if (arrive)
            printf("%.2f\n", allPrice);
        else
            printf("The maximum travel distance = %.2f", maxTravelDistance);
    }
};
int main()
{
    pta1033 question(cin);
    question.Solve();
    question.Print();
    return 0;
}
