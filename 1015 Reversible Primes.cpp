#include <iostream>//题目的意思是将10进制的数换算成D进制的数后再反向判断其是否是素数。
#include <cmath>
using namespace std;
bool GetInput(int &, int &);
bool IsPrime(long long Num);
int main()
{
	int N, D;
	int mod ;
	while (GetInput(N, D))
	{
		bool reversiblePrime = false;
		int reversibleNum = 0;
		if (IsPrime(N))
		{
			while(N)
			{
				reversibleNum *= D;
				mod = N % D;
				reversibleNum += mod;
				N /= D;
			}
			if(IsPrime(reversibleNum))
				reversiblePrime = true;
		}
		cout << ( reversiblePrime ? "Yes" : "No" ) << endl ;
	}
	return 0;
}
bool GetInput(int &N, int &D)
{
	cin >> N;
	if (N < 0)
		return false;
	cin >> D;
	return true;
}
bool IsPrime(long long Num)//更好的方法。质数一定是被6整除余1或者余5的数(1 2 3除外)
{
	if (Num <= 3)
		return Num > 1;
	if (Num % 6 != 1 && Num % 6 != 5)
		return false;
	long long range = (long long)sqrt(Num);
	for (int i = 5; i < range; i += 6)
		if (Num%i == 0 || Num % (i + 2) == 0)
			return false;
	return true;
}
