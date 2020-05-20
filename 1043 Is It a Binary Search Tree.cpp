#include<iostream>
#include<vector>
typedef unsigned int uint;
using namespace std;
class pta1042
{
	uint N;
	vector<int> preorder;
	vector<int> postorder;
	bool flag;
	void Deal(uint pre_index,uint pos_index, uint size)
	{
		if (size>0)
		{
			postorder[pos_index+size-1] = preorder[pre_index];
			uint boundry;
			uint cnt1 = 0;
			for (boundry = pre_index + 1; boundry < pre_index+size; ++boundry)
			{
				if (preorder[boundry] >= preorder[pre_index])
					break;
				cnt1++;
			}
			uint cnt2 = 0;
			for (size_t i = boundry ; i < pre_index + size ; ++i)
			{
				if (preorder[i] < preorder[pre_index])
				{
					flag = false;
					return;
				}
				cnt2++;
			}
			Deal(pre_index + 1, pos_index,cnt1);
			if (!flag)
				return;
			Deal(boundry, pos_index+ cnt1 , cnt2);
		}
	}
	void MirrorDeal(uint pre_index, uint pos_index, uint size)
	{
		if (size > 0)
		{
			postorder[pos_index + size - 1] = preorder[pre_index];
			uint boundry;
			uint cnt1 = 0;
			for (boundry = pre_index + 1; boundry < pre_index + size; ++boundry)
			{
				if (preorder[boundry] < preorder[pre_index])
					break;
				cnt1++;
			}
			uint cnt2 = 0;
			for (size_t i = boundry; i < pre_index + size; ++i)
			{
				if (preorder[i] >= preorder[pre_index])
				{
					flag = false;
					return;
				}
				cnt2++;
			}
			MirrorDeal(pre_index + 1, pos_index, cnt1);
			if (!flag)
				return;
			MirrorDeal(boundry, pos_index + cnt1, cnt2);
		}
	}
public:
	pta1042(istream& in) :flag(true)
	{
		in >> N;
		preorder.reserve(N);
		postorder.resize(N, 0);
		uint tem;
		for (size_t i = 0; i < N; ++i)
		{
			in >> tem;
			preorder.push_back(tem);
		}
	}
	void Solve()
	{
		Deal(0, 0, N);
		if (!flag)
		{
			flag = true;
			MirrorDeal(0, 0, N);
		}
	}
	void Print()
	{
		bool isFirst = true;
		if (flag)
		{
			cout << "YES" << endl;
			for (auto elem : postorder)
			{
				if (isFirst)
				{
					cout << elem;
					isFirst = false;
				}
				else
					cout << ' ' << elem;
			}
		}
		else
			cout << "NO" << endl;
	}
};
int main()
{
	pta1042 question(cin);
	question.Solve();
	question.Print();
}
