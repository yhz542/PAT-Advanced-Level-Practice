#include<cstdlib>
#include <cctype>
#include<string>
#include<cstdio>
#include<iostream>
using uint = unsigned int;
using namespace std;
typedef enum :short
{
	Non = 0,
	Mon = 'A',
	Tue ,
	Wed ,
	Thu ,
	Fri ,
	Sat ,
	Sun 
}day;
class pta1061
{
	string first;
	string second;
	string third;
	string forth;
	day weekday;
	uint hour;
	uint minute;
public:
	pta1061():weekday(Non),hour(0),minute(0)
	{
		cin >> first >> second >> third >> forth;
	}
	void Solve()
	{
		bool findCapital = false;
		size_t i = 0;
		while(1)
		{
			if ( first[i] == second[i] && (first[i]>='A' &&first[i]<='G'))
				break;
			++i;
		}
		weekday = static_cast<day>(first[i++]);
		while (1)
		{
			if (first[i] == second[i] && 
				(isdigit(first[i]) || ( first[i]>='A' && first[i]<='N') ) )
				break;
			++i;
		}
		if (isdigit(first[i]))
			hour = first[i] - '0';
		else
		{
			hour = first[i] - 'A' + 10;
		}
		i = 0;
		uint length = third.size() < forth.size() ? third.size() : forth.size();
		while (i < length)
		{
			if (third[i] == forth[i] && isalpha(third[i]))
			{
				minute = i;
				break;
			}
			++i;
		}
	}
	void Print()
	{
		switch (weekday)
		{
		case Mon:
			cout << "MON";
			break;
		case Tue:
			cout << "TUE";
			break;
		case Wed:
			cout << "WED";
			break;
		case Thu:
			cout << "THU";
			break;
		case Fri:
			cout << "FRI";
			break;
		case Sat:
			cout << "SAT";
			break;
		case Sun:
			cout << "SUN";
			break;
		default:
			break;
		}
		printf(" %02d:%02d", hour, minute);
	}
};
int main()
{
	pta1061* question = (pta1061*)malloc(sizeof(pta1061));
	new (question)pta1061();
	question->Solve();
	question->Print();
}
