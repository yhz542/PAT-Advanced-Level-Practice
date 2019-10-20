#include <iostream>//自己写的最早版本，实话说，逻辑较为复杂不太满意。
#include<vector>
#include<queue>
#include<cstdio>
using namespace std;
typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> MinHeap;
void GetInput(int &, int &, int &, int &, vector<int> &,vector<int> &);
void FillInsideYellowLine(vector<queue<int>> & ,int, int,int);
void InitializeWindowHeap(MinHeap &, const vector<int>&,int ,int);
void CalculateTime(vector<queue<int>> &,MinHeap &, int ,int,int,vector<int> &,vector<int> &);
int main()
{
	int numberOfWindows, theMaxCapOfEachWindow, numberOfCustomers, numberOfCustomerQueries;
	vector<int> processTimeOfCustomer;
	vector<int> customersOfQuery;
	GetInput(numberOfWindows, theMaxCapOfEachWindow, numberOfCustomers,
		numberOfCustomerQueries, processTimeOfCustomer, customersOfQuery);
	vector<queue<int>> insideYellowLine(numberOfWindows);//存放所有窗口黄线内的顾客
	FillInsideYellowLine(insideYellowLine, numberOfCustomers, numberOfWindows, theMaxCapOfEachWindow);
	MinHeap windowHeap;//最小堆，每次取出处理时间最短的顾客
	InitializeWindowHeap(windowHeap, processTimeOfCustomer, numberOfWindows, numberOfCustomers);
	vector<int> startTime(numberOfCustomers);
	CalculateTime(insideYellowLine,windowHeap,numberOfCustomers,numberOfWindows,theMaxCapOfEachWindow, processTimeOfCustomer, startTime);
	int time;
	for (auto beg = customersOfQuery.cbegin(); beg != customersOfQuery.cend(); ++beg)
	{
		time = startTime[*beg-1];
		if (time >= 540)
			printf("Sorry\n");
		else
		{
			int hour = (time + processTimeOfCustomer[*beg-1])/ 60;
			int minute = (time + processTimeOfCustomer[*beg - 1]) % 60;
			printf("%02d:%02d\n", 8 + hour, minute);
		}
	}

}
/*获取输入数据*/
void GetInput(int &numberOfWindows, int &theMaxCapOfEachWindow, int &numberOfCustomers,
	int &numberOfCustomerQueries, vector<int> &processTimeOfCustomer, vector<int> &customersOfQuery)
{
	cin >> numberOfWindows >> theMaxCapOfEachWindow >> numberOfCustomers >> numberOfCustomerQueries;
	processTimeOfCustomer.reserve(numberOfCustomers);
	for (int i = 0, temTime; i < numberOfCustomers; ++i)
	{
		cin >> temTime;
		processTimeOfCustomer.push_back(temTime);
	}
	customersOfQuery.reserve(numberOfCustomerQueries);
	for (int i = 0, customerNumber; i < numberOfCustomerQueries; ++i)
	{
		cin >> customerNumber;
		customersOfQuery.push_back(customerNumber);
	}
}
/*初始化填充黄线内的空间
参数：黄线以内顾客编号的队列，顾客的数目，窗口的数目，每个窗口的黄线内容量
功能：根据顾客的数目，将顾客放进黄线内。只会用一次。
*/
void FillInsideYellowLine(vector<queue<int>> &insideYellowLine, int numberOfCustomers, int windowNum,int CapOfEachWindow)
{
	int num = (windowNum*CapOfEachWindow < numberOfCustomers ? 
		windowNum * CapOfEachWindow : numberOfCustomers);
	for (int customerIndex = 0; customerIndex < num ; ++customerIndex)
	{
		insideYellowLine[customerIndex%windowNum].push(customerIndex);
	}
}
void InitializeWindowHeap(MinHeap &windowHeap,const vector<int>&processTimeOfCustomer,int numberOfWindows,int numberOfCustomers)
{
	int num = (numberOfCustomers < numberOfWindows ? numberOfCustomers : numberOfWindows);
	for (int i = 0; i < num; ++i)
	{
		windowHeap.push(make_pair(processTimeOfCustomer[i], i));
	}
}

void CalculateTime(vector<queue<int>> &insideYellowLine,MinHeap &windowHeap, int numberOfCustomers,int numberOfWindows,int capOfWindow, vector<int> &processTime,vector<int> &startTime)
{
	int restCustomers = numberOfCustomers - numberOfWindows * capOfWindow;
	restCustomers = (restCustomers > 0 ? restCustomers : 0);
	int windowDone = -1 ; 
	int customerDone = -1;
	vector<int> windowTime(numberOfWindows, 0);//每个窗口当前处理的时间
	if (restCustomers)//如果黄线外还有人
	{
		int firstWaitCustomer = numberOfWindows * capOfWindow;
		int newCustomer = -1 ;
		while (restCustomers)//创建一个窗口数组存放每个窗口的当前时间，窗口的时间是相互独立的。
		{
			windowDone = windowHeap.top().second;//从窗口中选出处理时间最短的窗口
			windowHeap.pop();
			customerDone = insideYellowLine[windowDone].front();//从队列中取出该窗口的完成业务的顾客（即首顾客)。
			insideYellowLine[windowDone].pop();//弹出以完成业务的顾客
			startTime[customerDone] = windowTime[windowDone] ;//存入该顾客的开始时间
			windowTime[windowDone] += processTime[customerDone];
			//窗口加入新的顾客，并且黄线外等待的顾客加入窗口中。
			//窗口加入新的顾客。
			newCustomer = insideYellowLine[windowDone].front();
			windowHeap.push(make_pair(processTime[newCustomer]+ windowTime[windowDone], windowDone));
			//黄线外的顾客加入黄线内中
			insideYellowLine[windowDone].push(firstWaitCustomer);
			++firstWaitCustomer;
			restCustomers--;
		}
	}
	//黄线外无人，即只处理黄线内
	restCustomers =( numberOfCustomers < ( numberOfWindows * capOfWindow) ?
		numberOfCustomers: (numberOfWindows * capOfWindow));
	while (restCustomers--)
	{
		windowDone = windowHeap.top().second;//从窗口中选出处理时间最短的窗口
		windowHeap.pop();
		customerDone = insideYellowLine[windowDone].front();//从队列中取出该窗口的完成业务的顾客（即首顾客)。
		insideYellowLine[windowDone].pop();//弹出以完成业务的顾客
		startTime[customerDone] = windowTime[windowDone];//存入该顾客的完成时间
		windowTime[windowDone] += processTime[customerDone];
		//处理完顾客的窗口如果黄线内还有顾客，则将其加入处理的最小堆中。
		if (!insideYellowLine[windowDone].empty())
		{
			int newCustomer = insideYellowLine[windowDone].front();
			windowHeap.push(make_pair(processTime[newCustomer]+ windowTime[windowDone], windowDone));
		}
	}
}
//不错的测试用例 https://blog.csdn.net/allisonshing/article/details/101025724
/*
2 2 7 5
1 2 6 4 3 534 2
3 4 5 6 7
输出1（符合原题输出）：

08:07
08:06
08:10
17:00
Sorry
输入2：

2 2 7 7
2 4 2 4 534 534 2
1 2 3 4 5 6 7
输出2：

08:02
08:04
08:04
08:08
16:58
25:52
08:10
输入3：

2 2 7 7
3 3 3 3 533 534 2
1 2 3 4 5 6 7
输出3：

08:03
08:03
08:06
08:06
16:59
17:00
17:01
输入4：

2 2 7 7
540 1 1 1 1 1 1
1 2 3 4 5 6 7
输出4：

17:00
08:01
Sorry
08:02
08:03
08:04
08:05

*/
