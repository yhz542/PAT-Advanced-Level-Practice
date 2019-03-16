#include<cstdio>//把别人的代码变量名改了一下，强化可读性 地址 https://blog.csdn.net/qq278672818/article/details/55669457
#define MAXN 100000
int main()
{
	int  N , M , C1 , C2 ;
	scanf("%d%d%d%d", &N , &M , &C1 , &C2 ) ;
	int numOfRescueTeam[ N ];
	int distance[N][N];
	for(int i=0 ; i < N ; ++i)
	{
		for(int j = 0 ; j < N ; j++ )
		{
			distance[ i ][ j ] = MAXN ;
			if( i == j )
				distance[ i ][ j ] = 0 ;
		}
	}
	for(int i = 0 ; i < N ; ++i )
		scanf( "%d", &numOfRescueTeam[i] ) ;
	for(int i=0 , city1 , city2 , length ; i < M ; ++i )
	{
		scanf("%d%d%d", &city1 , &city2 , &length ) ;
		distance[ city1 ][ city2 ] = length ;
		distance[ city2 ][ city1 ] = length ;
	}
	bool visited[N];
	int numOfShortestRoad[N];
        int Team[N];
	int shortest[N];
	for(int i=0;i<N;++i)
	{
		visited[i]=false;
		shortest[i]=distance[ C1 ][ i ] ;
		if(i==C1)
		{
			numOfShortestRoad[C1]=1;
			Team[C1]=numOfRescueTeam[C1];
		}
		else
		{
			numOfShortestRoad[i]=0;
			Team[i]=0;
		}
	}
	int city=-1;
	int cityNow;
	while(city!=C2)
	{
		int length = MAXN ;
		for( int i=0;i<N;++i)
		{
			if(visited[i]==true)
				continue;
			if(shortest[i]<length)
			{
				cityNow=i;
				length=shortest[i];
			}
		}
		visited[cityNow]=true;
		city=cityNow;
		for(int i=0;i < N ; ++i )
		{
			if(visited[i]==true)
				continue;
			if(shortest[i]>shortest[cityNow]+distance[cityNow][i])
			{
				shortest[i]=shortest[cityNow]+distance[cityNow][i];
				Team[i]=numOfRescueTeam[i]+Team[cityNow];
				numOfShortestRoad[i]=numOfShortestRoad[cityNow];
			}else if(shortest[i]==shortest[cityNow]+distance[cityNow][i])
			{
				numOfShortestRoad[i]=numOfShortestRoad[i]+numOfShortestRoad[cityNow];
				if(Team[i]<Team[cityNow]+numOfRescueTeam[i])
					Team[i]=Team[cityNow]+numOfRescueTeam[i];
			}
		}
	}
	printf("%d %d",numOfShortestRoad[C2],Team[C2]);
	return 0;
}
