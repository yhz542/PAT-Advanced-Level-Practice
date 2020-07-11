#include<cstdlib>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
using uint = unsigned int;
using namespace std;
#define GetVirtueGrade(p) (p.second.first)
#define GetTalentGrade(p) (p.second.second)
#define GetID(p) (p.first)
typedef enum
{
	Sage,
	NobleMan,
	FoolMan,
	SmallMan,
	TrashMan
}manType;
bool cmp(const pair<int, pair<char, char>>& a, const pair<int, pair<char, char>>& b)
{
	unsigned char firstGrade = GetVirtueGrade(a) + GetTalentGrade(a);
	unsigned char secondGrade = GetVirtueGrade(b) + GetTalentGrade(b);
	if (firstGrade != secondGrade)
		return firstGrade > secondGrade;
	else if (GetVirtueGrade(a) != GetVirtueGrade(b))
		return GetVirtueGrade(a) > GetVirtueGrade(b);
	else
		return GetID(a) < GetID(b);
}
class pta1062
{
	int N;
	char L;
	char H;
	int finalN;
	vector < pair<int, pair<char, char>>> people[4];
	manType judgeManType(char virtue , char talent)
	{
		manType type ;
		if (virtue < L || talent < L)
			type = TrashMan;
		else if (virtue >= H&& talent >= H)
			type = Sage;
		else if (virtue >= H&& talent >= L)
			type = NobleMan;
		else if (virtue < H && talent < H &&virtue>=talent)
			type = FoolMan;
		else
			type = SmallMan;
		return type;
	}
public:
	pta1062():finalN(0)
	{
		scanf("%d %d %d", &N, &L, &H);
		int ID_Number;
		char Virtue_Grade, Talent_Grade;
		manType type;
		for (size_t i = 0; i < N; ++i)
		{
			scanf("%d %hhd %hhd", &ID_Number, &Virtue_Grade, &Talent_Grade);
			type = judgeManType(Virtue_Grade, Talent_Grade);
			switch (type)
			{
			case Sage:
				people[Sage].push_back(make_pair(ID_Number, make_pair(Virtue_Grade, Talent_Grade)));
				break;
			case NobleMan:
				people[NobleMan].push_back(make_pair(ID_Number, make_pair(Virtue_Grade, Talent_Grade)));
				break;
			case FoolMan:
				people[FoolMan].push_back(make_pair(ID_Number, make_pair(Virtue_Grade, Talent_Grade)));
				break;
			case SmallMan:
				people[SmallMan].push_back(make_pair(ID_Number, make_pair(Virtue_Grade, Talent_Grade)));
				break;
			default:
				continue;
			}
		}
	}
	void Solve()
	{
		for (auto &elem : people)
		{
			sort(elem.begin(), elem.end(),cmp);
			finalN += elem.size();
		}
	}
	void Print()
	{
		printf("%d\n", finalN);
		for (auto elem : people)
		{
			for (auto man : elem)
				printf("%08d %d %d\n", man.first, GetVirtueGrade(man), GetTalentGrade(man));
		}
	}
};
int main()
{
	pta1062* question = (pta1062*)malloc(sizeof(pta1062));
	new (question)pta1062();
	question->Solve();
	question->Print();
}
