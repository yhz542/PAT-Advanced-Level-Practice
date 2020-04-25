#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstdio>
using namespace std;
struct record
{
	unsigned ID;
	string name;
	unsigned grade;
};
struct cmp
{
private:
	vector<record>& data;
	unsigned char sortType;
public:
	cmp(vector<record>& tem,int type) :data(tem),sortType(type)
	{}
	bool operator()(unsigned a, unsigned b)
	{
		switch (sortType)
		{
		case 1:
			return data[a].ID<data[b].ID;
			break;
		case 2:
			if (data[a].name != data[b].name)
				return data[a].name < data[b].name;
			else
				return data[a].ID < data[b].ID;
			break;
		case 3:
			if (data[a].grade != data[b].grade)
				return data[a].grade < data[b].grade;
			else
				return data[a].ID < data[b].ID;
			break;
		default:
			break;
		}
		return false;
	}
};
class pta1028
{
	int N, C;
	vector<record> data;
	vector<unsigned> index;
public:
	pta1028(istream& in)
	{
		cin >> N>>C;
		data.resize(N);
		for (int i = 0; i < N; ++i)
		{
			cin >> data[i].ID >> data[i].name >> data[i].grade;
		}
	}
	void Solve()
	{
		index.reserve(N);
		for (size_t i = 0; i < N; ++i)
			index.push_back(i);
		stable_sort(index.begin(), index.end(), cmp(data, C));
	}
	void Print()
	{
		for (auto elem : index)
		{
			printf("%06d %s %d\n" ,data[elem].ID , data[elem].name.c_str() , data[elem].grade );
		}
	}
};
int main()
{
	pta1028 question(cin);
	question.Solve();
	question.Print();
}
