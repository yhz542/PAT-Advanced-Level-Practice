#include <iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstdio>
using namespace std;
void BFS(int node, vector<vector<bool>> &isConnected,vector<bool> &visited)//广度优先搜索
{
	visited[node] = true;
	queue<int> Q;
	Q.push(node);
	int vertex;
	while (!Q.empty())
	{
		vertex = Q.front();
		Q.pop();
		for (size_t i = 0; i < visited.size(); ++i)
		{
			if (!visited[i] && isConnected[vertex][i])
			{
				visited[i] = true;
				Q.push(i);
			}
		}
	}
}
int main()
{
	int N, M, K;
	cin >> N>> M>> K;
	vector<vector<bool>> isConnected(N,vector<bool> (N,false));//邻接矩阵
	for (int i = 0,city1,city2; i < M; ++i)
	{
		cin >> city1 >> city2;
		--city1;
		--city2;
		isConnected[city1][city2] = true;
		isConnected[city2][city1] = true;
	}
	vector<int> cityConcerned;
	cityConcerned.reserve(K);//读入被占领的城市
	for (int i = 0,city; i < K; ++i)
	{
		cin >> city;
		cityConcerned.push_back(city-1);
	}
	vector<bool> visited(N, false);
	for (auto lostCity : cityConcerned)
	{
		visited[lostCity] = true;//将丢失的城市设置为已访问，则BFS/DFS就不会访问这个结点城市，也不会透过这个结点城市访问其他城市。
		int ncc = 0;//the number of connected component 连通分量数目
		for (int i = 0; i < N; ++i)
		{
			if (!visited[i])
			{
				BFS(i, isConnected,visited);//运行一次BFS代表图中有一组连通分量
				ncc++;
			}
		}
		fill(visited.begin(), visited.end(), false);//重置visited
		printf("%d\n", ncc-1);
	}
}
/*思路
用高速公路连接成的城市可以看成无向无权图。通过广度优先或者深度优先搜索查询该图中有几个连通分量，每个连通分量可以看成图中的一个点，一张n个点的图至少需要
n-1条边构成连通图，所以最终需要添加的边数为连通分量数目-1
*/
