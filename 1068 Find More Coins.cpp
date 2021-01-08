#include<cstdio>//解题思路：动态规划，背包问题。注意需要将可用的硬币值倒序排列。
//Note: sequence {A[1], A[2], ...} is said to be "smaller" than sequence {B[1], B[2], ...} 
//if there exists k≥1 such that A[i]=B[i] for all i<k, and A[k] < B[k].
//注意题意：对于存在k>=1，并且对于所有的i<k,都有A[i] = B[i]，那么只要A[k]<B[k],就说明A序列比B序列小
//也就是说A[1]=B[1] A[2]=B[2] ……只要A[i]<B[i]那么A就小于B，所以说需要取到尽可能小的数。
//所以需要将硬币值倒序排列，然后用动态规划计算，只要取到小的硬币值能满足要求，就对DP表进行更新
//如果正序排列，那么由于一开始就使用小的硬币值，后面使用大硬币值，后面则无法确定是否需要更新DP表。
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class pta1068
{
    int N,M;
    vector<int> value;
    vector<vector<int>> dp;
    vector<vector<bool>> use;
public:
    pta1068()
    {
        cin >> N >> M;
        dp.resize(N + 1, vector<int>(M + 1, 0));
        use.resize(N + 1, vector<bool>(M + 1, false));
        value.push_back(0);
        int tem = 0 ;
        for (int i = 0; i < N; ++i)
        {
            cin >> tem;
            value.push_back(tem);
        }
    }
    void solve()
    {
        sort(++value.begin(), value.end(), greater<int> ());//从大到小排列硬币值，这样才能确保动态规划的有效性。
        for (int i = 1; i <= N; ++i)//纵轴代表使用的硬币，横轴代表想要的值
        {
            for (int j = 1; j <= M; ++j)
            {
                if (j - value[i] >=0 && value[i] + dp[i - 1][j - value[i]] >= dp[i-1][j])//硬币值小于当前需要达到的值，确保后面的数组计算不会越界
                {
                    use[i][j] = true;
                    dp[i][j] = value[i] + dp[i - 1][j - value[i]];
                }
                else//如果当前硬币不满足要求，直接使用前一个硬币值的DP表值。
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }
    void print()
    {
        bool flag = false;
        if (dp[N][M] != M)
            cout << "No Solution" << endl;
        else
        {
            while (M)//当剩余的值为0，说明已经处理完了。
            {
                if (!use[N][M])//如果不使用当前的硬币，则向前一个硬币的DP表查询。
                {
                    --N;
                }
                else//使用当前硬币，直接输出。
                {
                    if (flag)
                    {
                        cout << " ";
                    }
                    else
                    {
                        flag = true;
                    }
                    cout << value[N];
                    M -= value[N];//减去当前硬币值，更新剩余需要的数值。
                    --N;//将硬币向上推进
                }
            }
        }
    }
    ~pta1068() {}
};
int main()
{
    pta1068* ptr = (pta1068 *)malloc(sizeof(pta1068));
    new(ptr) pta1068();
    ptr->solve();
    ptr->print();
}
