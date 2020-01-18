#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef struct Node* pos;
struct Node
{
	int data=-1;
	pos left=nullptr, right=nullptr;
};
class pta1020
{
	unsigned N;
	vector<unsigned> postorder;
	vector<unsigned> inorder;
	queue<pos> buffer;
public:
	pos answer;
	pta1020(istream& in):answer(nullptr)
	{
		in >> N;
		unsigned tem;
		postorder.reserve(N);
		for (unsigned i = 0; i < N; i++)
		{
			cin >> tem;
			postorder.push_back(tem);
		}
		inorder.reserve(N);
		for (unsigned i = 0; i < N; i++)
		{
			cin >> tem;
			inorder.push_back(tem);
		}
	}
	void Solve(int,int,int,pos * );
	void Print();
	unsigned length()
	{
		return N;
	}
};
int main()
{
	pta1020 question(cin);	
	question.Solve(0, 0, question.length(), &question.answer);
	question.Print();
}
//参数从左至右:后序遍历数组的开始下标，中序遍历数组的开始下标，当前子数组长度，二叉树的当前结点
void pta1020::Solve(int postorderindexstart , int inorderindexstart , int length ,pos *node)//建立二叉树
{
	if (length <= 0)//如果子数组长度为非负数返回
		return;
	if(!(*node))//如果当前的结点不存在，则创造一个结点
		(*node) = new Node;
	unsigned root = postorder[postorderindexstart+length-1];//后续遍历数组的最后一个成员为根节点
	(*node)->data = root;//赋值给当前结点
  //在中序遍历的数组中找到根节点，以此划分左右子树
	auto target = find(inorder.begin() + inorderindexstart, inorder.begin() + inorderindexstart+length , root);
	if (target == inorder.begin() + inorderindexstart + length)//调试用，可以忽略
	{
		cout << "error occur" << endl;
		exit(1);
	}
  //计算根节点在数组中的下标
	int rootIndex = target - inorder.begin();
  //计算左子树包含的元素个数
	int leftlength = rootIndex - inorderindexstart;
  //递归计算左子树
  Solve(postorderindexstart , inorderindexstart,leftlength, &((*node)->left));
	//计算右子树包含的元素个数
  int rightlength = inorderindexstart + length - rootIndex - 1;
  //递归计算右子树
  Solve(postorderindexstart+leftlength , rootIndex+1 ,rightlength, &((*node)->right));
}
void pta1020::Print()//BFS 广度搜索优先，利用队列先进先出进行实现
{
	if (!answer)
		return;
	pos cur = answer;
	cout << cur->data;
	if (cur->left)
		buffer.push(cur->left);
	if (cur->right)
		buffer.push(cur->right);
	while (!buffer.empty())
	{
		cur = buffer.front();
		cout << ' ' << cur->data;
		buffer.pop();
		if (cur->left)
			buffer.push(cur->left);
		if (cur->right)
			buffer.push(cur->right);
	}
}
