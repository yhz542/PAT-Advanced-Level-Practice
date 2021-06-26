#include<vector>//卡在段错误好久，才发现是分数是int类型，而不是一定小于100.
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define LASTSTUDENT(i) (studentInfos[lastStudent[i]])
struct compare;
class pat1080
{
private:
	friend struct compare;
	typedef struct info
	{
		int GE;
		int GI;
		vector<int> choices;
	}info;
	int N, M, K;
	vector<int> quotas;
	vector<info> studentInfos;
	vector<int> index;
	vector<vector<int>> result;
	vector<int> lastStudent;
public:
	pat1080(void)
	{
		scanf("%d %d %d", &N, &M, &K);
		studentInfos.resize(N);
		index.reserve(N);
		quotas.reserve(M);
		result.resize(M);
		lastStudent.resize(M,-1);
		int quota = 0;
		for (int i = 0; i < M; ++i)
		{
			scanf("%d", &quota);
			quotas.push_back(quota);
		}
		int choice;
		for (int i = 0; i < N; ++i)
		{
			index.push_back(i);
			studentInfos[i].choices.reserve(K);
			scanf("%d %d", &studentInfos[i].GE, &studentInfos[i].GI);
			for (int k = 0; k < K; ++k)
			{
				scanf("%d", &choice);
				studentInfos[i].choices.push_back(choice);
			}
		}
	}
	void solve();
	void display()
	{
		bool first;
		for (auto& school : result)
		{
			sort(school.begin(), school.end());//增序显示
			first = true;
			for (auto student : school)
			{
				if (first)
				{
					first = false;
					printf("%d", student);
				}
				else
					printf(" %d", student);
			}
			putchar('\n');
		}
	}
	~pat1080()
	{}
};
struct compare
{
	vector<pat1080::info>& cpy;
	compare(vector<pat1080::info>& src) :cpy(src) {}
	bool operator()(int a, int b)
	{
		if (cpy[b].GI + cpy[b].GE != cpy[a].GI + cpy[a].GE)
		{
			return cpy[a].GI + cpy[a].GE > cpy[b].GI + cpy[b].GE;
		}
		else
		{
			return cpy[a].GE > cpy[b].GE;
		}
	}
};
int main()
{
	pat1080* ptr = (pat1080*)malloc(sizeof(pat1080));
	new(ptr) pat1080();
	ptr->solve();
	ptr->display();
	ptr->~pat1080();
	free(ptr);
	return 0;
}
void pat1080::solve()
{
	bool flag = false;
	sort(index.begin(), index.end(), compare(studentInfos));
	for (auto i : index)//由于使用桶排序 所以这里处理比较方便
	{
		info &curStudent = studentInfos[i];
		for (auto j : curStudent.choices)
		{
			if (result[j].size() < quotas[j])
			{
				result[j].push_back(i);
				lastStudent[j] = i;//这里记录该学校最后一个录取的学生
				break;
			}
			else if (lastStudent[j]!=-1&&curStudent.GE == LASTSTUDENT(j).GE&& curStudent.GI == LASTSTUDENT(j).GI)//通过和最后一个学生比较成绩来计算名次是否相同
			{
				result[j].push_back(i);
				lastStudent[j] = i;
				break;
			}
		}
	}
}
/**
比较有用的测试用例 貌似不会影响到实际AC的结果
5 2 2
1 1
10 10 0 1
10 10 0 1
10 10 1 0
10 10 1 0
10 10 0 1

正确输出为：
0 1 4
2 3
**/
