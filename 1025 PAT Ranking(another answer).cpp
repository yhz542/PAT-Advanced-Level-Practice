//另一种复杂度更低的方法。
/* 直接把所有的数据读入进来存储在一个vector中，然后直接全部进行排序
然后根据存储的考场号来进行各个分考场的排名，按照出现的顺序和各自的分数比较来确定其排名
相比之前的方法逻辑更加简单
*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define INFINITE 65535
typedef unsigned int uint;
using namespace std;
struct studentInfo
{
friend struct cmp;
friend class pta1025;
private:
	long long registration_number;
	uint score;
	uint location_number;
public:
	studentInfo(long long a,uint b ,uint c):registration_number(a),score(b),location_number(c){}
};
struct cmp
{
private:
	vector<studentInfo> &copy;
public:
	cmp(vector<studentInfo> &source):copy(source){}
	bool operator()(uint a, uint b)
	{
		if (copy[a].score == copy[b].score)
			return copy[a].registration_number < copy[b].registration_number;
		else
			return copy[a].score > copy[b].score;
	}
};
class pta1025
{
	vector<studentInfo> info;
	vector<uint> group;
	vector<uint> localorder;
	vector<uint> highestScore;
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
	group.resize(N,0);
	highestScore.resize(N,INFINITE);
	long long regNum;
	uint score = 0;
	for (uint i = 0,K=0,cnt=0; i < N; ++i)
	{
		cin >> K;
		info.reserve(info.size() + K);
		for (uint j = 0; j < K; ++j)
		{
			cin >> regNum >> score;
			info.push_back(studentInfo(regNum, score, i+1));
			localorder.push_back(cnt++);
		}
	}
}
void pta1025::Solve()
{
	printf("%u\n", info.size());
	uint curOrder=0;
	uint highScore = INFINITE ;
	vector<uint> groupCnt(group.size(), 0);
	sort(localorder.begin(), localorder.end(),cmp(info));//一次整体性的排序
	for (uint i =  0; i < localorder.size(); ++i)
	{
		auto &curInfo = info[localorder[i]];
		if (curInfo.score < highScore)//确定整体名次
		{
			highScore = curInfo.score;
			curOrder=i+1;
		}
		++groupCnt[curInfo.location_number - 1];
		if (curInfo.score < highestScore[curInfo.location_number - 1])//确定分考场名次
		{
			highestScore[curInfo.location_number - 1] = curInfo.score;
			group[curInfo.location_number - 1] = groupCnt[curInfo.location_number - 1];
		}
		printf("%013lld %u %u %u\n", curInfo.registration_number, curOrder , curInfo.location_number,group[curInfo.location_number - 1]);
	}
}
void pta1025::Output()
{
	
}
