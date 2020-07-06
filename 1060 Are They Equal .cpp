#include<cstdlib>
#include <cstdio>
#include<vector>
#include<string>
#include<iostream>
using uint = unsigned int;
using namespace std;
class pta1060
{
	int N;
	struct info
	{
		string source;
		string num;
		int exp = 0;
		info() = default;
	};
	info A, B;
	void filterZero(string& str)//过滤输入一开始无用的0
	{
		uint index = A.source.find_first_not_of('0');
		A.source = A.source.substr(index);
		index = B.source.find_first_not_of('0');
		B.source = B.source.substr(index);
	}
	int findDot(string &str)//寻找点的位置，如果找到了，返回点的下标，没找到返回-1
	{
		int indexDot = 0;
		char tem = str[str.size() - 1];
		str[str.size() - 1] = '.';
		while(str[indexDot]!='.')
		{
			indexDot++;
		}
		str[str.size() - 1] = tem;
		if (str[indexDot] != '.')
			indexDot = -1;
		return indexDot;
	}
	int findFirstNum(string& str)//寻找第一个有效的非0数，找到了返回该数的下标，没找到返回-1
	{
		int indexNum = 0;
		char tem = str[str.size() - 1];
		str[str.size() - 1] = '1';
		while (str[indexNum] == '0'||str[indexNum]=='.')
		{
			++indexNum;
		}
		str[str.size() - 1] = tem;
		if (str[indexNum] == '0' || str[indexNum] == '.')
			indexNum = -1;
		return indexNum;
	}
	void calcul(info &str)//计算函数
	{
		bool dotExisted = false;
		bool noneZero = false;
		int indexDot = findDot(str.source);
		if (indexDot != -1)
			dotExisted = true;
		int indexNum = findFirstNum(str.source);
		if (indexNum != -1)
			noneZero = true;//如果没找到有效的非零数，说明这个数就是0
		if (!noneZero)//输入为0
		{
			for(size_t i = 0 ; i< N;++i)//直接在输出的字符串中填N个0即可
				str.num.push_back('0');
			str.exp = 0;//幂设置为0
		}
		else
		{
			for (int i = 0, curIndex = indexNum; i < N &&curIndex<str.source.size(); ++i,curIndex++)//i代表有效位数
			{
				if (str.source[curIndex] == '.')//如果是点，则不计为有效位
				{
					--i;
					continue;
				}
				else
					str.num.push_back(str.source[curIndex]);
			}
			while (str.num.size() != N)//如果距离N个有效数还未填满，补0
			{
				str.num.push_back('0');
			}
			if (!dotExisted)//如果没找到点,那么点的位置可以理解为字符串最后一个有效下标的后面一位
				indexDot = str.source.size();
			int expon = indexDot - indexNum;//计算幂的方法 用点的下标减去第一个有效数的下标
			if (expon < 0)//如果点在有效数前面出现，则将幂加1
				expon++;
			str.exp = expon;
		}
	}
public:
	pta1060()
	{
		cin >> N >> A.source >> B.source;
		A.num.reserve(N);
		B.num.reserve(N);
	}
	void Solve()
	{
		calcul(A);
		calcul(B);
	}
	void Print()
	{
		if (A.num == B.num && A.exp == B.exp)
		{
			cout << "YES" << " 0." << A.num << "*10^" << A.exp << endl;
		}
		else
		{
			cout << "NO"<< " 0." << A.num << "*10^" << A.exp << " 0." << B.num << "*10^" << B.exp << endl;
		}
	}
};
int main()
{
	pta1060* question = (pta1060*)malloc(sizeof(pta1060));
	new (question)pta1060();
	question->Solve();
	question->Print();
}
/************
测试点
3 12300 12358.9
YES 0.123*10^5


1 12300 12358.9
YES 0.1*10^5


1 1.2300 1.23589
YES 0.1*10^1


5 1.2300 1.23589
NO 0.12300*10^1 0.12358*10^1


4 0.01234 0.012345
YES 0.1234*10^-1


5 0.01234 0.012345
NO 0.12340*10^-1 0.12345*10^-1


5 0.1234 0.12345
NO 0.12340*10^0 0.12345*10^0


0 0.11 0
YES 0.*10^0或者YES 0.0*10^0，都可以AC，测试点应该没有这个例子


1 0.1 0
NO 0.1*10^0 0.0*10^0


1 0.0 0.1
NO 0.0*10^0 0.1*10^0


1 0.0 0.000
YES 0.0*10^0


1 00.0 0.000
YES 0.0*10^0


4 00.0 0.000
YES 0.0000*10^0


5 00.0 0.000
YES 0.00000*10^0


1 05.0 5.000
YES 0.5*10^1


1 00.01 0.010
YES 0.1*10^-1
————————————————
版权声明：本文为CSDN博主「昔之得一者」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/lannister_awalys_pay/article/details/90451536
*************/
