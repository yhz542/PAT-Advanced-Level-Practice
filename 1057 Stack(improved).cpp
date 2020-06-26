#include<stack>//利用两个multiset存放中位数的左右两边。因为栈操作每次只有一个操作，同时只能操作一个数，所以可以操作一次，调整一次multiset,源出处暂时找不到了
#include<cstdlib>
#include <cstdio>
#include<set>
using uint = unsigned int;
using namespace std;
class pta1057
{
	stack<uint> data;
	multiset<uint> smallerEqualMidean;//存储中位数左边以及中位数
	multiset<uint> biggerMidean;//存储中位数右边
	uint midean;
	uint N;
	void Adjust(void)
	{
		multiset<uint>::iterator iter;
		if (smallerEqualMidean.size() < biggerMidean.size())
		{
			iter = biggerMidean.begin();
			midean = *iter;
			smallerEqualMidean.insert(*iter);
			biggerMidean.erase(iter);
		}
		else if (smallerEqualMidean.size() > biggerMidean.size() + 1)
		{
			iter = smallerEqualMidean.end() ;
			--iter;
			--iter;
			midean = *iter;
			++iter;
			biggerMidean.insert(*iter);
			smallerEqualMidean.erase(iter);
		}
		if(!smallerEqualMidean.empty())//考虑smallerEqualMidean 大小与biggerMidean相等以及大一的时候需要更新midean
		{
			iter = smallerEqualMidean.end();
			--iter;
			midean = *iter;
		}
	}
	void Push(uint num)
	{
 		if (num <= midean)
			smallerEqualMidean.insert(num);
		else
			biggerMidean.insert(num);
		Adjust();
	}
	void Pop(uint num)
	{
		if (num <= midean)
			smallerEqualMidean.erase(smallerEqualMidean.find(num));
		else
			biggerMidean.erase(biggerMidean.find(num));
		Adjust();
	}
public:
	pta1057():midean(100001)
	{
		scanf("%u", &N);
		char str[11];
		uint num;
		for (size_t i = 0; i < N; ++i)
		{
			scanf("%s", str);
			switch (str[1])
			{
			case 'u'://push
			{
				scanf("%u", &num);
				data.push(num);
				Push(num);
				break;
			}
			case 'o'://pop
			{
				if (data.empty())
					printf("Invalid\n");
				else
				{
					num = data.top();
					printf("%u\n", num);
					data.pop();
					Pop(num);
				}
				break;
			}
			case 'e'://peekmedian
				if (data.empty())
					printf("Invalid\n");
				else
					printf("%u\n", midean);
				break;
			}
		}
	}
};
int main()
{
	pta1057* question = (pta1057*)malloc(sizeof(pta1057));
	new (question)pta1057;
}
