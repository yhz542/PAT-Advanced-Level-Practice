#include <cstdio>//注意的就一点 ，相加之后系数为0则不输出。
#include <vector>
#include <set>
using namespace std;
int main()
{
        int K1;
        scanf("%d",&K1);
        vector< float > ploy( 1001 ) ;
        set<int> expSet ;
        int exp ;
        float coef ;
        for( int i = 0 ; i < K1 ;++i )
        {
                scanf("%d%f",&exp,&coef);
                ploy[ exp ] += coef ;
                expSet.insert(exp);
                if(!ploy[ exp ])//如果系数变为0 则从集合中删除
                        expSet.erase(exp);
        }
        int K2 ;
        scanf("%d",&K2);
        for( int i = 0 ; i < K2 ;++i )
        {
                scanf("%d%f",&exp,&coef);
                ploy[ exp ] += coef ;
                expSet.insert(exp);
                if(!ploy[ exp ])
                        expSet.erase(exp);
        }
        printf("%d",expSet.size());
        for( int i = 1000 ; i >=0 ; --i)
        {
                if( ploy[i] )
                        printf(" %d %.1f",i,ploy[i]);
        }
}
