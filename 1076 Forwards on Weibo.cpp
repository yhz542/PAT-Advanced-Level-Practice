#include<vector>//题比较简单 广度优先搜索 需要注意的每层人数的计数累加 深度优先也可以，但是需要每个成员需要作为结构体额外带一个参数记录层数，
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<queue>
using namespace std;
class pat1076
{
private:
	short N,L;
	short num;
	vector<vector<int>> map;

	void BFS(short user)
	{
		vector<bool> visited(N,false);
		queue<int> q_user;
		--user;
		short curLayerNum = 1,nexLayerNum = 0 ;//当前层的人数，下一层的人数
		short layer = 0;
		q_user.push(user);
		visited[user] = true;
		short temUser;
		while (!q_user.empty() && layer < L )
		{
			user = q_user.front();
			q_user.pop();
			--curLayerNum;
			for (int i = 0; i < map[user].size(); ++i)
			{
				temUser = map[user][i];
				if (!visited[temUser])
				{
					q_user.push(temUser);
					visited[temUser] = true;
					++nexLayerNum;
					++num;
				}
			}	
			if (!curLayerNum)//当前层的转发人数用完
			{
				curLayerNum = nexLayerNum;//开始使用下一层的转发人数
				nexLayerNum = 0;
				++layer;
			}
		}
	}
public:
	pat1076(void)
	{
		scanf("%hd %hd", &N,&L);
		map.resize(N);
		short M,user;
		for (int i = 0; i < N; ++i)
		{
			scanf("%hd",&M);
			for (int j = 0; j < M; ++j)
			{
				scanf("%hd",&user);
				map[user - 1].push_back(i);
			}
		}
	}
	void slove()
	{
		short K, userID;
		scanf("%hd", &K);
		for (int i = 0; i < K; ++i)
		{
			scanf("%hd", &userID);
			num = 0;
			BFS(userID);
			printf("%d\n", num);
		}
	}
	~pat1076()
	{}
};
int main()
{
	pat1076* ptr = (pat1076 *)malloc(sizeof(pat1076));
	new(ptr) pat1076();
	ptr->slove();
	ptr->~pat1076();
	free(ptr);
	return 0;
}
