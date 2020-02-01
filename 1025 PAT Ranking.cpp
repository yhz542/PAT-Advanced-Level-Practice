//思路 首先分组排序，最后利用最大堆，每次从已排好序的各个组中取出最大的元素放入堆中，直到酱所有组中的元素全部取完为止
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
typedef unsigned int uint;
using namespace std;
struct studentInfo
{
	long long numOfReg;
	uint score;
	uint locationNum;
	studentInfo(long long n,uint sc,uint l):numOfReg(n),score(sc),locationNum(l){}
};
struct cmp
{
private:
	vector<studentInfo> &localInfo;
public:
	bool operator()(uint a, uint b)
	{
		if (localInfo[a].score == localInfo[b].score)
			return localInfo[a].numOfReg > localInfo[b].numOfReg;
		else
			return localInfo[a].score < localInfo[b].score;
	}
	cmp(vector<studentInfo> &local):localInfo(local){}
};
struct heapcmp
{
private:
	vector<vector<studentInfo>> &copy;
public:
	heapcmp(vector<vector<studentInfo>> &source):copy(source){}
	bool operator()(pair<uint, uint> &a, pair<uint, uint> &b)
	{
		uint a1 = a.first, a2 = a.second;
		uint b1 = b.first, b2 = b.second;
		if (copy[a1][a2].score == copy[b1][b2].score)
			return copy[a1][a2].numOfReg > copy[b1][b2].numOfReg;
		else
			return copy[a1][a2].score < copy[b1][b2].score;
	}
};
class pta1025
{
	vector<vector<studentInfo>> info;
	vector<vector<uint>> localorder;
	vector<pair<uint, uint>> heap;
public:
	void GetInput();
	void Solve();
	void Output();
};
int main()
{
	pta1025 question;
	question.GetInput();
	question.Solve();
	question.Output();
}
void pta1025::GetInput()
{
	uint N;
	cin >> N;
	info.resize(N);
	localorder.resize(N);
	long long int numOfReg;
	uint score;
	for (uint i = 0,K=0; i < N; ++i)
	{
		cin >> K;
		info[i].reserve(K);
		localorder[i].reserve(K);
		for (uint j = 0; j < K; ++j)
		{
			cin >> numOfReg >> score;
			info[i].push_back(studentInfo(numOfReg, score,i+1));
			localorder[i].push_back(j);
		}
	}
}
void pta1025::Solve()
{
	set<uint> remainLocal;
	heap.reserve(info.size());
	vector<uint> localHighScore;
	localHighScore.reserve(info.size());
	vector<uint> curorder(info.size(),1);
	for (uint i = 0; i < info.size(); ++i)
	{
		remainLocal.insert(i);
		sort(localorder[i].begin(), localorder[i].end(), cmp(info[i]));//分别对各组进行排序，使用的桶排序
		pair<uint, uint> temdata = make_pair(i, localorder[i].back());
		heap.push_back(temdata);
		localHighScore.push_back(info[i][temdata.second].score);
	}
	make_heap(heap.begin(), heap.end(),heapcmp(info));//建堆
	pair<uint, uint> targetIndex;
	uint order = 0;
	uint count = 0;
	uint highestScore = 101;
	vector<uint> cnt(info.size(), 0);
	uint allnum = 0;
	for (auto elem : info)
	{
		allnum += elem.size();
	}
	printf("%u\n", allnum);
	while (!remainLocal.empty())//使用堆排序每次取出最大的，再将新的放进去
	{
		pop_heap(heap.begin(), heap.end(), heapcmp(info));
		targetIndex = heap.back();
		localorder[targetIndex.first].pop_back();
		if (!localorder[targetIndex.first].empty())
		{
			heap.back() = make_pair(targetIndex.first, localorder[targetIndex.first].back());
			push_heap(heap.begin(), heap.end(),heapcmp(info));
		}
		else
		{
			remainLocal.erase(targetIndex.first);
			heap.pop_back();
		}
		cnt[targetIndex.first]++;
		count++;
		if (info[targetIndex.first][targetIndex.second].score < highestScore)
		{
			highestScore = info[targetIndex.first][targetIndex.second].score;
			order = count;
		}
		if (info[targetIndex.first][targetIndex.second].score < localHighScore[targetIndex.first])
		{
			localHighScore[targetIndex.first] = info[targetIndex.first][targetIndex.second].score;
			curorder[targetIndex.first]=cnt[targetIndex.first];
		}
		printf("%013lld %u ", info[targetIndex.first][targetIndex.second].numOfReg,order); 
		printf("%u %u\n" ,info[targetIndex.first][targetIndex.second].locationNum ,curorder[targetIndex.first]);
	}
}
void pta1025::Output()
{
	
}
