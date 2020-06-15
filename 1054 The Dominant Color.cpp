#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<unordered_map>
using namespace std;
typedef unsigned int uint;
typedef uint color;
typedef uint cnt;
class pta1054
{
	uint M, N;
	unordered_map<color,cnt> image;
public:
	pta1054(istream &in)
	{
		uint tem;
		in >> M >> N;
		uint target = (M * N)>>1;
		for (uint i = 0; i < N; ++i)
		{
			for (uint j = 0; j < M; ++j)
			{
				scanf("%u",&tem);
				image[tem]++;
				if (image[tem] > target)
				{
					printf("%u\n", tem);
					return;
				}
			}
		}
	}
	void Solve()
	{
	}
	void Print()
	{
	}
	~pta1054()
	{}
};
int main()
{
	pta1054 *question  = (pta1054 *)malloc(sizeof(pta1054));
	new (question) pta1054(cin);
	question->Solve();
	question->Print();
	question->~pta1054();
	free(question);
}
