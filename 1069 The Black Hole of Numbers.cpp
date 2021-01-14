#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class pta1069
{
    int num,increaseOrder,decreaseOrder;
    vector<int> data;
    vector<int> increase;
    vector<int> decrease;
public:
    pta1069():num(0),increaseOrder(0),decreaseOrder(0)
    {
        cin >> num;
        data.resize(4, 0);
    }
    void solve()
    {
        do
        {
            for (int i = 1000, j = 0; i > 0; i /= 10, ++j)
            {
                data[j] = num / i;
                num %= i;
            }
            sort(data.begin(), data.end());
            for (size_t i = 0; i < data.size(); ++i)
            {
                increaseOrder *= 10;
                increaseOrder += data[i];
            }
            reverse(data.begin(), data.end());
            for (size_t i = 0; i < data.size(); ++i)
            {
                decreaseOrder *= 10;
                decreaseOrder += data[i];
            }
            num = decreaseOrder - increaseOrder;
            print();
            decreaseOrder = 0;
            increaseOrder = 0;
        } while (num != 6174 && num != 0);
    }
    void print()
    {
        printf("%04d - %04d = %04d\n", decreaseOrder, increaseOrder, num);
    }
    ~pta1069() {}
};
int main()
{
    pta1069* ptr = (pta1069 *)malloc(sizeof(pta1069));
    new(ptr) pta1069();
    ptr->solve();
    //ptr->print();
}//没什么好说的，题很简单 ，将获取的数拆分成4个个位数处理即可，顺序排列 逆序排列 然后再做减法，反复如此直到最后的差为0或者6174为止
