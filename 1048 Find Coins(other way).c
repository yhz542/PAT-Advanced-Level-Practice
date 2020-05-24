#include<cstdio>
#include<cstdlib>
typedef unsigned int uint;
int compare(const void* p1, const void* p2)
{
	return *((uint*)p1) - *((uint*)p2);
}
int main()
{
	uint N, M;
	scanf("%u %u", &N, &M);
	uint* inputData = (uint*)malloc(sizeof(uint) * N);
	uint value;
	for (size_t index = 0; index < N; ++index)
	{
		scanf("%u", &value);
		inputData[index] = value;
	}
	qsort(inputData, N, sizeof(uint), compare);
	const uint* head = inputData;
	const uint* tail = inputData + N-1;
	uint sum = 0;
	while (head < tail)
	{
		sum = *head + *tail;
		if (sum < M)
			head++;
		else if (sum > M)
			tail--;
		else
			break;
	}
	if (head >= tail)
		printf("No Solution\n");
	else
		printf("%u %u", *head, *tail);
	free(inputData);
}
