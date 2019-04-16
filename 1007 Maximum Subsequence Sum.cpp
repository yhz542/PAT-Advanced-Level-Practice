#include <iostream>
#include <vector>
#include <memory>
#define Min -65535
using namespace std;
unique_ptr<int []> MaxSeqSum(const vector<int> &);
int main()
{
	int K;
	cin >> K;
	vector<int> seq(K);
	for (auto &elem : seq)
	{
		cin >> elem;
	}
	unique_ptr<int[]> result = MaxSeqSum(seq);
	printf("%d %d %d", result[0], result[1], result[2]);
	result.reset();
}
unique_ptr<int []> MaxSeqSum(const vector<int> &seq)
{
	int maxSum = Min, temSum = Min;
	int tem, First, Last;
	for (auto beg = seq.cbegin(), end = seq.cend(); beg != end; ++beg)
	{
		if (temSum < 0)
		{
			temSum = *beg;
			tem = *beg;
		}
		else
			temSum += *beg;
		if (temSum > maxSum)
		{
			maxSum = temSum;
			Last = *beg;
			First = tem;
		}
	}
	if (maxSum < 0)
	{
		maxSum = 0;
		First = seq[0];
		Last = seq[seq.size() - 1];
	}
	unique_ptr<int[]>  result(new int[3]{ maxSum,First,Last });
	return result;
}
