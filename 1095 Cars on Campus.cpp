#include <cstdio> //总体写的复杂度较高，再给我一次机会可能不会再采用这种方法解题。
#include <vector>//推荐柳婼的解题思路，对in out记录成对处理。   https://www.liuchuo.net/archives/2951
#include <cstdlib>
#include <algorithm>
#include<map>
#include<string>
#include<set>
using namespace std;
#define in true
#define out false
#define invalid -1
typedef bool parkStatus;
class pta1095
{
	typedef struct timeInfo//用于记录每个车的进入时间和停留时间 用于计算最长停留时间
	{
		int inTime;
		int allTime;
	}timeInfo;
	typedef struct record
	{
		char plate_number[9];//车排名
		int time;
		parkStatus status;//状态 in or out
	}record;
	struct compare//桶排序的比较类
	{
		vector<record>& cpy;
		compare(vector<record> &src):cpy(src){}
		bool operator()(int a, int b)
		{
			return cpy[a].time < cpy[b].time;
		}
	};
	int N, K;
	vector<record> records;
	vector<int>       index;
	vector<int> queries;
	map<string, timeInfo> parktime;
	int longestTime = -1;
	record& getRecordFromIndex(int ind)//由于使用桶排序 所以中间中转了一个下标，这里是通过下标直接返回记录
	{
		int indexOfRecords = index[ind];
		return records[indexOfRecords];
	}
public:
	pta1095()
	{
		scanf("%d %d", &N, &K);
		records.resize(N);
		index.reserve(N);
		char in_out[4];
		short hour, min, sec;
		for (int i = 0; i < N; ++i)
		{
			scanf("%s %2hd:%2hd:%2hd %s", records[i].plate_number, 
		    &hour, &min, &sec, in_out);
			records[i].time = (hour * 60 + min) * 60 + sec;
			records[i].status = (in_out[0] == 'i' ? in : out);
			index.push_back(i);
		}
		queries.resize(K);
		for (int i = 0; i < K; ++i)//此处可优化，和display中的函数合并处理，降低时间复杂度
		{
			scanf("%2hd:%2hd:%2hd", &hour, &min, &sec);
			queries[i] = (hour * 60 + min) * 60 + sec;
		}
	}
	void solve()
	{
		map<string, int> plate_num2index;
		sort(index.begin(), index.end(), compare(records));//桶排序 可以节约大量时间，但是会提升代码的阅读难度以及复杂性
		int formerIndex;
		for (int indexOfIndex = 0 ; indexOfIndex < N ;++indexOfIndex)
		{
			record& cur = getRecordFromIndex(indexOfIndex);
			auto curPlate2Index = plate_num2index.find(cur.plate_number);
			if (curPlate2Index == plate_num2index.end())//如果车还没有进入校园
			{
				if (cur.status == in)//如果该车进入
				{
					plate_num2index[cur.plate_number] = indexOfIndex;
					if (parktime.find(cur.plate_number) == parktime.end())//创建进入时间
						parktime[cur.plate_number] = { cur.time ,0 };
					else
						parktime[cur.plate_number].inTime = cur.time;
				}
				else
					index[indexOfIndex] = invalid;
			}
			else//如果该车已经进入校园
			{
				formerIndex = plate_num2index[cur.plate_number];
				if (cur.status == out)//本次记录为出去
				{
					plate_num2index.erase(curPlate2Index);
					auto& temParkTime = parktime[cur.plate_number];//计算停留时间
					temParkTime.allTime += (cur.time - temParkTime.inTime);//计算该车的总停留时间
					if (longestTime < temParkTime.allTime)//更新最长时间
					{
						longestTime = temParkTime.allTime;
					}
				}
				else//本次记录为进入
				{
					index[formerIndex] = invalid;///将上次记录设置为非法
					curPlate2Index->second = indexOfIndex;//更新车的进入记录为本次
					parktime[cur.plate_number].inTime = cur.time;//更新进入的记录时间
				}
			}
		}
		for (auto& item : plate_num2index)//如果进入的记录没有出去的记录配对，将其置为非法记录，这里的处理显然较为复杂，推荐用柳婼的成对处理，复杂度低易于维护
		{
			formerIndex = plate_num2index[item.first];
			index[formerIndex] = invalid;
		}
	}
	void converthms(int time)
	{
		char h, m, s;
		h = time / 3600;
		m = (time / 60) % 60;
		s = time % 60;
		printf("%02d:%02d:%02d\n", h, m, s);
	}
	void display()
	{
		int indexOfIndex = 0;
		int ind;
		int cnt = 0;
		for (auto querytime : queries)
		{
			while (indexOfIndex < N)
			{
				ind = index[indexOfIndex];
				if (ind != invalid)//如果记录非法 直接处理下一条
				{
					auto& record = records[ind];
					if (querytime < record.time)//如果记录时间大于查询时间，退出循环 输出计数结果
					{
						break;
					}
					if (record.status == in)
					{
						++cnt;
					}
					else
					{
						--cnt;
					}
				}
				++indexOfIndex;
			}
			printf("%d\n", cnt);
		}
		
		for (auto &item : parktime)
		{
			if (longestTime == item.second.allTime)
				printf("%s ", item.first.c_str());
		}
		
		converthms(longestTime);//输出最长时间
	}
	~pta1095()
	{
		
	}
};
int main()
{
	pta1095* question = (pta1095*)malloc(sizeof(pta1095));
	new(question) pta1095();
	question->solve();
	question->display();
	question->~pta1095();
	free(question);
}
