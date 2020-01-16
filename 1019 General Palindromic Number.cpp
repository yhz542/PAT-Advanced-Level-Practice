#include<iostream>
#include<string>
#include<vector>
using namespace std;
class question1019
{
	unsigned N;
	unsigned b;
	string answer;
	vector<unsigned> num;
public:
	question1019(istream& in):answer("Yes")//获取输入
	{
		in >> N >> b;
	}
	void Process();//计算处理
	void Print()//输出结果
	{
		bool flag = false;
		cout << answer << endl;
		for (auto beg = num.crbegin() ;beg!=num.crend();beg++)//倒序放入数组中，所以要倒序输出
		{
			if (!flag)
			{
				flag = true;
				cout << *beg;
			}
			else
				cout << ' ' << *beg;
		}
	}
};
int main()
{
	question1019 question(cin);
	question.Process();
	question.Print();
}
void question1019::Process()
{
	unsigned tem = N;
	while (tem)//计算N的b进制数，并倒序存入num数组中
	{
		num.push_back(tem % b);
		tem /= b;
	}
	int compareTimes = num.size() / 2;//从两侧到中间进行对比，如果是奇数，正中央的数不用对比。
	for (int i = 0; i < compareTimes; i++)
	{
		if (num[i] != num[num.size() - 1 - i])
		{
			answer = "No";
			break;
		}
	}
}
