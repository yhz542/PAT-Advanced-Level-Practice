#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#define INFINITE (2<<24)
using namespace std;
class PublicBike
{
	unsigned maxCap, totalNumStation, indexOfProblemStation, quantityOfRoad;
	vector<int> curNumBike;//存储每个自行车站点当前的自行车数量
	vector<vector<unsigned>> graph;//存储两个站点之间的距离权重
	//管理中心到问题站点的最短可选路线。vector<number>储存number站的前一个可选站点,最短路劲可能有多条
	vector<vector<unsigned>> pred;
	//用于深度优先搜索，遍历存储每条最短路径的过程结点
	vector<unsigned> dfsBuffer;
	//用于深度优先搜索遍历满足题目要求的最短路劲，由于是倒序存放，需要倒叙输出
	vector<unsigned> bestRoad;//如果dfsBuffer中存储的路径比bestRoad存储的路径更优，则用dfsBuffer中的结果对其进行替换
	unsigned FindMin(vector<unsigned>&,vector<unsigned>&);//用于最短路径搜索，每次取出当前移动距离最短的结点
	unsigned in, out;//存储最终需要从管理中心发出，和带回管理中心的自行车数量
public:
	void GetInput(void);//用于获取输入
	PublicBike() :maxCap(0), totalNumStation(0), indexOfProblemStation(0), quantityOfRoad(0),in(INFINITE),out(INFINITE) {};
	void Solve();
	void DFS(unsigned,unsigned,unsigned);
};

int main()
{
	PublicBike hangZhou;
	hangZhou.GetInput();
	hangZhou.Solve();
}

void PublicBike::GetInput(void)//获取输入
{
	cin >> maxCap >> totalNumStation >> indexOfProblemStation >> quantityOfRoad;
	pred.resize(totalNumStation+1);
	dfsBuffer.reserve(totalNumStation + 1);
	graph.resize(totalNumStation + 1,vector<unsigned> (totalNumStation+1,INFINITE));//图初始化权重
	curNumBike.reserve(totalNumStation);
	for (unsigned i = 0,currentNum, perfectCondition = maxCap >> 1; i < totalNumStation; ++i)
	{
		cin >> currentNum;
		curNumBike.push_back(currentNum-perfectCondition);
		graph[i][i] = 0;
	}
	for (unsigned i = 0,S1,S2,T12; i < quantityOfRoad; ++i)
	{
		cin >> S1 >> S2 >> T12;
		graph[S1][S2] = T12;
		graph[S2][S1] = T12;
	}
}
/**********************************************************************************************
寻找距离最短的结点
输入：1.当前还剩下的结点数组 2.到每个结点的最短距离数组
输出：最小距离的结点标号
本函数用的是桶排序的思想，每次取完后，将最小距离结点放的剩余数组的最后面，
然后删除，以此降低数组规模，加快运行速度，代价是需要有一个额外的数组
**************************************************************************************************/
unsigned PublicBike::FindMin(vector<unsigned> &vertexRemain,vector<unsigned> &shortest)//寻找移动距离最小地节点
{
	unsigned vertex = INFINITE;
	unsigned indexOfVertex = INFINITE;
	for (unsigned index = 0, distance = INFINITE; index < vertexRemain.size(); ++index)//遍历还剩下的结点数组寻找距离最短的点
	{
		if (shortest[vertexRemain[index]] < distance)
		{
			distance = shortest[vertexRemain[index]];//更新最小距离
			vertex = vertexRemain[index];//更新结点
			indexOfVertex = index;//更新最短距离结点在还剩下结点数组中的下标
		}
	}
	if(INFINITE != vertex)
	{
		vertexRemain[indexOfVertex] = vertexRemain[vertexRemain.size() - 1];//将最小距离结点放到数组的最后一个位置
		vertexRemain.pop_back();//将集合的规模减一，从当前还剩下结点的集合中删除最小距离结点
	}
	return vertex;
}
void PublicBike::Solve()
{
	vector<unsigned> shortest(totalNumStation+1,INFINITE);//存储到每个结点的最短距离
	shortest[0] = 0;//初始结点的距离设置为0
	unsigned vertexMinDistance = 0;//用于存储最短距离结点的下标
	vector<unsigned> vertexRemain;//用于存储当前没有走过的结点的数组
	vertexRemain.reserve(totalNumStation + 1);
	for (unsigned i = 0; i < totalNumStation + 1; ++i)//初始化剩余结点数组
	{
		vertexRemain.push_back(i);
	}
	while (!vertexRemain.empty())//最短路径计算，将最短路径遍历后的结果存储于pred中
	{
		vertexMinDistance = FindMin(vertexRemain,shortest);//每次取出一个距离最短的结点
		if (INFINITE == vertexMinDistance)
			break;
		for (unsigned v = 0,temIndex=0; v < vertexRemain.size(); ++v)//遍历还剩下的结点数组
		{
			temIndex = vertexRemain[v];
			//如果tem结点的最小距离 大于 当前取出的距离最短的结点 加上 该点到tem结点的距离，那么更新tem结点的最短距离
			if (shortest[temIndex] > shortest[vertexMinDistance] + graph[vertexMinDistance][temIndex])
			{
				shortest[temIndex] = shortest[vertexMinDistance] + graph[vertexMinDistance][temIndex];//更新距离
				pred[temIndex].clear();//清除通往tem结点的前一个结点
				pred[temIndex].push_back(vertexMinDistance);//将当前取出的距离最短结点设置为tem结点的前一个结点
			}
			//如果tem结点的最小距离 等于 当前取出的距离最短的结点 加上 该点到tem结点的距离 ,那么将更新通往tem结点的前一个结点的数组集合
			else if (shortest[temIndex] == shortest[vertexMinDistance] + graph[vertexMinDistance][temIndex])
			{
				pred[temIndex].push_back(vertexMinDistance);
			}
		}
	}
	DFS(0,0,indexOfProblemStation);
	//打印输出最终结果
	cout << in << " 0";
	for (auto beg = bestRoad.crbegin()+1 ;beg!=bestRoad.crend();beg++)
	{
		cout << "->" <<*beg;
	}
	 cout <<  " "<<out << endl;
}

void PublicBike::DFS(unsigned takeBack,unsigned sendOut,unsigned curVertex)
{
	dfsBuffer.push_back(curVertex);
	if (!curVertex)
	{
		if (in > sendOut|| in == sendOut && out > takeBack)
		{
			in = sendOut;
			out = takeBack;
			bestRoad = dfsBuffer;
		}
		dfsBuffer.pop_back();
		return;
	}
	else
	{
		int curDivert = curNumBike[curVertex-1];
		if (curDivert > 0)//要带回去的
		{
			if (!sendOut)
			{
				takeBack += curDivert;
			}
			else
			{
				if ((int)sendOut > curDivert)
					sendOut -= curDivert;
				else
				{
					takeBack += (curDivert - sendOut);
					sendOut = 0;
				}
			}
		}
		else if (curDivert < 0)
		{
			sendOut += (-curDivert);
		}
		if (!pred[curVertex].empty())
		{
			for (auto elem : pred[curVertex])
			{
				DFS(takeBack,sendOut,elem);
			}
		}
	}
	dfsBuffer.pop_back();
}
/*
测试用例
10 4 4 5
4 8 9 0
0 1 1
1 2 1
1 3 2
2 3 1
3 4 1

输出： 1 0->1->2->3->4 2
*/
