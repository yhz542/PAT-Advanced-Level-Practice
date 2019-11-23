#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
#define OPENTIME (8*60*60)
typedef unsigned int uint;
struct info//这里存储的数据全部是按秒为单位
{
	uint arriveTime;
	uint processTime;
	info( uint t, uint pt) :arriveTime(t), processTime(pt) {}
	bool operator<(const info &tem)
	{
		return this->arriveTime < tem.arriveTime;
	}
};
vector<info> &GetInput(uint &,uint &);
void Process(vector<info>&,uint K);
int main()
{
	uint N, K;
	vector<info>& customerData = GetInput(N, K);
	sort(customerData.begin(), customerData.end());
	Process(customerData,K);
	delete &customerData;
}
vector<info> &GetInput(uint &N,uint &K)//读取输入
{
	cin >> N >> K ;
	vector<info> *customerData = new vector<info>();
	for (uint i = 0, hour = 0, minute = 0, second = 0, processTime = 0 ,arriveTime = 0 ; i < N; ++i)
	{
		scanf_s("%2u:%2u:%2u %u", &hour, &minute, &second, &processTime);//因为调试用的vs，所以不支持scanf,提交的时候改为scanf即可通过编译
		if (hour >= 17)//不读入到达银行时间超过17点的顾客数据
		{
			if (0 != minute || 0 != second || 17 != hour)
				continue;
		}
		arriveTime = (hour * 60 + minute) * 60 + second;
		customerData->push_back(info(arriveTime,processTime*60));
	}
	return *customerData;
}
void Process( vector<info>&data,uint K)
{
	uint numberOfPeople =data.size();
	uint length = numberOfPeople < K ? numberOfPeople : K;//处理人数少于窗口数的情况
	int waitTime;
	uint waitTimeSum = 0;//最终的等待时间,输出结果
	vector<uint> minHeap;//存储窗口时间数据的的最小堆
	uint minValue = 0;//从最小堆中取出的最先结束的窗口时间数据
	minHeap.reserve(length);
//下面处理配合上面的三目运算符,实际上处理了两种场景，分别是实际处理人数少于窗口数以及实际人数
//大于等于窗口数的情况。这里将本来分开处理的语句改变边界情况一起处理了。
	for (uint i = 0,time; i < length; ++i)
	{
		time =data[i].arriveTime;
		if (time < OPENTIME)
		{
			waitTime= OPENTIME - time;
			waitTimeSum += waitTime;
			time = OPENTIME;
		}
		time += data[i].processTime;
		minHeap.push_back(time);
	}
	make_heap(minHeap.begin(), minHeap.end(),greater<uint>());//构建最小堆
	for (int i = K,time; i < numberOfPeople; ++i)//判断时间是否在八点之后
	{
		time = data[i].arriveTime;
		pop_heap(minHeap.begin(), minHeap.end(),greater<uint>());
		minValue = minHeap.back();//取出堆顶的最先结束窗口的时间
		waitTime = minValue - time;//计算本次即将进入咨询的顾客的等待时间
		if (waitTime < 0)
		{
			waitTime = 0;
			minValue = time;
		}
		waitTimeSum += waitTime;
		minHeap.back() = minValue + data[i].processTime ;
		push_heap(minHeap.begin(), minHeap.end(), greater<uint>());//将本次顾客的结束时间加入堆中
	}
	printf("%.1f", (float)waitTimeSum/numberOfPeople/60  );
}
/*附上几组测试数据，如果能全过基本问题不大
3 3
07:00:00 10
07:20:00 10
07:40:00 10
40.0

1 3
17:00:00 10
0.0

2 1
16:30:00 60
17:00:00 10
15.0

注意的几个点:
1.来的早于八点，也要计算等待时间
2.满足咨询条件的顾客人数小于窗口时的处理
3.晚于下午5点不处理，也不算人数
4.只要来的时间早于下午5点，不论等到几点都要进行计算
大概只想到这么多
上面的代码是简化和优化过的，在牺牲了一定可读性的情况下，提升了运行速度。
*/
