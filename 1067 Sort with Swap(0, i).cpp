#include<iostream>//解题思路，首先存储所有需要下标不等于值的元素，然后看0此时的下标，如果0的下标不为0，就将它下标对应的数换到0的位置，那么这样就减少了一个需要处理的元素。如果0的下标等于0，就将
#include<cstdlib>//它和需要处理的随便一个元素交换位置。然后再按照0的下标不为0的方法处理。即可解决本问题。
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
	map<Value,Index,greater<uint>> numPos;//用map存储所有输入数字的下标，用于快速查找，注意是逆序排列
public:
	pta1067():times(0)
	{
		cin >> N;
		numVector.reserve(N); 
		for (size_t i = 0,value; i < N; ++i)
		{
			cin >> value;
			numVector.push_back(value);
			if(value != i)//只有下标和值不相同时，才放入map中。
				numPos.insert(make_pair(value,i));
		}
	}
	void Solve()
	{
		if (numPos.empty())
		{
			return;
		}
		while( !numPos.empty() )//如果还有下标和值不相同的元素，就继续运行
		{
			while( numPos[0] != 0)//如果0不在位置0上，进入循环，如果0在位置0上，直接往下运行。
			{
				Value targetVal = numPos[0] ;//0当前下标对应的目标数值。
				uint targetIndex = numPos[targetVal] ;//获取0的下标对应的数值的下标
				//交换位置
				numPos[0] = targetIndex;//将0的下标设置为其下标对应数值的位置
				numVector[targetIndex] = 0;
				numPos[targetVal] = targetVal;//将对应的目标数值放入正确位置下标中。
				numVector[targetVal] = targetVal;
				if (numPos.find(targetVal) != numPos.end())
					numPos.erase(targetVal);//擦除该数值。
				times++;//交换次数加1
			}//退出while循环说明 0已经在下标0位置上。
			if(numPos.size() > 1)//如果map中不止一个元素，说明除了0以外还有其他元素没有回到自己的位置。这种情况下需要将0随便与其中一个元素交换位置。
			{
				uint index = numPos.begin()->second;
				Value val = numPos.begin()->first;
				numPos[val] = numPos[0];
				numVector[numPos[0]] = val;
				numPos[0] = index;
				numVector[index] = 0;
				++times;//次数+1
			}
			else if (numPos.size() == 1)//如果此时map中只有一个元素，那么这个元素一定是0，并且就在位置0上。不需要增加交换次数，直接清空map
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
