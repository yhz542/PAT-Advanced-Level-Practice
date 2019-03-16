#include <cstdio>
#include<vector>
#include<map>
#define Max 655350
using namespace std;
void GetTeamInfo(vector<int> &);
void GetMapInfo(vector<map<int, int>>&,int);
void ShortestDistance(vector < map<int, int> >&, vector<int> &,int , int);
void DeleteCity(vector<int> &visited, int yourCity);
int FindShortest(vector<int> &, vector<int> &);
int main()
{
	int N, M, yourCity, targetCity;
	scanf("%d%d%d%d", &N, &M, &yourCity, &targetCity);
	vector<int> teamInfo(N);
	GetTeamInfo(teamInfo);//获取城市的救援队数据
	vector<map<int, int>> mapInfo(N);//map的key为城市号码,value为距离
	GetMapInfo(mapInfo, M);//获取城市地图数据
	ShortestDistance(mapInfo, teamInfo, yourCity, targetCity);
}
inline void GetTeamInfo(vector<int> &teamInfo)
{
	for (size_t i = 0; i < teamInfo.size(); ++i)
	{
		scanf("%d", &teamInfo[i]);
	}
}
inline void GetMapInfo(vector<map<int, int>>&mapInfo,int M)
{
	int c1, c2, length;
	for (int i = 0; i < M ; ++i)
	{
		scanf("%d%d%d", &c1, &c2, &length);
		mapInfo[c1][c2] = length;
		mapInfo[c2][c1] = length;
	}
}
inline void DeleteCity(vector<int> &city, int index)
{
	city[index] = city[city.size() - 1];
	city.pop_back();
}
inline int FindShortest(vector<int> &citys, vector<int> &shortest)
{
	int shortestDis = Max;
	int shortestCity=-1;
	int Index;
	for (int i = 0; i < citys.size(); ++i)
	{
		if (shortest[citys[i]] < shortestDis )
		{
			shortestDis = shortest[citys[i]];
			shortestCity = citys[i];
			Index = i;
		}
	}
	DeleteCity(citys, Index);
	return shortestCity;
}
void ShortestDistance(vector < map<int, int> >&mapInfo, vector<int> &teamInfo, int yourCity, int targetCity)
{
	vector<int> numShortestDis(mapInfo.size(), 0);
	vector<int> maxTeam(mapInfo.size(), 0);
	vector<int> shortest(mapInfo.size(),Max);
	vector<int> citys(mapInfo.size());
	for (int i = 0; i < citys.size(); ++i)
		citys[i] = i;
	shortest[yourCity] = 0;
	maxTeam[yourCity] = teamInfo[yourCity];
	numShortestDis[yourCity] = 1;
	int cityNow = FindShortest(citys, shortest);
	while (cityNow!=targetCity)
	{
		for (auto beg = mapInfo[cityNow].cbegin(); beg != mapInfo[cityNow].cend(); ++beg)
		{
			if (shortest[cityNow] + beg->second < shortest[beg->first])
			{
				shortest[beg->first] = shortest[cityNow] + beg->second;
				maxTeam[beg->first] = maxTeam[cityNow] + teamInfo[beg->first];
				numShortestDis[beg->first] = numShortestDis[cityNow];
			}
			else if (shortest[cityNow] + beg->second == shortest[beg->first] )
			{
				numShortestDis[beg->first]+=numShortestDis[cityNow];
				if (maxTeam[beg->first] < maxTeam[cityNow] + teamInfo[beg->first])
				{
					maxTeam[beg->first] = maxTeam[cityNow] + teamInfo[beg->first];
				}
			}
		}
		cityNow = FindShortest(citys, shortest);
	}
	printf("%d %d",numShortestDis[targetCity], maxTeam[targetCity]);
}
