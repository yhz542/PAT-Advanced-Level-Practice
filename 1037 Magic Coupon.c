#include<stdio.h>//解体思路，将每个数组按照正负拆成两个数组，也就是说两个数组会被拆成4个数组，然后负和负从小到大相乘
#include<stdlib.h>//正和正从大到小相乘。
#include<stdbool.h>
#include<string.h>
typedef unsigned int uint;
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int main(void)
{
    uint Nc,ncp=0,ncn=0;
    scanf("%u", &Nc);
    int *coupons = (int*)malloc(sizeof(int) * Nc);
    for (size_t i = 0; i < Nc; ++i)
    {
        scanf("%d", coupons + i);
        if (coupons[i] < 0)//计算负数的个数
            ++ncn;
        else
            ++ncp;//计算正数及0的个数
    }
    qsort(coupons, Nc, sizeof(int), cmp);
    uint Np,npp=0,npn=0;
    scanf("%u", &Np);
    int* products = (int*)malloc(sizeof(int) * Np);//从小到大排序
    for (size_t i = 0; i < Np; ++i)
    {
        scanf("%d", products + i);
        if (products[i] < 0)
            ++npn;
        else
            ++npp;
    }
    qsort(products, Np, sizeof(int), cmp);//从小到大排序
    int *ptrNc = coupons;
    int* ptrNp = products;
    uint n = (ncn < npn ? ncn : npn);//取两者较小的值 组成负数数组的长度
    uint p = (ncp < npp ? ncp : npp);
    uint moneyBack = 0;
    while (n--)
        moneyBack += *(ptrNc++) * *(ptrNp++);
    ptrNc = coupons + Nc - 1;
    ptrNp = products + Np - 1;
    while(p--)
        moneyBack += *(ptrNc--) * *(ptrNp--);
    printf("%d", moneyBack);
    return 0;
}
