#include <iostream>//虽然是以cpp结尾的c++程序，但实际上值在读取整数的时候用了一个cin而已。整体来说用的都是C语言的知识。
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;
bool Less(int , int , int , int ,int , int );
int main()
{
        int M;
        cin >> M;
        int HHul=24,MMul=60,SSul=60,HHl=0,MMl=0,SSl=0,HHin,MMin,SSin,HHout,MMout,SSout;
        char ID[16],ID_unlock[16],ID_lock[16];
        for( int i = 0 ; i < M ; ++i )
        {
                scanf("%s",ID);
                scanf("%d:%d:%d %d:%d:%d",&HHin,&MMin,&SSin,&HHout,&MMout,&SSout);
                if(Less(HHin,MMin,SSin,HHul,MMul,SSul))
                {
                        strcpy(ID_unlock,ID);
                        HHul=HHin;
                        MMul=MMin;
                        SSul=SSin;
                }
                if(!Less(HHout,MMout,SSout,HHl,MMl,SSl))
                {
                        strcpy(ID_lock,ID);
                        HHl=HHout;
                        MMl=MMout;
                        SSl=SSout;
                }
        }
        printf("%s %s\n",ID_unlock,ID_lock);
}
inline bool Less(int HH1, int MM1, int SS1, int HH2,int MM2, int SS2)
{
        if(HH1 != HH2)
                return HH1 < HH2 ;
        else if( MM1 != MM2 )
                return MM1 < MM2 ;
        else
                return SS1 < SS2 ;
}
