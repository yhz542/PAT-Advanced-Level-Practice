#include <cstdio>//更好的map解决方案
#include <map>
using namespace std ;
int main()
{
        map<int,float> ploy;
        int K1 ;
        scanf("%d",&K1) ;
        int exp;
        float coef;
        for( int i = 0 ; i < K1 ; ++i )
        {
                scanf("%d%f",&exp,&coef);
                ploy[exp]+=coef;
                if(!ploy[exp])
                        ploy.erase(exp);
        }
        int K2 ;
        scanf("%d",&K2);
        for( int i = 0 ; i <K2 ; ++i )
        {
                scanf("%d%f",&exp,&coef);
                ploy[exp]+=coef;
                if(!ploy[exp])
                        ploy.erase(exp);
        }
        printf("%d",ploy.size());
        for(auto beg = ploy.crbegin() ; beg!=ploy.crend() ; ++beg)
        {
                printf(" %d %.1f",beg->first,beg->second);
        }
}
