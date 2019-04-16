#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int N;
	cin >> N;
	vector<int> list(N);
	for (int &elem : list)
	{
		cin >> elem;
	}
	int before=0,timeCost=0;
	for (auto now : list)
	{
		if (now < before)
		{
			timeCost += (before - now) * 4 + 5;
		}
		else if (now > before)
		{
			timeCost += (now - before) * 6 + 5;
		}
		else
			timeCost += 5;
		before = now;
	}
	cout << timeCost << endl;
}
