#include<iostream>//思路，没什么太值得说的，输入的时候，将输入的每位数每出现一次就增加一次次数，然后计算输出的时候，再将对应的每位数的次数减1
#include<cstdio>  //最后次数应该全部为0
#include<vector>
using namespace std;
class pta1023
{
	vector<int> input;
	vector<int> output;
	char symbol = '+';
	bool yesOrNo = true;
	vector<int> timesOfNum;
public:
	void GetInput();
	void Solve();
	void Output();
};
int main()
{
	pta1023 question;
	question.GetInput();
	question.Solve();
	question.Output();
}
void pta1023::GetInput()
{
	timesOfNum.resize(10, 0);
	input.reserve(20);
	char n;
	while ( 1 )
	{
		n = getchar();
		if (n != ' ')
			break;
	}
	if ('-' == n)
		symbol = '-';
	else
	{
		input.push_back(n - '0');
		++timesOfNum[n - '0'];
	}
	while (n = getchar(), '\n' != n)
	{
		input.push_back(n - '0');
		timesOfNum[n - '0']++;
	}
}
void pta1023::Solve()
{
	bool biggerThan10 = false;
	int result = 0;
	for (auto beg = input.rbegin(); beg != input.rend(); ++beg)
	{
		result = (*beg) << 1;
		if (biggerThan10)
			++result;
		if (result >= 10)
		{
			result -= 10;
			biggerThan10 = true;
		}
		else
			biggerThan10 = false;
		output.push_back(result);
		timesOfNum[result]--;
	}
	if (biggerThan10)
	{
		output.push_back(1);
		timesOfNum[1]--;
	}
	for (int i = 0; i < (int)timesOfNum.size(); ++i)
	{
		if (timesOfNum[i]!=0)
		{
			yesOrNo = false;
			break;
		}
	}
}
void pta1023::Output()
{
	cout << (yesOrNo ? "Yes" : "No") << endl;
	if ('-' == symbol)
		cout << '-';
	for (auto beg = output.rbegin(); beg != output.rend(); ++beg)
		cout << *beg;
	cout << endl;
}
