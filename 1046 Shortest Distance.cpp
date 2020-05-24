#include<iostream>
#include<vector>
typedef unsigned int uint;
using namespace std;
class pta1046
{
	int N,M;
	vector<uint> D;
public:
	pta1046(istream& in)
	{
		in >> N;
		D.reserve(N+1);
		D.push_back(0);
		uint distance;
		for (int i = 0; i < N; ++i)
		{
			in >> distance;
			D.push_back(D[i]+distance);
		}
		in >> M;
	}
	void Solve()
	{
		int i, j;
		int distance = 0;
		for (int cnt = 0; cnt < M; ++cnt)
		{
			distance = 0;
			cin >> i >> j;
			if (i > j)
			{
				int tem = i;
				i = j;
				j = tem;
			}
			--i;
			--j;
			distance = D[j] - D[i];
			if (distance <(int)D[N] - distance)
				cout << distance<<endl;
			else
				cout << D[N] - distance<<endl;
		}
	}
	void Print()
	{
	}
};
int main()
{
	pta1046 question(cin);
	question.Solve();
	question.Print();
}
