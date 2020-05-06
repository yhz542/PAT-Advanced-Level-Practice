#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
typedef unsigned int uint;
using namespace std;
class pta1038
{
	uint N;
	vector<string> data;
	static bool Cmp(const string& str1, const string& str2)
	{
    return str1+str2<str2+str1;
	}
public:
	pta1038(istream &in)
	{
		in >> N;
		data.reserve(N);
		string num;
		for (size_t i = 0; i < N; ++i)
		{
			in >> num;
			data.push_back(num);
		}
	}
	void Solve()
	{
		sort(data.begin(), data.end(),Cmp);
	}
	void Print()
	{
		bool flag = false;
		for (const auto &elem : data)
		{
			if (!flag)
			{
				int pos = elem.find_first_not_of('0');
				if (pos == string::npos)
					continue;
				else
				{
					flag = true;
					for (uint i = pos; i < elem.size(); ++i)
						cout << elem[i];
				}
			}
			else
				cout << elem;
		}
		if (!flag)
			cout << '0' << endl;
	}
};
int main()
{
	pta1038 question(cin);
	question.Solve();
	question.Print();
}
