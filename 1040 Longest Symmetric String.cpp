#include<iostream>//dynamic programming 动态规划 思想 如果 A是回文 则BAB就是回文，后续添加具体说明
#include<string>
#include<vector>
typedef unsigned int uint;
using namespace std;
class pta1040
{
	string str;
	vector<vector<uint>> symLength;
	vector<vector<bool>> isSym;
public:
	pta1040(istream &in)
	{
		getline(in,str);
		symLength.resize(str.size(), vector<uint>(str.size(), 0));
		isSym.resize(symLength.size(), vector<bool>(symLength.size(), false));
		for (uint i = 0; i < symLength.size(); ++i)
		{
			symLength[i][i] = 1;
			isSym[i][i] = true;
			if (i >= 1)
				isSym[i][i - 1] = true;
		}
	}
	void Solve()
	{
		for (int i = str.size() - 2 ; i >=0; --i )
		{
			for (int x = i, y = str.size()-1; x>=0; --x, --y)
			{
				if (isSym[x+1][y-1]&&str[x]==str[y])
				{
					isSym[x][y] = true;
					symLength[x][y] = symLength[x + 1][y - 1] + 2;
				}
				else
				{
					symLength[x][y] = (symLength[x + 1][y] > symLength[x][y - 1] ? symLength[x + 1][y] : symLength[x][y - 1]);
				}
			}
		}
	}
	void Print()
	{
		cout << symLength[0][str.size()-1];
	}
};
int main()
{
	pta1040 question(cin);
	question.Solve();
	question.Print();
}
