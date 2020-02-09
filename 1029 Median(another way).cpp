
#include<iostream>//另一种使用哨兵的方案，在比较时更为方便
#include<cstdlib>
#include<climits>
#define INFINITE LONG_MAX
using namespace std;
typedef unsigned int uint;
class pta1029
{
	uint lengthS1;
	uint lengthS2;
	long median;
	long *S1;
	long s2num;
public:
	pta1029() = default;
	bool GetInput()
	{
		scanf("%u",&lengthS1);
		bool result = true;
		S1 = (long *)malloc(sizeof(long)*(lengthS1+1));
		if (nullptr == S1)
			result = false;
		else
		{
			for (uint i = 0; i < lengthS1; ++i)
				scanf("%ld", S1+i);
		}
		S1[lengthS1] = INFINITE;
		scanf("%u",&lengthS2);
		return result;
	}
	void Solve();
	void Output();
};
int main()
{
	pta1029 question;
	question.GetInput();
	question.Solve();
	question.Output();
}
void pta1029::Solve()
{
	typedef uint index;
	uint posOfMedian = (lengthS1 + lengthS2 + 1) / 2;
	uint curPos=0;
	if (lengthS2)
	{
		scanf("%ld", &s2num);
	}
	do
	{
		++curPos;
		if (lengthS2<=0)
		{
			median = *S1;
			++S1;
			--lengthS1;
		}
		else
		{
			if (*S1<s2num)//s1比s2小，则s1的下标后移
			{
				median = *S1;
				++S1;
				--lengthS1;
			}
			else
			{
				median = s2num;
				if (--lengthS2>0)
					scanf("%ld", &s2num);
			}
		}
	} while (curPos != posOfMedian);//条件待修改
}
void pta1029::Output()
{
	cout << median << endl;
}
