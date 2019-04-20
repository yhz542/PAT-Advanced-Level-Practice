#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
using namespace std;
struct student
{
	int C;
	int M;
	int E;
	int A;
	student(istream &in) 
	{
		in >> C >> M >> E;
		A =(int)( (C + M + E) / 3.+0.5);
	}
};
void Process(student *, int);
void BestRank(const student *const);
int main()
{
	int N, M;
	cin >> N >> M;
	allocator<student> alloc;
	unordered_map<string, student *> studentInfo;
	student *const dataStudent = alloc.allocate(N);
	string StudentID;
	for (int i = 0; i < N; ++i)
	{
		cin >> StudentID;
		alloc.construct(dataStudent + i, cin);
		studentInfo.insert(make_pair(StudentID, dataStudent + i));
	}
	Process(dataStudent, N);
	for (int i = 0; i < M; ++i)
	{
		cin >> StudentID;
		if (studentInfo.find(StudentID) != studentInfo.end())
		{
			BestRank(studentInfo[StudentID]);
		}
		else
			printf("N/A\n");
	}
}
void Process(student *const dataStudent, int N )
{
	vector<int> index;
	index.reserve(N);
	for (int i = 0; i < N; ++i)
		index.push_back(i);
	int rank = 0;
	int scoreFormer = 101;
	int scoreCurrent = 0;	
	sort(index.begin(), index.end(), [&dataStudent](int i, int j) { return dataStudent[i].A > dataStudent[j].A; });
	for (int i = 0; i < N; ++i)
	{
		scoreCurrent = dataStudent[index[i]].A;
		if (scoreCurrent < scoreFormer)
			dataStudent[index[i]].A = i + 1;
		else
			dataStudent[index[i]].A = dataStudent[index[i - 1]].A;
		scoreFormer = scoreCurrent;
	}
	rank = 0;
	scoreFormer = 101;
	scoreCurrent = 0;
	sort(index.begin(), index.end(), [&dataStudent](int i, int j) { return dataStudent[i].C > dataStudent[j].C; });
	for (int i = 0; i < N; ++i)
	{
		scoreCurrent = dataStudent[index[i]].C;
		if (scoreCurrent < scoreFormer)
			dataStudent[index[i]].C = i + 1;
		else
			dataStudent[index[i]].C = dataStudent[index[i - 1]].C;
		scoreFormer = scoreCurrent;
	}
	rank = 0;
	scoreFormer = 101;
	scoreCurrent = 0;
	sort(index.begin(), index.end(), [&dataStudent](int i, int j) { return dataStudent[i].M > dataStudent[j].M; });
	for (int i = 0; i < N; ++i)
	{
		scoreCurrent = dataStudent[index[i]].M;
		if (scoreCurrent < scoreFormer)
			dataStudent[index[i]].M = i + 1;
		else
			dataStudent[index[i]].M = dataStudent[index[i - 1]].M;
		scoreFormer = scoreCurrent;
	}
	rank = 0;
	scoreFormer = 101;
	scoreCurrent = 0;
	sort(index.begin(), index.end(), [&dataStudent](int i, int j) { return dataStudent[i].E > dataStudent[j].E; });
	for (int i = 0; i < N; ++i)
	{
		scoreCurrent = dataStudent[index[i]].E;
		if (scoreCurrent < scoreFormer)		
			dataStudent[index[i]].E = i + 1;
		else
			dataStudent[index[i]].E = dataStudent[index[i - 1]].E;
		scoreFormer = scoreCurrent;
	}
}
void BestRank(const student *const info)
{
	int rank = info->E;
	char course = 'E';
	if (rank >= info->M)
	{
		rank = info->M;
		course = 'M';
	}
	if (rank >= info->C)
	{
		rank = info->C;
		course = 'C';
	}
	if (rank >= info->A)
	{
		rank = info->A;
		course = 'A';
	}
	printf("%d %c\n", rank, course);
}
