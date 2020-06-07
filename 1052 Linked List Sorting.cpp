#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
typedef unsigned int uint;
typedef int Address;
typedef int Key;
typedef int Next;
class pta1051
{
	uint N;
	int headAddress;
	map<Address, pair<Key, Next>> info;
	vector<pair<Address,Key>> effectiveInfo;
	static bool cmp(const pair<Address, Key>& a, const pair<Address, Key>& b)
	{
		return a.second < b.second;
	}
public:
	pta1051(istream &in)
	{
		in >> N>>headAddress;
		int temAddress, temKey, temNext;
		effectiveInfo.reserve(N);
		for (size_t i = 0; i < N; ++i)
		{
			in >> temAddress >> temKey >> temNext;
			info.insert(make_pair(temAddress,make_pair(temKey,temNext)));
		}
		temAddress = headAddress;
		while (temAddress != -1)
		{
			effectiveInfo.push_back(make_pair(temAddress, info[temAddress].first));
			temAddress = info[temAddress].second;
		}
	}
	void Solve()
	{
		sort(effectiveInfo.begin(), effectiveInfo.end(), cmp);
	}
	void Print()
	{
		uint effectCnt = effectiveInfo.size();
		if (!effectCnt)
			printf("0 -1");//注意的地方
		else
		{
			printf("%u %05d\n", effectCnt, effectiveInfo[0].first);
			for (uint i = 0; i < effectCnt - 1; ++i)
			{
				printf("%05d %d %05d\n", effectiveInfo[i].first, effectiveInfo[i].second, effectiveInfo[i + 1].first);
			}
			printf("%05d %d -1", effectiveInfo[effectCnt - 1].first, effectiveInfo[effectCnt - 1].second);
		}
	}
	~pta1051()
	{}
};
int main()
{
	pta1051 *question  = (pta1051 *)malloc(sizeof(pta1051));
	new (question) pta1051(cin);
	question->Solve();
	question->Print();
	question->~pta1051();
	free(question);
}
