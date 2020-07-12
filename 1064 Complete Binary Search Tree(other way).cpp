#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
using uint = unsigned int;
#define GetNum(index) (source[index])
class pta1064
{
	uint N;
	vector<int> source;
	vector<int> answer;
	uint curcnt;
	void Process(uint index)//直接从源点开始对左右子树进行遍历，遍历的效率更高
	{
		uint next = index << 1;
		if (next + 1 <= N - 1)
			Process(next + 1);
		answer[index] = GetNum(curcnt++);
		if (next + 2 <= N - 1)
			Process(next + 2);
	}
public:
	pta1064() :curcnt(0)
	{
		cin >> N;
		source.reserve(N);
		answer.resize(N, -1);
		int tem = 0;
		for (size_t i = 0; i < N; ++i)
		{
			cin >> tem;
			source.push_back(tem);
		}
	}
	void Solve()
	{
		sort(source.begin(), source.end());
		Process(0);
	}
	void Print()
	{
		bool flag = false;
		for (auto elem : answer)
		{
			if (!flag)
			{
				flag = true;
				printf("%d", elem);
			}
			else
				printf(" %d", elem);
		}
	}
	~pta1064()
	{}
};
int main()
{
	pta1064* question = (pta1064*)malloc(sizeof(pta1064));
	new(question) pta1064();
	question->Solve();
	question->Print();
}
