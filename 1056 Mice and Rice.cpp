//思路，根据顺序选出优胜者放入数组中，递归循环选至数组只剩最后一个。每次选取时可以根据晋级人数算出当前的排名，因为如果有4个人晋级，则当前的排名就是第五名，诸如此类，不断更新
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef unsigned int uint;
using weight = uint;
class pta1056
{
	struct info
	{
		weight wi;
		uint rank;
		info(weight tem):wi(tem),rank(0){}
	};
	uint Np, Ng;
	vector<info> data;
	vector<uint> index;
	uint findMaxIndex(uint beginIndex, uint endIndex,const uint rank)
	{
		uint curIndex = index[beginIndex];
		uint maxIndex = curIndex;
		weight max = data[curIndex].wi;
		while (beginIndex < endIndex)
		{
			curIndex = index[beginIndex];
			if (data[curIndex].wi > max)
			{
				maxIndex = curIndex;
				max = data[curIndex].wi;
			}
			data[curIndex].rank = rank;
			++beginIndex;
		}
		return maxIndex;
	}
	void calcul(uint np)//可以优化成循环
	{
		if (1 == np)
		{
			data[index[0]].rank = 1;
			return;
		}
		uint times = np / Ng;
		uint remained = np % Ng;
		const uint rank = (!remained ? times + 1: times + 2);
		uint maxIndex;
		size_t i = 0;
		for( ; i < times ; ++i)
		{
			maxIndex = findMaxIndex(i * Ng, (i + 1) * Ng,rank);
			index[i] = maxIndex;
		}
		if (remained)
		{
			maxIndex = findMaxIndex(i * Ng, np,rank);
			index[i] = maxIndex;
			++times;
		}
		index.resize(times);
		np = times;
		calcul(np);
	}
public:
	pta1056(istream &in)
	{
		in >> Np >> Ng;
		data.reserve(Np);
		index.reserve(Np);
		weight wi;
		for (size_t i = 0; i < Np; ++i)
		{
			in >> wi;
			data.push_back(wi);
		}
		uint playOrder;
		for (size_t i = 0; i < Np; ++i)
		{
			in >> playOrder;
			index.push_back( playOrder);
		}
	}
	void Solve()
	{
		calcul(Np);
	}
	void Print()
	{
		auto begin = data.begin();
		if (begin == data.end())
			return;
		printf("%d", begin->rank);
		while (++begin != data.end())
			printf(" %d", begin->rank);
	}
	~pta1056()
	{}
};
int main()
{
	pta1056 *question  = (pta1056 *)malloc(sizeof(pta1056));
	new (question) pta1056(cin);
	question->Solve();
	question->Print();
	question->~pta1056();
	free(question);
}
