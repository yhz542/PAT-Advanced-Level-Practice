#include<stdio.h>
#include<stdlib.h>
typedef unsigned int uint;
uint coins[1001];
int compare(const void* p1, const void* p2)
{
	return *((uint*)p1) - *((uint*)p2);
}
int main()
{
	uint N, M;
	scanf("%u %u", &N, &M);
	uint *inputData = (uint *)malloc(sizeof(uint) * N);
	uint value;
	for (size_t index = 0; index < N; ++index)
	{
		scanf("%u", &value);
		coins[value]++;
		inputData[index] = value;
	}
	qsort(inputData, N, sizeof(uint), compare);
	uint i;
	uint flag = 0;
	for ( i = 0; i < N; ++i)
	{
		if (inputData[i] > M / 2)
		{
			flag = 1;
			break;
		}
		else
		{
			--coins[inputData[i]];
			if (coins[M - inputData[i]])
			{
				flag = 2;
				break;
			}
		}
	}
	if (!flag || flag == 1)
		printf("No Solution\n");
	else
		printf("%d %d\n", inputData[i], M - inputData[i]);
	free(inputData);
}
