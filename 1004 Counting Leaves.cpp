#include<iostream>//BFS广度优先 由于不确定输入顺序，所以要先读取输入 然后再遍历对各个结点的深度进行计算整理 最后输出
#include<vector>
#include<map>
using namespace std;
struct node
{
	int parent = 0;//父节点
	int level = -1;//当前的层次等级
	int numOfChild = 0;//子结点数目
	vector<int> child;//连接的子结点
};
int main()
{
	int N, M;
	cin >> N >> M;
	vector<node> data(N + 1);
	data[1].parent = 0;
	data[1].level = 0;
	int ID, K, temp;
	for (int i = 0; i < M; ++i)
	{
		cin >> ID >> K;
		data[ID].numOfChild = K;
		data[ID].child.resize(K);
		for (int j = 0; j < K; ++j)
		{
			cin >> temp;
			data[ID].child[j] = temp;
			data[temp].parent = ID;
		}
	}
	vector<int> store;
	store.reserve(100);
	store.push_back(1);
	int deepth = 0;//用于存储最大深度。
	while (!store.empty())
	{
		int IDnow = store.back();
		store.pop_back();
		int levelCur = data[IDnow].level;
		if (deepth < levelCur)
			deepth = levelCur;
		for (auto element : data[IDnow].child)
		{
			store.push_back(element);
			data[element].level = levelCur+1;
		}
	}
	vector<int> output(deepth+1, 0);
	for (int i = 1; i < N + 1; ++i)
	{
		node dataNow = data[i];
		if(!dataNow.numOfChild)
			output[dataNow.level]++;
	}
	cout << output[0];
	for (unsigned i = 1 ; i<output.size();++i )
		cout << ' ' <<output[i] ;
}
