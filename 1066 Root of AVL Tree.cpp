#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
using uint = unsigned int;
typedef struct node* pos;
typedef struct node
{
	int value;
	uint height;
	pos left;
	pos right;
	node() :value(0), height(0),left(nullptr), right(nullptr)
	{}
	node(int val):value(val), height(0), left(nullptr), right(nullptr)
	{}
} node;
class pta1066
{
	uint N;
	pos root;
	pos insert(pos tree , int value)
	{
		if (!tree)
		{
			tree = new node(value);
		}
		else
		{
			if (value < tree->value)
			{
				tree->left = insert(tree->left, value);
				if (GetHeight(tree->left) - GetHeight(tree->right) > 1)
				{
					if (value < tree->left->value)
					{
						tree = leftRotate(tree);
					}
					else
					{
						tree->left = rightRotate(tree->left);
						tree = leftRotate(tree);
					}
				}
			}
			else if (value > tree->value)
			{
				tree->right = insert(tree->right, value);
				if (GetHeight(tree->right) - GetHeight(tree->left) > 1)
				{
					if (value > tree->right->value)
					{
						tree = rightRotate(tree);
					}
					else
					{
						tree->right = leftRotate(tree->right);
						tree = rightRotate(tree);
					}
				}
				//右旋
			}
			else
				return nullptr;
			tree->height = (GetHeight(tree->left) > GetHeight(tree->right) ? GetHeight(tree->left) : GetHeight(tree->right)) + 1;
		}
		return tree;
	}
	int GetHeight(pos tree)
	{
		if (!tree)
			return -1;
		else
			return tree->height;
	}
	pos leftRotate(pos tree)
	{
		pos tem = tree->left;
		tree->left = tem->right;
		tem->right = tree;
		tree->height = (GetHeight(tree->left) > GetHeight(tree->right) ? GetHeight(tree->left) : GetHeight(tree->right)) + 1;;
		tem->height = (GetHeight(tem->left) > GetHeight(tem->right) ? GetHeight(tem->left) : GetHeight(tem->right)) + 1;
		return tem;
	}
	pos rightRotate(pos tree)
	{
		pos tem = tree->right;
		tree->right = tem->left;
		tem->left = tree;
		tree->height = (GetHeight(tree->left) > GetHeight(tree->right) ? GetHeight(tree->left) : GetHeight(tree->right)) + 1;;
		tem->height = (GetHeight(tem->left) > GetHeight(tem->right) ? GetHeight(tem->left) : GetHeight(tem->right)) + 1;
		return tem;
	}
public:
	pta1066():root(nullptr)
	{
		cin >> N;
	}
	void Solve()
	{
		int value = 0;
		for (size_t i = 0; i < N; ++i)
		{
			cin >> value;
			root = insert(root, value);
		}
	}
	void Print()
	{
		cout << root->value << endl;
	}
	~pta1066()
	{}
};
int main()
{
	pta1066* question = (pta1066*)malloc(sizeof(pta1066));
	new(question) pta1066();
	question->Solve();
	question->Print();
}
