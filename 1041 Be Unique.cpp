#include<iostream>
#include<unordered_map>
#include<vector>
typedef unsigned int uint;
using namespace std;
class pta1041
{
	uint N;
	vector<uint> data;
	unordered_map<uint, uint> times;
public:
	pta1041(istream &in)
	{
		in >> N;
		data.reserve(N);
		uint num;
		for (size_t i = 0; i < N; ++i)
		{
			in >> num;
			data.push_back(num);
			if (times.find(num) == times.end())
				times.insert(make_pair(num, 0));
			times[num]++;
		}
	}
	void Solve()
	{
		
	}
	void Print()
	{
		for (auto beg = data.begin(); beg != data.end(); ++beg)
		{
			if (times[*beg] == 1)
			{
				cout << *beg << endl;
				return;
			}
		}
		cout << "None" << endl;
	}
};
int main()
{
	pta1041 question(cin);
	question.Solve();
	question.Print();
}
