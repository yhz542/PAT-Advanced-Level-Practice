#include <cstdio>
using namespace std ;
void Print( int , int );
int main()
{
        int a , b;
        scanf( "%d%d", &a , &b ) ;
        int sum = a + b ;
        if( sum<0 )//负数当正数处理 只用单独输出一个负号
        {
                printf("-");
                Print(-sum,0);
        }
        else if( sum>0 )
                Print(sum,0);
        else//特殊情况 和为0
                printf("0");
}
void Print( int sum , int cnt)//递归解决问题 cnt代表位数
{
        int output = sum%10;
        int divide = sum/10;
        ++cnt;
        if( !sum )
                return ;
        else
                Print(divide,cnt);
        printf("%d",output);
        if((cnt-1)%3==0&&cnt!=1) //cnt-1 恰好为3的倍数时输出一个逗号，1位数时特殊处理 或者 ！cnt%3 && divide 即前面还有数时输出逗号
                printf(",");
}
