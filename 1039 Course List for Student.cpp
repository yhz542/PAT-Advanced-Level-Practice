#include<iostream>
#include<forward_list>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<set>
typedef unsigned int uint;
using namespace std;
struct studentData
{
	set<int> course;
	int numOfCourse = 0;
	studentData() = default;
};
class pta1039
{
	uint N, K;
	unordered_map<int, studentData> info;
	int Convert(char name[])
	{
		int num = 0;
		for (size_t i = 0; i < 3; ++i)
		{
			num *= 26;
			num += name[i] - 'A';
		}
		num *= 10;
		num += (name[3]-'0');
		return num;
	}
public:
	pta1039(istream& in)
	{
		scanf("%u %u", &N, &K);
		int course;
		uint numOfStudents;
		char student[5];
		uint num = 0;
		for (uint i = 0; i < K; ++i)
		{
			scanf("%d %u", &course, &numOfStudents);
			for (uint j = 0; j < numOfStudents; ++j)
			{
				scanf("%s", student);
				num = Convert(student);
				if (info.find(num) == info.end())
					info.insert(make_pair(num, studentData()));
				info[num].course.insert(course);
				info[num].numOfCourse++;
			}
		}

	}
	void Solve()
	{
	}
	void Print()
	{
		char student[5];
		uint index = 0;
		for (size_t i = 0; i < N; ++i)
		{
			scanf("%s", student);
			printf("%s ", student);
			index = Convert(student);
			if (info.find(index) == info.end())
			{
				printf("0\n");
				continue;
			}
			else
				printf("%d", info[index].numOfCourse);
			for (auto elem : info[index].course)
			{
				printf(" %d", elem);
			}
			printf("\n");
		}
	}
};
int main()
{
	pta1039 question(cin);
	question.Solve();
	question.Print();
}
