#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class pta1027
{
	int R, G, B;
	string answer;
	char numToCharacter(int num)
	{
		if (num > 13)
		{
			cout << "error" << endl;
			return '\0';
		}
		if (num < 10)
			return '0' + num;
		else
		{
			switch (num)
			{
			case 10:
				return 'A';
			case 11:
				return 'B';
			case 12:
				return 'C';
			default:
				cout << "error number" << endl;
				return 0;
			}
		}
	}
	string decimalTo13radix(int num)
	{
		string colorValue;
		if (num > 168)
		{
			cout << "bigger than 168 error!" << endl;
			return colorValue;
		}
		if(num<13)
			return colorValue+'0'+ numToCharacter(num);
		int result = num / 13;
		colorValue += numToCharacter(result);
		result = num - ((result << 3) +( result << 2) + result);
		colorValue += numToCharacter(result);
		return colorValue;
	}
public:
	pta1027(istream& in)
	{
		cin >> R >> G >> B;
	}
	void Solve()
	{
		answer += decimalTo13radix(R);
		answer += decimalTo13radix(G);
		answer += decimalTo13radix(B);
	}
	void Print()
	{
		cout << '#'<<answer << endl;
	}
};
int main()
{
	pta1027 question(cin);
	question.Solve();
	question.Print();
}
