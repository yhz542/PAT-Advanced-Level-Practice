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
	vector<bool> isVisted;
	uint curcnt;
	void Process(uint index)
	{
		if (isVisted[index])//如果该下标遍历过，直接返回
			return;
		isVisted[index] = true;//设置该下标已遍历
		uint nextLayerIndex = index << 1;
		if (nextLayerIndex +1 <= N-1)//如果左子数存在，进行遍历
		{
			Process(nextLayerIndex +1);
		}
		answer[index] = GetNum(curcnt++);//设置当前下标存放的数值
		if (nextLayerIndex  + 2 <= N - 1)//如果右子树存在，进行遍历
		{
			Process(nextLayerIndex +2);
		}
		if(index)//如果父节点存在，进行遍历
			Process((index - 1) / 2);
	}
public:
	pta1064():curcnt(0)
	{
		cin >> N;
		source.reserve(N);
		answer.resize(N, -1);
		isVisted.resize(N, false);
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
		int layer = (int)(log(N) / log(2));
		uint beginIndex = pow(2, layer) - 1;//找到最小的的数在二叉树数组中的下标
		Process(beginIndex);//进行递归
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
