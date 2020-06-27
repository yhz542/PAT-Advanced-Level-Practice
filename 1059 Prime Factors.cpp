#include<cstdlib>//可优化
#include <cstdio>
#include<vector>
#include<cmath>
using ulint = unsigned long int;
using uint = unsigned int;
using namespace std;
class pta1059
{
	struct prime
	{
		uint num;
		uint cnt;
		prime(uint n ,uint c):num(n),cnt(c){}
	};
	ulint N;
	vector<prime> primeFactor;
	bool IsPrime(unsigned long Num)//更好的方法。质数一定是被6整除余1或者余5的数(1除外)
	{
		if (Num <= 3)
			return Num > 1;
		if (Num % 6 != 1 && Num % 6 != 5)
			return false;
		long long range = (long long)sqrt(Num);
		for (int i = 5; i < range; i += 6)
			if (Num % i == 0 || Num % (i + 2) == 0)//%i 表示6x+5 %(i+2)表示 6x+7也就是6x+1
				return false;
		return true;
	}
	void process(ulint &curN,uint num)
	{
		if (curN % num == 0)
		{
			primeFactor.push_back(prime(num, 0));
			while (!(curN % num))
			{
				curN /= num;
				++primeFactor[primeFactor.size() - 1].cnt;
			}
		}
	}
public:
	pta1059()
	{
		scanf("%lu", &N);
	}
	void Solve()
	{
		ulint curN = N;
		process(curN,2);
		process(curN,3);
		uint num;
		for (size_t i = 1; curN !=1 ; ++i)//可以process一次，输出一次，如果cnt=0,就不输出
		{
			num = 6 * i - 1;
			if (IsPrime(num))
				process(curN,num);
			num = 6 * i + 1;
			if (IsPrime(num))
				process(curN,num);
		}
	}
	void Print()//优化点，可边计算边输出，不需要算完后，再输出，如果边计算边输出，占用的空间复杂度是O(1)
	{
		printf("%lu=",N);
		if (1==N)
			printf("1");
		else
		{
			printf("%u", primeFactor[0].num);
			if (primeFactor[0].cnt != 1)
				printf("^%u", primeFactor[0].cnt);
		}
		for (size_t i = 1 ; i < primeFactor.size() ;++i)
		{
			printf("*%u",primeFactor[i].num);
			if (primeFactor[i].cnt != 1)
				printf("^%u", primeFactor[i].cnt);
		}
	}
};
int main()
{
	pta1059* question = (pta1059*)malloc(sizeof(pta1059));
	new (question)pta1059();
	question->Solve();
	question->Print();
}
