#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <map>
#include <algorithm>
#define HOURNUM 24
using namespace std;
class record
{
public:
	unsigned month;
	unsigned day;
	unsigned hour;
	unsigned minute;
	bool isOnLine;
	record(int mon, int d, int h, int min, string &oof) :month(mon), day(d), hour(h), minute(min) 
	{
		isOnLine = ("on-line" == oof ? true : false);
	}
};
struct cmp
{
	cmp(const vector<record> &data) :info(data) {}
	bool operator()(int a, int b)
	{
		if (info[a].month != info[b].month)
		{
			return info[a].month < info[b].month;
		}
		else if (info[a].day != info[b].day)
		{
			return info[a].day < info[b].day;
		}
		else if (info[a].hour != info[b].hour)
		{
			return info[a].hour < info[b].hour;
		}
		else
			return info[a].minute < info[b].minute;
	}
private:
	const vector<record> &info;
};
void GetInput(vector<int> &,int &, map<string, vector<record>> &);
void Process(vector<int> &, map<string, vector<record>> &);
void Sort(vector<int> & ,const vector<record> &);
void OutputResult(vector<int> &,const pair<string,vector<record>> &,vector<int> &);
bool CalculateCost(const record &,const record &,const vector<int> &,float &,unsigned &);
unsigned CalculateCost(const record &, const vector<int> &);
int main()
{
	vector<int> theHourPrice;
	int N; 
	map<string, vector<record>> info;
	GetInput(theHourPrice, N, info);
	Process(theHourPrice, info);
	return 0;
}
void GetInput(vector<int> &theHourPrice , int &N , map<string, vector<record>> &info)//读取输入
{
	theHourPrice.reserve(HOURNUM);
	for (int i = 0,price; i < HOURNUM; ++i)
	{
		cin >> price;
		theHourPrice.push_back(price);
	}
	cin >> N;
	string name;
	int month, day, hour, minute;
	string onOrOff;
	for (int i = 0; i < N; ++i)
	{
		cin >> name;
		scanf("%2d:%2d:%2d:%2d ", &month, &day, &hour, &minute);
		cin >> onOrOff;
		info[name].push_back(record(month, day, hour, minute, onOrOff));
	}
}
void Process(vector<int> &theHourPrice, map<string, vector<record>> &info)
{
	vector<vector<int>> order(info.size());//存储每个人的时间数据序列
	int index = 0;
	for (auto beg = info.cbegin(); beg != info.cend(); ++beg)
	{
		Sort(order[index], beg->second);//对每个人的数据进行排序，因为数据结构中的成员比较多，所以采用桶排序
		OutputResult(order[index], *beg, theHourPrice);//利用排序后结构进行逻辑判断并输出结果。
		index++;
	}
}
void Sort(vector<int> &subOrder, const vector<record> &data)//桶排序，对每个人的电话数据按时间排序
{
	int length = data.size();
	//桶排序
	subOrder.reserve(length);
	for (int i = 0; i < length; ++i)
	{
		subOrder.push_back(i);
	}
	sort(subOrder.begin(), subOrder.end(), cmp(data));
}
void OutputResult(vector<int> &order,const pair<string,vector<record> >&info,vector<int> &price)
{
	const string &name = info.first;
	const vector<record> &data = info.second;
	bool isfirst = true;
	if (data.empty())/风险规避处理，如果该人无时间数据直接返回。
		return;
	float sum = 0.f;//总花费
	const record *start =NULL,*end = NULL ;
	bool onLine = false, offLine = false;
	for (unsigned i = 0,index; i < order.size(); ++i)
	{
		index = order[i];
		if (data[index].isOnLine)//上线
		{
			onLine = true;
			offLine = false;
			start = &data[index];
		}
		else//下线
		{
			end = &data[index];
			if (onLine)//只有前面一个数据是上线才表示这是一对有效数据
			{
				float thisCost = 0;
				unsigned time = 0;
				if (CalculateCost(*start, *end, price,thisCost,time))//如果该数据为有效数据，但是有效时间为0，即上线时间等于下线时间，也不输出结果
				{
					if (isfirst)//只有每个人第一次有效数据才打印名字
					{
						printf("%s %02d\n", name.c_str(), data[0].month);
						isfirst = false;
					}
					printf("%02u:%02u:%02u %02u:%02u:%02u %u $%.2f\n", start->day, start->hour, start->minute,
						end->day, end->hour, end->minute, time, thisCost);
					sum += thisCost;
				}
			}
			onLine = false;
			offLine = true;
		}
	}
	if (sum)//累计总值不为0，即输出
	{
		printf("Total amount: $%.2f\n", sum);
	}
}
bool CalculateCost(const record &start, const record &end, const vector<int> &price,float &cost,unsigned &time)
{
//本函数用于计算一对有效数据的有效时间以及开销
	unsigned numOfDay = 0;
	numOfDay = end.day - start.day;
	time = (numOfDay * 24 + end.hour - start.hour)*60+end.minute-start.minute;
	if (time)
	{
		unsigned costPerDay = 0;
		for (unsigned index = 0; index < price.size(); ++index)
		{
			costPerDay += price[index];
		}
		costPerDay *= 60;
		unsigned costNeedDelete = CalculateCost(start, price);
		//计算小时
		unsigned costNeedAdd = CalculateCost(end, price);
		cost =( costPerDay * numOfDay - costNeedDelete + costNeedAdd)/100.f;
		return true;
	}
	else
		return false;
}
unsigned CalculateCost(const record &data, const vector<int> &price)
{
	unsigned cost = 0;
	//计算小时
	unsigned i = 0;
	for (; i < data.hour; ++i)
	{
		cost += price[i];
	}
	cost *= 60;
	cost += data.minute*price[i];
	return cost;
}
