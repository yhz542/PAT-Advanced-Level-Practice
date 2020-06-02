#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<stack>
using namespace std;
typedef unsigned int uint;
class pta1051
{
	int M, N, K;
	stack<int> data;
	bool result;
public:
	pta1051(istream &in):result(false)
	{
		in >> M >> N >> K;
	}
	void Solve()
	{
		int tem;
		int start = 1;
		int curTop = 0;
		for (size_t i = 0; i < (uint)K; ++i)
		{
			start = 1;
			result = true;
			while (data.size())
				data.pop();
			for (size_t j = 0; j < (uint)N; ++j)
			{
				cin >> tem;
				if (!result)
					continue;
				if (tem >= start)
				{
					for (size_t beg = start; beg <= (uint)tem; ++beg)
					{
						data.push(beg);
					}
					if (data.size() > (uint)M)
						result = false;
					start = tem + 1;
					data.pop();
				}
				else
				{
					curTop = data.top();
					data.pop();
					if (curTop != tem)
						result = false;
				}
			}
			cout << (result ? "YES" : "NO") << endl;
		}
	}
	void Print()
	{
		
	}
};
int main()
{
	pta1051 *question  = (pta1051 *)malloc(sizeof(pta1051));
	new (question) pta1051(cin);
	question->Solve();
	question->Print();
}
