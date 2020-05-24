#include<cstdio>
#include<iostream>
#include<string>
#include<set>
using namespace std;
typedef unsigned int uint;
class pta1050
{
	string S1, S2;
	set<char> needDel;
public:
	pta1050(istream &in)
	{
		getline(in,S1);
		getline(in, S2);
	}
	void Solve()
	{
		for (auto elem : S2)
			needDel.insert(elem);
		for (auto& elem : S1)
		{
			if (needDel.find(elem) != needDel.end())
				elem = '\0';
		}
	}
	void Print()
	{
		for (auto elem : S1)
		{
			if (elem!='\0')
				cout << elem;
		}
	}
};
int main()
{
	pta1050 question(cin);
	question.Solve();
	question.Print();
}
