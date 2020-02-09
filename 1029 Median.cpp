#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
typedef unsigned int uint;
class pta1029
{
	uint lengthS1;
	uint lengthS2;
	long median;
	long *S1;
public:
	pta1029() = default;
	bool GetInput()
	{
		scanf("%u",&lengthS1);
		bool result = true;
		S1 = (long *)malloc(sizeof(long)*lengthS1);
		if (nullptr == S1)
			result =  false;
		else
		{
			for (uint i = 0; i < lengthS1; ++i)
				scanf("%ld",S1+i);
		}
		scanf("%d",&lengthS2);
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
	long s2num;
	uint targetpos = (lengthS1 + lengthS2+1) / 2;
	uint curpos = 0;
	for (uint i = 0; i < lengthS2; ++i)
	{
		scanf("%ld", &s2num);
		while (*S1 < s2num&&lengthS1)
		{
			++curpos;
			if (curpos==targetpos)
			{
				median = *S1;
				return;
			}
			++S1;
			--lengthS1;
		}
		++curpos;
		if(curpos ==targetpos)
		{
			median = s2num;
			return;
		}
	}
	while (1)
	{
		curpos++;
		if (curpos == targetpos)
		{
			median = *S1;
			break;
		}
		S1++;
	}
}
void pta1029::Output()
{
	cout << median << endl;
}
//只读入一组数据，然后读入第二组数据时 边读边处理，注意读数据时使用scanf而不是cin
