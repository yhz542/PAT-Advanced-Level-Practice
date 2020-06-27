#include<stack>
#include<cstdlib>
#include <cstdio>
#include<set>
using uint = unsigned int;
using namespace std;
class pta1058
{
	struct money
	{
		uint Galleon;
		uint Sickle;
		uint Knut;
		money() :Galleon(0), Sickle(0), Knut(0) {}
		money(uint g,uint s,uint k):Galleon(g),Sickle(s),Knut(k){}
	};
	money A, B,result;
public:
	pta1058()
	{
		uint galleon, sickle, knut;
		scanf("%u.%u.%u", &galleon, &sickle, &knut);
		A = money(galleon, sickle, knut);
		scanf("%u.%u.%u", &galleon, &sickle, &knut);
		B = money(galleon, sickle, knut);                         
	}
	void Solve()
	{
		result.Knut = A.Knut + B.Knut;
		if (result.Knut >= 29)
		{
			result.Knut -= 29;
			++result.Sickle;
		}
		result.Sickle += (A.Sickle + B.Sickle);
		if (result.Sickle >= 17)
		{
			result.Sickle -= 17;
			++result.Galleon;
		}
		result.Galleon += (A.Galleon + B.Galleon);
	}
	void Print()
	{
		printf("%u.%u.%u\n", result.Galleon, result.Sickle, result.Knut);
	}
};
int main()
{
	pta1058* question = (pta1058*)malloc(sizeof(pta1058));
	new (question)pta1058;
	question->Solve();
	question->Print();
}
