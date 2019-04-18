#include<iostream>//链表解法，比较省空间。但是速度较慢。建立一个单向链表，将乘积的结果一项一项的插入链表中。
#include<forward_list>
#include<memory>
#include<cstdio>
using namespace std;
struct term
{
	term(istream &is) { is >> exp >> coef; }
	term(int e, float c) :exp(e), coef(c) {}
	int exp;
	float coef;
};
term *GetInput(int N)
{
	allocator<term> alloc;
	auto ptr = alloc.allocate(N);
	term *tem = ptr;
	for (int i = 0; i < N; ++i)
	{
		alloc.construct(tem++, cin);
	}
	return ptr;
}
shared_ptr<forward_list<term>> Calculate(term * const, term* const, int, int,int &);
int main()
{
	int K1, K2;
	cin >> K1;
	term *const poly1 = GetInput(K1);
	cin >> K2;
	term *const poly2 = GetInput(K2);
	int cnt;
	shared_ptr<forward_list<term>> result=Calculate(poly1,poly2,K1,K2,cnt);
	printf("%d", cnt);
	for (auto beg = result->cbegin(); beg != result->cend(); ++beg)
		printf(" %d %.1f", beg->exp, beg->coef);
}
shared_ptr<forward_list<term>> Calculate(term * const poly1, term* const poly2, int K1, int K2 ,int &cnt)
{
	cnt = 0;
	shared_ptr<forward_list<term>> result = make_shared<forward_list<term>>();
	int exp = 0;
	float coef = 0.f;
	for (auto beg1 = poly1; beg1 != poly1 + K1; ++beg1)
	{
		for (auto beg2 = poly2; beg2 != poly2 + K2; ++beg2)
		{
			exp = beg1->exp + beg2->exp;
			coef = beg1->coef * beg2->coef;
			if (!coef)//如果系数为0直接跳过这一步
				continue;
			else if (result->begin() == result->cend())//如果链表为空，也就是说当前没有任何元素，直接插入
			{
				result->insert_after(result->before_begin(), term(exp, coef));
				++cnt;
			}
			else//链表不空，对里面的元素遍历选择一个位置插入
			{
				forward_list<term>::iterator former=result->before_begin();
				for (auto cur = result->begin(); ; ++cur)
				{
					if (cur == result->end() || exp > cur->exp )//如果需要插入的元素比链表中所有元素都要小 或者 需要插入的元素找到了位置 就插入
					{
						result->insert_after(former, term(exp, coef));
						++cnt;
						break;
					}
					else if (exp == cur->exp)//如果值相等
					{
						cur->coef += coef;
						if (!cur->coef)
						{
							result->erase_after(former);
							--cnt;
						}
						break;
					}
					former = cur;//记录当前的元素迭代器。
				}
			}
		}
	}
	return result;
}
