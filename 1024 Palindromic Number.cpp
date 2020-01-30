//思路 没什么好说的 注意一点，就是用字符串进行数字存储，否则放不下。
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
typedef unsigned int uint;
using namespace std;
class pta1024
{
	string N ;
	uint K = 0;
	bool IsPalindromicNum(const string &);
	void Add(string &);
public:
	void GetInput();
	void Solve();
	void Output();
};
int main()
{
	pta1024 question;
	question.GetInput();
	question.Solve();
	question.Output();
}
void pta1024::GetInput()
{
	cin >> N >> K;
}
void pta1024::Solve()
{
	uint i = 0;
	for ( i = 0; i < K; ++i)
	{
		if (IsPalindromicNum(N))
		{
			break;
		}
		Add(N);
	}
	reverse(N.begin(), N.end());
	cout << N << endl<< i;
}
void pta1024::Output()
{
	
}
bool pta1024::IsPalindromicNum(const string &numStr)
{
	uint length = numStr.size();
	for (uint head = 0,tail = length-1; head < tail; ++head,--tail)
	{
		if (numStr[head] != numStr[tail])
			return false;
	}
	return true;
}
void pta1024::Add(string &num )
{
	uint numLen = num.size();
	bool biggerThan10 = false;
	string result;
	if (num[0] - '0' + num[numLen - 1] - '0' >= 10)
		result.reserve(numLen + 1);
	else
		result.reserve(numLen);
	for (uint i = 0,digit = 0; i < numLen; ++i)
	{
		digit = num[i] + num[numLen - i - 1] -( '0' << 1);
		if (biggerThan10)
			++digit;
		if (digit >= 10)
		{
			digit -= 10;
			biggerThan10 = true;
		}
		else
			biggerThan10 = false;
		result.push_back(digit+'0');
	}
	if (biggerThan10)
		result.push_back('1');
	num = result;
}
