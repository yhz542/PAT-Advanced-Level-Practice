#include<iostream>//本解法从逻辑上来说存在问题，但实际测试的时候由于编译器优化导致可以通过所有测试用例，理论而言 longlong类型会将 2^63 当成-2^63储存。
#include<cstdlib>//所以按理来说long long无法区分2^63和-2^63 但是实际使用cin或者scanf时，编译器会直接将其转化为2^63-1,这样Longlong类型就可以储存的下了。接下来就只有考虑溢出问题。
#include<cstdio>//简单来讲 溢出只存在两种，既负负溢出 和正正溢出。
using namespace std;
using uint = unsigned int;
class pta1065
{
	uint num;
	long long A, B, C;
public:
	bool Process()
	{
		long long sum = A + B;
		if (A > 0 && B > 0 && sum < 0)//正正溢出 由于longlong最多只能储存2^63-1所以sum不可能为0.故只用考虑小于0的情况
			return true;
		else if (A < 0 && B < 0 && sum >= 0)//负负溢出 当A=B=-2^63次方时 sum=0
			return false;
		else
			return sum > C;
	}
	pta1065()
	{
		cin >> num;
	}
	void Solve()
	{
		for (size_t i = 0; i < num; ++i)
		{
			cin >> A;
			if (cin.rdstate() & cin.failbit)
				cin.clear();
			cin >> B;
			if (!cin)
				cin.clear();
			cin >> C;
			if (cin.fail())
				cin.clear();
			cout << "Case #" << i + 1 << (Process() ?": true" : ": false") << endl;
		}
	}
	void Print()
	{
		
	}
	~pta1065()
	{}
};
int main()
{
	pta1065* question = (pta1065*)malloc(sizeof(pta1065));
	new(question) pta1065();
	question->Solve();
	question->Print();
}
