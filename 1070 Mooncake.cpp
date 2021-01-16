#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
//贪心算法 将所有月饼按照单价进行降序排列或者构建最大堆，每次取出首元素。然后对比需求量。
//需要注意题目只限制了需求量是整数，但是并没有说每个月饼的库存是整数。所以D和库存都应该设置为浮点数类型
class pta1070
{
    struct cmp
    {
        const vector<double>& copy_inventory;
        const vector<double>& copy_prices;
        cmp(vector<double>& inventory, vector<double>& prices) :copy_inventory(inventory), copy_prices(prices)
        {}
        bool operator()(int index1, int index2)
        {
            return copy_prices[index1] / copy_inventory[index1] < copy_prices[index2] / copy_inventory[index2];
        }
    };
    int N;
    double D;
    double sum;
    vector<double> inventory;
    vector<double> prices;
    vector<int> index;
public:
    pta1070():sum(0.)
    {
        cin >> N >> D;
        inventory.reserve(N);
        prices.reserve(N);
        index.reserve(N);
        for (int i = 0; i < N; ++i)
        {
            double tem;
            cin >> tem;
            inventory.push_back(tem);
            index.push_back(i);
        }
        for (int i = 0 ; i < N; ++i)
        {
            double tem;
            cin >> tem;
            prices.push_back(tem);
        }
        make_heap(index.begin(), index.end(),cmp(inventory,prices));
    }
    void solve()
    {
        int curIndex = 0;
        double cap = 0;
        while (D!=0&&index.size())
        {
            pop_heap(index.begin(), index.end());
            curIndex = index[index.size() - 1];
            cap = inventory[curIndex];
            index.pop_back();
            if (cap <= D)
            {
                D -= cap;
                sum += prices[curIndex];
            }
            else if (cap > D)
            {
                sum += prices[curIndex] /  cap* D;
                D = 0;
            }
        }
    }
    void print()
    {
        printf("%.2lf", sum);
    }
    ~pta1070() {}
};
int main()
{
    pta1070* ptr = (pta1070 *)malloc(sizeof(pta1070));
    new(ptr) pta1070();
    ptr->solve();
    ptr->print();
}
