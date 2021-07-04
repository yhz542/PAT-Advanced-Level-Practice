#include <cstdio>//前序遍历后是递增的顺序 对输入的数值进行排序 即可一一对应 ，然后再层次遍历输出即可
#include <vector>
#include <cstdlib>
#include <algorithm>
#include<queue>
using namespace std;
class pta1099
{
	typedef int child;
	typedef struct treeNode
	{
		int value;
		child left;
		child right;
	}treeNode;
	vector<int> treeValue;
	vector<treeNode> tree;
	queue<int> layerTree;
	int valueIndex;
	int N;
	void preOrder(int nodeIndex)
	{
		if (nodeIndex != -1)
		{
			treeNode& curNode = tree[nodeIndex];
			preOrder(curNode.left);
			assign(curNode, treeValue[valueIndex++]);
			preOrder(curNode.right);
		}
	}
	void assign(treeNode& node, int value)
	{
		node.value = value;
	}
public:
	pta1099():valueIndex(0)
	{
		scanf("%d", &N);
		treeValue.resize(N);
		tree.resize(N);
		for (size_t i = 0; i < tree.size(); ++i)
		{
			scanf("%d %d", &tree[i].left, &tree[i].right);
		}
		for (size_t i = 0; i < treeValue.size(); ++i)
		{
			scanf("%d", &treeValue[i]);
		}
	}
	void solve()
	{
		sort(treeValue.begin(), treeValue.end());
		preOrder(0);
		layerTree.push(0);
	}
	
	void display()
	{
		int cur;
		bool flag = true;
		while (!layerTree.empty())
		{
			cur = layerTree.front();
			layerTree.pop();
			if (flag)
			{
				printf("%d", tree[cur].value);
				flag = false;
			}
			else
				printf(" %d", tree[cur].value);
			if (tree[cur].left != -1)
				layerTree.push(tree[cur].left);
			if (tree[cur].right != -1)
				layerTree.push(tree[cur].right);
		}
	}
	~pta1099()
	{
		
	}
};
int main()
{
	pta1099* question = (pta1099*)malloc(sizeof(pta1099));
	new(question) pta1099();
	question->solve();
	question->display();
	question->~pta1099();
	free(question);
}
