#include<cstdio>
#include<cstdlib>
#include<set>
#include<vector>
#include<new>
using namespace std;
using uint = unsigned int ;
class PTA_1063
{
	uint N;
	uint M;
	uint K;
	vector<set<int>>data;
public:
	PTA_1063():N(0),M(0),K(0)
	{
		int temValue;
		scanf("%d", &N);
		data.resize(N);
		for (size_t i = 0; i < N; ++i)
		{
			scanf("%d", &M);
			for (size_t j = 0; j < M; ++j)
			{
				scanf("%d", &temValue);
				data[i].insert(temValue);
			}
		}
	}
	void Solve()
	{
		scanf("%d", &K);
		uint setA, setB;
		uint sameCnt;
		for (size_t i = 0; i < K; ++i)
		{
			sameCnt = 0;
			scanf("%d %d", &setA, &setB);
			--setA;
			--setB;
			const set<int>& tem = data[setA];
			for (auto elem : tem)
			{
				if (data[setB].find(elem) != data[setB].end())
				{
					sameCnt++;
				}
			}
			printf("%.1f%%\n", (float)sameCnt / (data[setA].size() + data[setB].size() - sameCnt)*100);
		}
	}
	void Print()
	{

	}
	~PTA_1063()
	{}
};
int main()
{
	PTA_1063* ptr = (PTA_1063*)malloc(sizeof(PTA_1063));
	new(ptr) PTA_1063();
	ptr->Solve();
	ptr->Print();
	ptr->~PTA_1063();
}
