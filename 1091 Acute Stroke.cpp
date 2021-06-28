#include <cstdio>//没什么好说的 广度优先或者深度优先搜索
#include <vector>
#include <cstdlib>
#include <set>
#include<cstring>
using namespace std;
#define INFINITE 65535
class pta1091
{
	struct core
	{
		short L;
		int M, N;
		core(short hig,int wid,int len):L(hig),M(wid),N(len){}
	};
	short L;
	int M,N,T;
	vector<vector<vector<bool>>> slice;
	vector<core> cores;
	int sum;
	void vistCoreNeghibour(core& target)
	{
		short h = target.L;
		int w = target.M;
		int l = target.N;
		if (h > 0 && slice[h - 1][w][l])
		{
			cores.push_back(core(h - 1, w, l));
			slice[h - 1][w][l] = false;
		}
		if (h + 1 < L && slice[h + 1][w][l])
		{
			cores.push_back(core(h + 1, w, l));
			slice[h + 1][w][l] = false;
		}
		if (w > 0 && slice[h][w - 1][l])
		{
			cores.push_back(core(h, w - 1, l));
			slice[h][w - 1][l] = false;
		}
		if (w + 1 < M && slice[h][w + 1][l])
		{
			cores.push_back(core(h, w + 1, l));
			slice[h][w + 1][l] = false;
		}
		if (l > 0 && slice[h][w][l - 1])
		{
			cores.push_back(core(h, w, l - 1));
			slice[h][w][l - 1] = false;
		}
		if (l + 1 < N && slice[h][w][l + 1])
		{
			cores.push_back(core(h, w, l + 1));
			slice[h][w][l + 1] = false;
		}
	}
	void BFS(core start)
	{
		int cnt = 0;
		cores.push_back(start);
		slice[start.L][start.M][start.N] = false;//标记为已访问
		while (!cores.empty())
		{
			core curCore = cores.back();
			//printf("visited core = %d,%d,%d\n", curCore.L, curCore.M, curCore.N);
			cores.pop_back();
			++cnt;
			vistCoreNeghibour(curCore);
		}
		//printf("cnt = %d T= %d\n", cnt,T);
		if(cnt >= T)
			sum += cnt;
	}
public:
	pta1091():sum(0)
	{
		scanf("%d %d %hd %d", &M, &N, &L, &T);
		slice.resize(L, vector<vector<bool>>(M, vector<bool>(N)));
		short zeroOrOne = 0;
		for (short i = 0; i < L; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				for (int k = 0; k < N; ++k)
				{
					scanf("%hd", &zeroOrOne);
					slice[i][j][k] = (bool)zeroOrOne;
				}
			}
		}
	}
	void solve()
	{
		for (short high = 0; high < L; ++high)
		{
			for (int width = 0; width < M; ++width)
			{
				for (int length = 0; length < N; ++length)
				{
					if (slice[high][width][length])
						BFS(core((short)high, width, length));
				}
			}
		}
	}
	void display()
	{
		printf("%d", sum);
	}
	~pta1091()
	{
		
	}
};
int main()
{
	pta1091* question = (pta1091*)malloc(sizeof(pta1091));
	new(question) pta1091();
	question->solve();
	question->display();
	question->~pta1091();
	free(question);
}
