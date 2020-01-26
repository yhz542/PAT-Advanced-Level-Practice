#include<iostream>//思路，利用深度优先搜索进行遍历
#include<vector>
#include<forward_list>
using namespace std;
typedef unsigned int uint;
class pta1021
{
	uint N,longestDepth,components,curDepth;//最长的距离，连接分量数目，当前节点作为根节点的最深深度
	vector<uint> deepestNode;//用于存放深度最深的所有根节点的向量组
	vector<forward_list<uint>> edge;//存放边，用的邻接表
	void DFS(uint,vector<bool> &,uint);//深度优先搜索
public:
	void GetInput();
	void Solve();
	void Output();
};
int main()
{
	pta1021 question;
	question.GetInput();
	question.Solve();
	question.Output();
}
void pta1021::GetInput()//初始化以及获取输入数据
{
	curDepth = 0;
	longestDepth = 0;
	components = 0;
	cin >> N;
	edge.resize(N);
	uint node1, node2;
	for (uint i = 0; i < N - 1; ++i)
	{
		cin >> node1 >> node2;
		--node1;
		--node2;
		edge[node1].push_front(node2);
		edge[node2].push_front(node1);
	}
}
void pta1021::Solve()
{
	vector<bool> isVisited(N, false);//所有节点是否遍历过的标志
	for (uint root = 0; root < N; root++)//对所有节点进行探测，如果正常输出，本for循环只运行一遍。
	{
		if (!isVisited[root])
		{
			DFS(root, isVisited, 0);
			components++;//DFS一次，连接分量增加一次。
			longestDepth = curDepth;
			deepestNode.push_back(root);//将当前深度设置为最深深度
		}
	}
	if (1 == components)//如果连接分量为1，也就是连通图
	{
		for (uint root = 1; root < N; ++root)//继续以剩余每个节点为根节点，进行遍历计算最深深度以及相应的根节点
		{
			fill(isVisited.begin(), isVisited.end(), false);
			curDepth = 0;
			DFS(root, isVisited, 0);
			if (curDepth > longestDepth)
			{
				longestDepth = curDepth;
				deepestNode.clear();//如果有新的最深深度，则清空当前储存的最深根节点列表。
				deepestNode.push_back(root);
			}
			else if (curDepth == longestDepth)
				deepestNode.push_back(root);//储存深度相同的根节点
		}
	}
}
void pta1021::DFS(uint node,vector<bool> &isVisited,uint depth)
{
	isVisited[node] = true;//将本节点设置为已访问
	++depth;//深度加1
	for (auto elem : edge[node])//遍历与该节点相连接的节点
	{
		if (!isVisited[elem])//如果该节点没有遍历过
			DFS(elem, isVisited,depth);//进行DFS
	}
	if (depth > curDepth)
		curDepth = depth;
}
void pta1021::Output()
{
	if (components > 1)
	{
		cout << "Error: " << components << " components" << endl;
	}
	else
	{
		for (auto elem : deepestNode)
		{
			cout << elem+1 << endl;
		}
	}
}
//注意只有一个点的特殊情况，该情况下，应该需要输出一个1
