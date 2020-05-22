#include<iostream>//O(n)时间复杂度的解法
#include<vector>
typedef unsigned int uint;
#define INFINITE 1<<30
using namespace std;
class pta1044
{
	uint N, M;
	vector<uint> D;
	vector<pair<int, int>> answer;
	uint curBestPay;
public:
	pta1044(istream& in) :curBestPay(INFINITE)
	{
		uint tem;
		in >> N >> M;
		D.reserve(N);
		for (size_t i = 0; i < N; ++i)
		{
			in >> tem;
			D.push_back(tem);
		}
	}
	void Solve()
	{
		uint curSum = 0;
		size_t curIndex, begIndex = 0;
		for (curIndex = 0 ; curIndex<N;++curIndex)
		{
			curSum += D[curIndex];
			if(curSum >= M)
			{
				while (curSum > M && begIndex != curIndex)
				{
					curSum -= D[begIndex];
					++begIndex;
				}
				if (curSum < M)
					curSum += D[--begIndex];
				if (curBestPay > curSum)
				{
					answer.clear();
					curBestPay = curSum;
					answer.push_back(make_pair(begIndex+1, curIndex+1));
				}
				else if (curBestPay == curSum)
				{
					answer.push_back(make_pair(begIndex+1, curIndex+1));
				}
			}
		}
	}
	void Print()
	{
		for (auto elem : answer)
		{
			cout << elem.first << '-' << elem.second<<endl;
		}
	}
};
int main()
{
	pta1044 question(cin);
	question.Solve();
	question.Print();
}
