#include<iostream>
#include<vector>
typedef unsigned int uint;
using namespace std;
class pta1042
{
	uint K;
	vector<uint> order;
	vector<uint> result;
public:
	pta1042(istream &in)
	{
		in >> K;
		order.reserve(K);
		result.reserve(K);
		uint tem;
		for (size_t i = 0; i < 54; ++i)
		{
			in >> tem;
			order.push_back(tem-1);
			result.push_back(i);
		}
	}
	void Solve()
	{
		for (size_t i = 0; i < 54; ++i)
		{
			uint des_index = 0 ;
			for (size_t cnt = 0, cur_index = i; cnt < K; ++cnt)
			{
				des_index = order[cur_index];
				cur_index = des_index;
			}
			result[des_index] = i;
		}
	}
	void Print()
	{
		for (auto elem : result)
		{
			if (elem != *result.begin())
				cout << ' ';
			if (elem < 13)
				cout << 'S' << elem + 1 ;
			else if (elem < 26)
				cout << 'H' << elem - 12 ;
			else if (elem < 39)
				cout << 'C' << elem - 25 ;
			else if (elem < 52)
				cout << 'D' << elem - 38 ;
			else
				cout << 'J' << elem - 51 ;
		}
	}
};
int main()
{
	pta1042 question(cin);
	question.Solve();
	question.Print();
}
