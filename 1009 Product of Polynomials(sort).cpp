/* 如果测试点0无法通过可以尝试一下以下测试数据
测试点0
3 2 2 2 -2 1 5
1 1 1
1 3 5.0
*/
#include <iostream>
#include <vector>
#include<algorithm>
#include<set>
#include<cstdio>
using namespace std;
struct term
{
	int exponent;
	double coefficient;
};
int main()
{
	int K1, K2;
	cin >> K1;
	vector<term> poly1(K1);
	for (auto &elem : poly1)
	{
		cin >> elem.exponent>>elem.coefficient;
	}
	cin >> K2;
	vector<term> poly2(K2);
	for (auto &elem : poly2)
	{
		cin >> elem.exponent >> elem.coefficient;
	}
	vector<term> data;
	data.reserve(K1*K2);
	for (auto beg1 = poly1.cbegin(); beg1 != poly1.cend(); ++beg1)
	{
		for (auto beg2 = poly2.cbegin(); beg2 != poly2.cend(); ++beg2)
		{
			data.push_back({beg1->exponent+beg2->exponent,beg1->coefficient*beg2->coefficient});
		}
	}
	sort(data.begin(), data.end(), [](const term& one, const term& two) { return one.exponent > two.exponent; });
	int fmrExp = data[0].exponent;
	int curExp;
	double fmrCoef=0., curCoef=0.;
	int index = 0;
	for (auto &elem : data)
	{
		curCoef = elem.coefficient;
		curExp = elem.exponent;
		if (curExp == fmrExp)
			curCoef += fmrCoef;
		else if (fmrCoef)
			{
				data[index].exponent = fmrExp;
				data[index].coefficient = fmrCoef;
				++index;
			}
		fmrExp = curExp;
		fmrCoef = curCoef;
	}
	if (fmrCoef)
	{
		data[index].exponent = fmrExp;
		data[index].coefficient = fmrCoef;
		++index;
	}
	printf("%d", index);
	for (auto beg = data.cbegin(),end=beg+index; beg != end; ++beg)
	{
		printf(" %d %.1f", beg->exponent, beg->coefficient);
	}
}
//思路：先将所有项求出并存储起来，然后从大到小排序，然后合并同指数项。如果系数为0，则略去这一项。最后依次输出，由于K的值最大为10 所以该方法最多也只有
//10*10 =100项，如果K可以取值很大，则该方法过于占用内存。
//网上有一种 直接利用指数构造数组的方法，因为指数最高取到1000，所以多项式的乘积指数最高为2000，利用这一点可以直接构造一个2001的数组。下标对应指数值
//缺点一样，如果指数值上不封顶，则该方法就不好用了。
