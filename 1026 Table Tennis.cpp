//写的很乱
/******************************
思路：简单来说分情况
1.球桌全部是空的
该情况下按照顾客是否是vip分情况讨论
1)是vip 把编号最小的vip空位分给他。如果没有vip空位，按照第二种情况处理
2)不是vip 在空位中找出编号最小的空位分给他
2.球桌不空
这种情况下要进一步分情况讨论
1)如果有空位，此时继续按照1的方式
2)座位以满
此时将剩余客户中第一个客户的到达时间 和 球桌上第一个到点的时间进行比较。
如果客户先来。
检查第一个到点的球桌是否为vip球桌。
如果是vip球桌
则此时以第一个到点的球桌时间为截至时间，找出在此之前所有等待的顾客，找寻第一个vip用户，如果没找到，则选取第一个等待的客户
如果不是vip球桌
直接选取第一个等待的客户
如果球桌先到点 则直接腾出球桌。
*******************************/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<forward_list>
#define NOEXIST 65535
typedef unsigned int uint;
typedef uint table;
typedef uint index;
using namespace std;
struct timerecord
{
	uint arrivetime;
	uint P;
	uint waittime;
	bool VIP;
	timerecord(uint h, uint m, uint s, uint p, uint tag) :arrivetime(h*3600+m*60+s), P(p),waittime(0), VIP(tag) 
	{
		if (arrivetime < 8 * 3600)
		{
			waittime = 8 * 3600 - arrivetime;
		}
	}
	bool operator<(const timerecord &other) const
	{
			return arrivetime < other.arrivetime;
	}
	void print()
	{
		uint h = arrivetime / 3600;
		uint m = arrivetime % 3600 / 60;
		uint s = arrivetime % 3600 % 60;
		printf("%02u:%02u:%02u ", h, m, s);
		uint endtime =arrivetime + waittime;
		h = endtime / 3600;
		m = endtime % 3600 / 60;
		s = endtime % 3600 % 60;
		uint waitminute = (waittime+30) / 60;
		printf("%02u:%02u:%02u %u\n", h, m, s,waitminute);
	}
};
struct cmp
{
	const vector<timerecord> &copy;
	cmp(const vector<timerecord> &source):copy(source){}
	bool operator()(const pair<index, table> &a, const pair<index, table> b)
	{
		const timerecord &A = copy[a.first];
		const timerecord &B = copy[b.first];
		return A.arrivetime + A.P * 60 +A.waittime> B.arrivetime + B.P * 60+B.waittime;
	}
};
class pta1026
{
	uint N,K,M;
	set<uint> viptable;
	set<uint> remainVIPTable;
	set<uint> availabletable;
	vector<timerecord> data;
	vector<index> recordindex;
	vector<pair<index, table>> tableInfo;
	forward_list<index> remainedplayer;
	vector<uint> cnt;
	bool IsTableFull()
	{
		return availabletable.size() == 0;
	}
	bool IsTableEmpty()
	{
		return availabletable.size() == K;
	}
	bool IsVIPtable(table i)
	{
		return viptable.find(i) != viptable.end();
	}
	void TableEmptyProcess(index &,table &);
	void TableTimeOutProcess(index &, table &);
	void DelTable(table tableindex)
	{
		if (IsVIPtable(tableindex))
			remainVIPTable.erase(tableindex);
		availabletable.erase(tableindex);
	}
public:
	void GetInput();
	void Solve();
	void Output();
};
int main()
{
	pta1026 question;
	question.GetInput();
	question.Solve();
	question.Output();
}
void pta1026::GetInput()
{
	cin >> N;
	data.reserve(N);
	recordindex.reserve(N);
	uint h, m, s, p, tag;
	for (uint i = 0; i < N; ++i)
	{
		scanf_s("%2u:%2u:%2u %u %u", &h, &m, &s, &p, &tag);
		if (h >= 21)
			continue;
		if (p > 120)
			p = 120;
		data.push_back(timerecord(h, m, s, p, tag));
	}
	cin >> K >> M;
	cnt.resize(K, 0);
	for (uint i = 0; i < K; ++i)
		availabletable.insert(i+1);
	for (uint i = 0,vip; i < M; ++i)
	{
		cin >> vip;
		viptable.insert(vip);
		remainVIPTable.insert(vip);
	}
	for (int i = data.size() - 1; i >= 0; --i)
		remainedplayer.push_front(i);
}
void pta1026::Solve()
{
	sort(data.begin(),data.end());//对所有顾客按抵达时间进行排序。
	while ( !remainedplayer.empty() )
	{
		index playerindex=NOEXIST;//开始打球的顾客
		table tablenum;
		if (IsTableEmpty())//如果所有球台都是空的
		{
			TableEmptyProcess(playerindex,tablenum);//第一种情况
		}
		else//如果球台不空,查看第一个到点的顾客和排队第一的顾客时间
		{
			timerecord &out = data[tableInfo.front().first];
			timerecord &in = data[remainedplayer.front()];
			uint outtime = out.arrivetime + out.P * 60+out.waittime;//到点时间
			uint intime = in.arrivetime;//开始排队时间
			if (outtime <= intime)//如果球台上的人先到点，则先把球桌空出来
			{
				TableTimeOutProcess(playerindex, tablenum);//第二种情况
			}
			else//如果顾客先到
			{
				if (IsTableFull())//第三种情况 当前球桌已满 这种情况会出现 顾客等待的情况
				{
					if (outtime >= 75600)
						break;
					//等到第一个时间到点的球桌
					pop_heap(tableInfo.begin(),tableInfo.end(),cmp(data));
					tablenum = tableInfo.back().second;
					if (IsVIPtable(tablenum))//如果是vip桌子，要在等待队伍里看是否有vip
					{
						playerindex = remainedplayer.front();
						auto before = remainedplayer.before_begin();
						auto beg = remainedplayer.begin();
						for (; beg != remainedplayer.end(); ++beg)
						{
							if (data[*beg].arrivetime > outtime)
								break;
							if (data[*beg].VIP)
							{
								playerindex = *beg;
								break;
							}
							before = beg;
						}
						if (playerindex == remainedplayer.front())
						{
							tableInfo.back()=(make_pair(playerindex, tablenum));
							remainedplayer.pop_front();
						}
						else//顾客是vip
						{
							tableInfo.back()=(make_pair(playerindex, tablenum));
							remainedplayer.erase_after(before);
						}
					}
					else//如果不是vip桌子，直接把第一个排队的客人加进来。
					{
						playerindex = remainedplayer.front();
						tableInfo.back()=make_pair(playerindex, tablenum);
						remainedplayer.pop_front();
					}
					data[playerindex].waittime +=( outtime - data[playerindex].arrivetime);
					push_heap(tableInfo.begin(), tableInfo.end(), cmp(data));
				}
				else//还有空余的球桌
				{
					playerindex = remainedplayer.front();
					if (data[playerindex].VIP)//如果新到的客人是vip
					{//查看是否有vip座位
						if (!remainVIPTable.empty())//有vip球桌
							tablenum = *remainVIPTable.begin();
						else//没有vip球桌
							tablenum = *availabletable.begin();
					}
					else//新到客人不是vip
						tablenum= *availabletable.begin();
					tableInfo.push_back(make_pair(playerindex, tablenum));//将客人分配到球桌上
					push_heap(tableInfo.begin(), tableInfo.end(), cmp(data));
					DelTable(tablenum);//删除该球桌
					remainedplayer.pop_front();//删除该顾客
				}
			}
		}
		if (playerindex != NOEXIST)
		{
			data[playerindex].print();
			cnt[tablenum-1]++;
		}
	}
}
void pta1026::Output()
{
	bool flag = 1;
	for (auto elem : cnt)
	{
		if (flag)
		{
			flag = 0;
			cout << elem;
		}
		else
			cout << ' ' << elem;
	}
}
void pta1026::TableEmptyProcess(index &playerindex,table &tablenum)
{
	playerindex = remainedplayer.front();//选取第一个到的顾客
	if (data[playerindex].VIP)//如果该顾客是vip
		tablenum = *remainVIPTable.begin();//选取号码最小的可用vip球桌
	else
		tablenum = *availabletable.begin();
	DelTable(tablenum);//删除该可用球桌
	tableInfo.push_back(make_pair(playerindex, tablenum));//将等待的顾客加入开始计时的球桌中
	push_heap(tableInfo.begin(), tableInfo.end(), cmp(data));
	remainedplayer.pop_front();//将排队的第一个顾客去除
}
void pta1026::TableTimeOutProcess(index &playerindex, table &tablenum)
{
	tablenum = tableInfo.front().second;
	availabletable.insert(tablenum);
	if (IsVIPtable(tablenum))
		remainVIPTable.insert(tablenum);
	pop_heap(tableInfo.begin(), tableInfo.end(), cmp(data));
	tableInfo.pop_back();
}
/*************************
有用的测试用例以及说明
测试点3是有一个21点来的人。

测试点4是有人想打超过2个小时，题目说了只能打最多2小时。

测试点8 等待时间四舍五入

//vip桌子分配例子，有vip桌子时，优先把vip分到编号小的vip桌子，而不是编号小的vip桌子
4
06:00:00 30 1
08:00:00 30 1
10:00:00 30 1
12:00:00 30 1
5 1
3
答案为：
06:00:00 08:00:00 120
08:00:00 08:00:00 0


10:00:00 10:00:00 0
12:00:00 12:00:00 0
1 0 3 0 0


//边缘测试例子
1
21:00:00 10 1
3 3
1 2 3
答案为：
0 0 0

//超过两小时的例子
2
18:00:00 180 1
20:00:00 60 1
1 1
1
答案为：
18:00:00 18:00:00 0
20:00:00 20:00:00 0
2

//关于四舍五入为1分钟的例子，大约等于30秒才+1分钟，小于30则不+
3
07:59:31 60 1
07:59:29 60 1
08:00:30 100 1
2 1
1
答案为：
1
07:59:29 08:00:00 1
07:59:31 08:00:00 0
08:00:30 09:00:00 60
2 1

9
20:52:00 10 0
08:00:00 20 0
08:02:00 30 0
20:51:00 10 0
08:10:00 5 0
08:12:00 10 1
20:50:00 10 0
08:01:30 15 1
20:53:00 10 1
10 10
1 2 3 4 5 6 7 8 9 10
08:00:00 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:10:00 08:10:00 0
08:12:00 08:12:00 0
20:50:00 20:50:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
20:53:00 20:53:00 0
2 2 2 2 1 0 0 0 0 0

2
10:00:00 30 1
12:00:00 30 1
5 1
3
输出正确结果应为：
10:00:00 10:00:00 0
12:00:00 12:00:00 0
0 0 2 0 0
*************************/
