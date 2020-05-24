#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
typedef unsigned int uint;
using namespace std;
class pta1047
{
	int N, K;
	vector<vector<int>> courseInfo;
	inline int Convert(const string &str)
	{
		return (((str[0]-'A') * 26 + (str[1]-'A')) * 26 + (str[2]-'A')) * 10 + str[3] - '0';
	}
	inline string Convert(int num)
	{
		string str;
		str.resize(4);
		str[3] = num % 10+'0';
		num /= 10;
		for (int i = 2; i >= 0; --i)
		{
			str[i] = num % 26+'A';
			num /= 26;
		}
		return str;
	}
public:
	pta1047(istream& in)
	{
		uint cnt;
		uint courseNum;
		in >> N >> K;
		courseInfo.resize(K);
		string name;
		for (size_t index = 0; index < (uint)N; ++index)
		{
			in >> name;
			in >> cnt;
			for (size_t i = 0; i < cnt; ++i)
			{
				in >> courseNum;
				courseInfo[courseNum - 1].push_back(Convert(name));
			}
		}
	}
	void Solve()
	{
		
	}
	void Print()
	{
		uint num = 1;
		for (auto& elem : courseInfo)
		{
			sort(elem.begin(), elem.end());
			printf("%d %d\n", num++, elem.size());
			for (auto nameNum : elem)
			{
				printf("%s\n",Convert(nameNum).c_str());
			}
		}
	}
};
int main()
{
	pta1047 question(cin);
	question.Solve();
	question.Print();
}
