#include<iostream>
#include<memory>
#include<cstdio>
enum {W,T,L};
using namespace std;
int main()
{
	allocator<float> alloc;
	float *const data = alloc.allocate(9);
	float temInput;
	for (size_t i = 0; i < 9; ++i)
	{
		cin >> temInput;
		alloc.construct(data+i, temInput);
	}
	float result = 1.f,tem=0.f;
	for (int i = 0,choice; i < 3; ++i)
	{
		tem = 0.f;
		for (int j = 0; j < 3; ++j)
		{
			if (tem < data[i * 3 + j])
			{
				tem = data[i * 3 + j];
				choice = j;
			}
		}
		printf("%c ", choice == W ? 'W' :( choice == T ? 'T' : 'L'));
		result *= tem;
	}
	printf("%.2f", (result*0.65 - 1) * 2);
	for (int i = 8; i >= 0; --i)
	{
		alloc.destroy(data + i);
	}
	alloc.deallocate(data, 9);
}
