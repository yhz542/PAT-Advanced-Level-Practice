#include<iostream>//用map解决，写起来更加简单，但是实际运行速度会慢一些。
#include<map>
#include<vector>
#include<memory>
#include<cstdio>
using namespace std;
struct term
{
	term(istream &is) {is >> exp >> coef; }
	int exp;
	float coef;
};
term * GetInput(int N)
{
	allocator<term> alloc;
	auto const poly = alloc.allocate(N);
	term * tem = poly;
	while (tem != poly + N)
		alloc.construct(tem++, term(cin));
	return poly;
}
void Clean(term *const ptr, int N)
{
	allocator<term> alloc;
	for (auto beg = ptr + N; beg != ptr;)
	{
		alloc.destroy(--beg);
	}
	alloc.deallocate(ptr, N);
}
int main()
{
	int K1 = 0 , K2 = 0 ;
	cin >> K1;
	auto const poly1 = GetInput(K1);
	cin >> K2;
	auto const poly2 = GetInput(K2);
	map<int, float> data;
	int exp = 0;
	float coef = 0;
	for (auto beg1 = poly1; beg1 != poly1 + K1; ++beg1)
	{
		for (auto beg2 = poly2; beg2 != poly2 + K2; ++beg2)
		{
			exp = beg1->exp + beg2->exp;
			coef = beg2->coef*beg1->coef;
			if (data.find(exp) == data.end())//如果指数不在data中，将其加入data
			{
				data[exp] = coef;
			}
			else
				data[exp] += coef;//如果指数在data中，累加系数。
			if (data[exp] == 0)//如果系数为0，删除该项
				data.erase(exp);
		}
	}
	cout << data.size();
	for (auto beg = data.rbegin(); beg != data.rend(); ++beg)//逆序输出
		printf(" %d %.1f", beg->first, beg->second);
	Clean(poly1, K1);
	Clean(poly2, K2);
}
