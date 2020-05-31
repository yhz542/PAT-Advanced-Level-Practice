//没什么好说的 动态规划，开一个二维数组，利用floyed的思想进行动态规划，当前最长长度等于前一个的最长长度加1，纵轴代表当前的彩带长度下，order到自己
//的最长长度值。说的不清楚以后再补充
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;
typedef unsigned int uint;
class pta1045
{
	int N,M,L;
	vector<int> order;
	vector<bool> isFavorite;
	vector<int> stripe;
	vector<vector<uint>> length;
public:
	pta1045(istream &in)
	{
		in >> N >> M ;
		isFavorite.resize(N+1,false);
		order.reserve(M);
		uint temcolor;
		for (size_t i = 0; i < (uint)M; ++i)
		{
			in >> temcolor;
			order.push_back(temcolor);
			isFavorite[temcolor] = true;
		}
		in >> L;
		for (size_t i = 0; i < (uint)L; ++i)
		{
			in >> temcolor;
			if(isFavorite[temcolor])
				stripe.push_back(temcolor);
		}
		length.resize(M, vector<uint>(stripe.size(), 0));
	}
	void Solve()
	{
		if (order[0] == stripe[0])
			length[0][0] = 1;
		for (size_t i = 1; i < (uint)M; ++i)
		{
			length[i][0] = length[i - 1][0];
			if (stripe[0] == order[i])
				++length[i][0];
		}
		for (size_t i = 1; i < stripe.size(); ++i)
		{
			length[0][i] = length[0][i - 1];
			if (order[0] == stripe[i])
				 ++length[0][i];
		}
		for (size_t i = 1; i < (uint)M; ++i)
		{
			for (size_t j = 1; j < stripe.size(); ++j)
			{
				length[i][j] = (length[i - 1][j] > length[i][j - 1] ? length[i - 1][j] : length[i][j - 1]);
				if (order[i] == stripe[j])
				{
					++length[i][j];
				}
			}
		}
	}
	void Print()
	{
		cout << length[order.size() - 1][stripe.size() - 1] << endl;
	}
};
int main()
{
	pta1045 *question  = (pta1045 *)malloc(sizeof(pta1045));
	new (question) pta1045(cin);
	question->Solve();
	question->Print();
}
