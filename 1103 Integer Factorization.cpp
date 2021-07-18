#include <cstdio>
#include <vector>
#include <cstdlib>
#include<cmath>
#include<csetjmp>
using namespace std;
class pta1103
{
	bool flag;
	short N, K,P;
	short startNum,sum,factorSum,maxfactorSum;
	vector<short> num;
	vector<short> powOfNum;
	vector<short> curNum;
	vector<short> answer;
	void DFS(short order,short upLimit)
	{
		if (order >= K)
			return;
		while (sum < N && curNum[order]< upLimit)//第二步剪枝 如果当前数组的和大于等于N直接返回
		{
			sum -= powOfNum[curNum[order]];
			factorSum -= curNum[order];
			++curNum[order];
			factorSum+= curNum[order];
			sum += powOfNum[curNum[order]];
			DFS(order + 1, curNum[order]);
		}
		if (sum == N)
		{
			if (!flag)
			{
				maxfactorSum = factorSum;
				answer = curNum;
			}
			else if (maxfactorSum == factorSum)
			{
				if (curNum[order] > answer[order])
					answer = curNum;
			}
			else if (maxfactorSum < factorSum)
			{
				maxfactorSum = factorSum;
				answer = curNum;
			}
			flag = true;
		}
		sum -= powOfNum[curNum[order]];
		factorSum -= curNum[order];
		curNum[order] = 1;
		sum++;
		factorSum++;
	}
public:
	pta1103():sum(0),flag(false),factorSum(0)
	{
		short tem = 0 ;
		scanf("%hd %hd %hd", &N, &K, &P);
		short upLimit = (short)pow(N, (double)1 / P);
		num.reserve(upLimit + 1);
		powOfNum.reserve(upLimit + 1);
		curNum.resize(K);
		for (short i = 0; i <= upLimit; ++i)
		{
			num.push_back(i);
			powOfNum.push_back((short)pow(i, P));
		}
		startNum = (short)pow(N/K,1/(double)P);//第一步剪枝，不必从1开始
		fill(curNum.begin(), curNum.end(), startNum);
	}
	void solve()
	{
		for (auto i : curNum)
		{
			sum += powOfNum[i];
		}
		DFS(0, (short)num.size() - 1);
	}

	void display()
	{
		if (flag)
		{
			printf("%hd = %hd^%hd",N,answer[0],P);
			for (size_t i = 1; i < curNum.size(); ++i)
			{
				printf(" + %hd^%d", answer[i],P);
			}
		}
		else
		{
			printf("Impossible");
		}
	}
	~pta1103()
	{

	}
};
int main()
{
	pta1103* question = (pta1103*)malloc(sizeof(pta1103));
	new(question) pta1103();
	question->solve();
	question->display();
	question->~pta1103();
	free(question);
}
