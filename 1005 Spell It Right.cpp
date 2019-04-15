#include <iostream>//需要注意的是输入N最大可以取到10的100次方。一般的整形是放不下这么大的数的。所以需要用字符串存储。另外可以一次读取一个字符
#include <cstdio>//直到读到换行符或者eof停止。这样只需对输入扫描一遍，理论上会更快。
#include <string>
using namespace std;
void NumberToEnglish(int);
void Print(int);
int main()
{
	string N;
	cin >> N;
	int sum = 0;
	for( char elem:N)
	{
		sum += elem - '0';
	}
	Print(sum);
}
inline void NumberToEnglish(int num)
{
	switch (num)
	{
	case 0:
		printf("zero");
		break;
	case 1:
		printf("one");
		break;
	case 2:
		printf("two");
		break;
	case 3:
		printf("three");
		break;
	case 4:
		printf("four");
		break;
	case 5:
		printf("five");
		break;
	case 6:
		printf("six");
		break;
	case 7:
		printf("seven");
		break;
	case 8:
		printf("eight");
		break;
	case 9:
		printf("nine");
		break;
	}
}
void Print(int N)
{
	if (N < 10)
		NumberToEnglish(N);
	else
	{
		Print(N / 10);
		putchar(' ');
		NumberToEnglish(N % 10);
	}
}
