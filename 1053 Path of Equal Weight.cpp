#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<vector>
#include<set>
using namespace std;
typedef unsigned int uint;
vector<int> weight;
class comp
{
public:
	bool operator()(const int& left, const int& right) const
	{
		return weight[left] > weight[right];
	}
};
class pta1053
{
	uint N;
	uint M;
	uint S;
	vector<int> &W;
	vector<multiset<int, comp>> tree;
	vector<uint> answer;
	void solve(uint node,int remain)
	{
		if (remain == W[node])
		{
			if (tree[node].empty())
			{
				bool flag = true;
				for (auto elem : answer)
				{
					if (flag)
					{
						cout << W[elem];
						flag = false;
					}
					else
						cout <<' '<< W[elem];
				}
				cout << endl;
			}
			else
				return;
		}
		else if (remain > W[node])
		{
			for (auto elem : tree[node])
			{
				answer.push_back(elem);
				solve(elem, remain - W[node]);
				answer.pop_back();
			}
		}
		else
			return;
	}
public:
	pta1053(istream &in):W(weight)
	{
		in >> N >> M >> S;
		W.reserve(N);
		tree.resize(N);
		int temValue;
		for (uint index = 0; index < N; ++index)
		{
			in >> temValue;
			W.push_back(temValue);
		}
		uint ID, K,child;
		for (uint i = 0; i < M; ++i)
		{
			in >> ID >> K;
			for (uint j = 0; j < K; ++j)
			{
				in >> child;
				tree[ID].insert(child);
			}
		}
	}
	void Solve()
	{
		uint root = 0;
		answer.push_back(root);
		solve(root,S);
		answer.pop_back();
	}
	void Print()
	{
	}
	~pta1053()
	{}
};
int main()
{
	pta1053 *question  = (pta1053 *)malloc(sizeof(pta1053));
	new (question) pta1053(cin);
	question->Solve();
	question->Print();
	question->~pta1053();
	free(question);
}
