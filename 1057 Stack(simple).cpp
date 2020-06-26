#include<cstdio>//因为key值最大不超过100000，所以可以将其分为若干份，这里分成了100份。然后用sumOfBlock存每一份中含的数目数量。然后搜索的时候先搜sumOfblocks再对其中的一份进行精确搜索。
#include<cstdlib>
#include<vector>
#include<stack>
using namespace std;
typedef unsigned int uint;
using weight = uint;
class pta1057
{
	uint N;
	vector<vector<uint>> numSet;
	vector<uint> sumOfBlock;
	stack<uint> data;
	char str[11];
	void findMedian()
	{
		uint targetOrder = (data.size() + 1)/ 2;
		uint index = 0;
		uint curOrder = 0;
		while( curOrder + sumOfBlock[index] < targetOrder )
		{
			curOrder += sumOfBlock[index];
			++index;
		}
		for (size_t i = 0 ; i< numSet[index].size() ; ++i)
		{
			curOrder += numSet[index][i];
			if (curOrder >= targetOrder)
			{
				printf("%d\n", index*1000+i);
				break;
			}
		}
	}
public:
	pta1057()
	{
		scanf("%u", &N);
		numSet.reserve(101);
		numSet.resize(100, vector<uint>(1000));
		sumOfBlock.resize(101, 0);
		numSet.push_back(vector<uint>(1));
		for (uint i = 0; i < N; ++i)
		{
			scanf("%s", str);
			switch (str[1])
			{
			case 'u'://Push
			{
				int key;
				scanf("%d", &key);
				data.push(key);
			    ++numSet[key / 1000 ][key%1000];
				++sumOfBlock[key / 1000];
				break;
			}
			case 'o'://Pop
				if (data.empty())
					printf("Invalid\n");
				else
				{
					printf("%d\n", data.top());
					--numSet[data.top() / 1000 ][data.top()%1000];
					--sumOfBlock[data.top() / 1000];
					data.pop();
				}
				break;
			case 'e':
				if (data.empty())
					printf("Invalid\n");
				else
					findMedian();
				break;
			}
		}
	}
	void Solve()
	{
		
	}
	void Print()
	{
		
	}
	~pta1057()
	{}
};
int main()
{
	pta1057 *question  = (pta1057 *)malloc(sizeof(pta1057));
	new (question) pta1057();
	question->Solve();
	question->Print();
	question->~pta1057();
	free(question);
}
