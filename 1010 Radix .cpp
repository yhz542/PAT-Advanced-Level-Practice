#include<iostream>
#include<string>
#include<cctype>
#include<cstdio>
using namespace std;
long long int StrToNum(string &str, long long int radix)//将字符串按照进制来转换成整数。
{
	long long int num = 0;
	int tem = 0, cnt = 0;
	for (auto beg = str.cbegin(); beg != str.cend(); ++beg)
	{
		num *= radix;
		if (isdigit(*beg))
			tem = *beg - '0';
		else
			tem = *beg - 'a' + 10;
		num += tem;
	}
	return num;
}
long long int BinarySearch(long long left, long long right, long long num, string &other)//二分查找
{
	long long radix = 0;
	long long numOther = 0;
	while (left <= right)
	{
		radix = (left + right) / 2;
		numOther = StrToNum(other, radix);
		if (numOther == num)
			return radix;
		else if (numOther > num || numOther < 0)//因为进制可以很大，导致即使是long long也存不下转换后的数据。超出范围后会变成负数。
			right = radix - 1;
		else
			left = radix + 1;
	}
	return 0;//没找到
}
long long int FindRadix(long long int num, string &other)//为另一个字符串寻找合适的radix
{
	char charMax = '0' ;
	for (char elem : other)
	{
		if (elem > charMax)
			charMax = elem;
	}
	long long int radix = 0;
	if (isdigit(charMax))
		radix = charMax - '0' + 1;
	else
		radix = charMax - 'a' + 11;
	radix = BinarySearch(radix, num+1, num,other);
	if (1==radix)
		radix = 2;
	return radix;
}

int main()
{
	string N1, N2,*other;
	int tag;
	long long radix;
	cin >> N1 >> N2 >> tag >> radix;
	long long int num1=0, num2=0;
	if (1 == tag)
	{
		num1 = StrToNum(N1, radix);
		other = &N2;
	}
	else
	{
		num1 = StrToNum(N2, radix);
		other = &N1;
	}
	long long result = FindRadix(num1, *other);
	if (result)
		printf("%lld", result);
	else
		printf("Impossible");
}
/*
几个要点：
1.存整数时一定要使用long long
2.即使long long也会越界。越界后long long会变为负数，二分查找的时候判断的时候需要注意。
3.如果有解，radix最低为2。
4.二分查找的下界是查询字符串中最大字母对应的数字+1，上界应该是已知radix数的十进制数的值.为了处理 0 0 1 10 以及 12 c 1 10这种特殊情况上界+1.
（或者可以分情况处理，如果被查询radix的数只有一位数，那么该数的radix只可能为该数的十进制数+1，即c的radix只可能为13，因为不管radix为多少，都无法改变
c的值。
如果查询的radix有多位数，那么上界就是已知数的十进制数值
参考下文
https://blog.csdn.net/zhoujian_1943/article/details/79341548
）
