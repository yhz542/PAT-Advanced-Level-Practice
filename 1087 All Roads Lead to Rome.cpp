#include <cstdio>//dijsktra的大杂烩
#include <vector>
#include <cstdlib>
#include <map>
#include<cstring>
using namespace std;
#define INFINITE 65535
class pta1087
{
	typedef struct cityName
	{
		char name[4];
		bool operator ==(const cityName& other) const
		{
			return strcmp(this->name, other.name) == 0;
		}
		bool operator <(const cityName& other) const
		{
			return strcmp(this->name, other.name) < 0;
		}
		cityName(){}
		cityName(const cityName &other)
		{
			strncpy(this->name, name, 4);
		}
		cityName(char* name)
		{
			strncpy(this->name, name, 4);
		}
	}cityName;
	int N, K;
	int* happiness;//除开始城市以外其他城市的愉悦值
	vector<vector<int>> costRoute;//各城市间的开销
	map<int, cityName> num2city;//序号到城市名字的映射
	map<cityName, int> city2num;//城市到序号的映射
	vector<int> shortest;//到各个城市的最小代价
	vector<int> maxhappiness;//到各个城市的最大愉悦值
	vector<int> numOfPassCity;//经过的城市数目
	vector<int> pred;//去每个城市前的一个城市
	vector<int> numOfDifferentRoutes;//前往每个城市的不同走法
	int targetNum;//目的地罗马的序号
	void setMapbetweenCityAndNum(int num, char* cityname)//用于建立序号到城市名字间的映射
	{
		num2city.insert(make_pair( num, cityname));
		city2num.insert(make_pair(cityname, num));
	}
	int FindMin(vector<int>& index)//寻找开销最小的城市序号
	{
		if (0 == index.size())
			return -1;
		int minNodeIndex = 0;
		int minNode;
		for (int nodeIndex = 0; nodeIndex < index.size(); ++nodeIndex)
		{
			int curNode = index[nodeIndex];
			minNode = index[minNodeIndex];
			if (shortest[curNode] < shortest[minNode])
			{
				minNodeIndex = nodeIndex;
			}
		}
		minNode = index[minNodeIndex];
		index[minNodeIndex] = index[index.size() - 1];//将取出的最小距离结点的下标与最后一个元素交换，并将数组规模减1
		index.pop_back();
		return minNode;
	}
	void reverseprintcity(int citynum)//逆序输出
	{
		if (citynum == 0)
		{
			printf("%s", num2city[0].name);
			return;
		}
		reverseprintcity(pred[citynum]);
		printf("->%s", num2city[citynum].name);
	}
public:
	pta1087():happiness(NULL)
	{
		char cityName[4];//开始城市名字
		scanf("%d %d %s", &N, &K,cityName);
		costRoute.resize(N,vector<int>(N,INFINITE+1));//开销初始化 注意 开销的默认值比shortest的默认值要大
		setMapbetweenCityAndNum(0, cityName);//开始城市的序号为0
		happiness = (int*)malloc(sizeof(int) * N );
		happiness[0] = 0;
		int happy;
		for (int i = 1; i < N ; ++i)//记录愉悦值
		{
			scanf("%s %d", cityName, happiness+i);
			setMapbetweenCityAndNum(i, cityName);
		}
		char city1[4], city2[4];
		int num1, num2;
		int cost;
		for (int i = 0; i < K ; ++i)//建立地图
		{
			scanf("%s %s %d", city1, city2, &cost);
			num1 = city2num[city1];
			num2 = city2num[city2];
			costRoute[num1][num2] = costRoute[num2][num1] = cost;
		}
	}
	void solve()
	{
		char targetName[4] = "ROM";
		targetNum = city2num[targetName];
		shortest.resize(N, INFINITE);//注意shortest的默认值比costRoute要小，用于区分两个城市间无路径和开销相同时的处理，减少运算量
		maxhappiness.resize(N, 0);
		numOfPassCity.resize(N, 0);
		numOfDifferentRoutes.resize(N, 0);
		pred.resize(N,-1);
		shortest[0] = 0;//设置起始点到自己的距离为0
		numOfDifferentRoutes[0] = 1;
		vector<int> shortestIndex;
		shortestIndex.reserve(N);
		for (int i = 0; i < N; ++i)
			shortestIndex.push_back(i);
		int curNode = 0;
		while (curNode != targetNum)//点到单点的算法 如果是需要寻找点到所有点的算法需将条件改成shortestIndex.size()
		{
			curNode = FindMin(shortestIndex);//从堆中取出距离远点最近的点
			for (size_t i = 0; i < N; ++i)//遍历当前点的所有边
			{
				if (shortest[curNode] + costRoute[curNode][i] < shortest[i])//如果经过本点到其他点的开销可以缩短
				{
					shortest[i] = shortest[curNode] + costRoute[curNode][i];
					maxhappiness[i] = maxhappiness[curNode] + happiness[i];
					numOfPassCity[i] = numOfPassCity[curNode] + 1;
					pred[i] = curNode;//设置最短路径上其他点的前一个结点为本节点
					numOfDifferentRoutes[i] = numOfDifferentRoutes[curNode];//刷新路径数
				}
				else if (shortest[curNode] + costRoute[curNode][i] == shortest[i])//如果shortest的默认值和costRoute一样 那么由于初始点的shortest值为0，则所有和初始点不连接的城市都会满足条件
				{
					numOfDifferentRoutes[i]+=numOfDifferentRoutes[curNode];//累加路径数
					if (maxhappiness[i] < maxhappiness[curNode] + happiness[i])
					{
						maxhappiness[i] = maxhappiness[curNode] + happiness[i];
						numOfPassCity[i] = numOfPassCity[curNode] + 1;
						pred[i] = curNode;
					}
					else if (maxhappiness[i] == maxhappiness[curNode] + happiness[i])//如果最大愉悦值相同
					{
						if(numOfPassCity[i] > numOfPassCity[curNode] + 1)//并且经过的城市更少 更新路径和经过的城市数
						{
							numOfPassCity[i] = numOfPassCity[curNode] + 1;
							pred[i] = curNode;
						}
					}
				}
			}
		}
	}
	void display()
	{
		printf("%d %d %d %d\n", numOfDifferentRoutes[targetNum], shortest[targetNum],maxhappiness[targetNum], maxhappiness[targetNum]/numOfPassCity[targetNum]);
		reverseprintcity(targetNum);
	}
	~pta1087()
	{
		if (happiness)
		{
			free(happiness);
			happiness = NULL;
		}
	}
};
int main()
{
	pta1087* question = (pta1087*)malloc(sizeof(pta1087));
	new(question) pta1087();
	question->solve();
	question->display();
	question->~pta1087();
	free(question);
}
