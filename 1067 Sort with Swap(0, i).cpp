#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
using namespace std;
using uint = unsigned int;
using Value = uint;
using Index = uint;
class pta1067
{
	uint N,times;
	vector<Value> numVector;//存储数字内容
	map<Value,Index,greater<uint>> numPos;//用map存储所有输入数字的顺序，用于快速查找下标
public:
	pta1067():times(0)
	{
		cin >> N;
		numVector.reserve(N); 
		for (size_t i = 0,value; i < N; ++i)
		{
			cin >> value;
			numVector.push_back(value);
			if(value != i)
				numPos.insert(make_pair(value,i));
		}
	}
	void Solve()
	{
		if (numPos.empty())
		{
			return;
		}
		while( !numPos.empty() )//如果数字没有拿完，就继续运行
		{
			while( numPos[0] != 0)//如果0不在位置0上
			{
				Value targetVal = numPos[0] ;//0当前下标对应的目标数值。
				uint targetIndex = numPos[targetVal] ;//目标数值存放的位置
				//交换位置
				numPos[0] = targetIndex;
				numVector[targetIndex] = 0;
				numPos[targetVal] = targetVal;
				numVector[targetVal] = targetVal;
				if (numPos.find(targetVal) != numPos.end())
					numPos.erase(targetVal);
				times++;
			}
			if(numPos.size() > 1)
			{
				uint index = numPos.begin()->second;
				Value val = numPos.begin()->first;
				numPos[val] = numPos[0];
				numVector[numPos[0]] = val;
				numPos[0] = index;
				numVector[index] = 0;
				++times;//次数+1
			}
			else if (numPos.size() == 1)
			{
				numPos.clear();
			}
		}
	}
	void Print()
	{
		cout << times;
	}
	~pta1067()
	{}
};
int main()
{
	pta1067* question = (pta1067*)malloc(sizeof(pta1067));
	new(question) pta1067();
	question->Solve();
	question->Print();
	question->~pta1067();
	free(question);
}
