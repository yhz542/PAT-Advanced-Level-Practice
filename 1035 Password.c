#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef unsigned int uint;
typedef struct account Account;
struct account
{
    char userName[11];
    char passWord[11];
    bool needModify;
};
int main(void)
{
    uint N;
    scanf("%u", &N);
    Account* data = (Account*)malloc(sizeof(struct account) * N);
    for (uint i = 0; i < N; ++i)
    {
        scanf("%s %s", data[i].userName, data[i].passWord);
        data[i].needModify = false;
    }
    uint cnt = 0;
    for (uint i = 0; i < N; ++i)
    {
        char* curPtr = data[i].passWord;
        while ((*curPtr) != '\0')
        {
            switch (*curPtr)
            {
            case '1':
                *curPtr = '@';
                data[i].needModify = true;
                break;
            case 'l':
                *curPtr = 'L';
                data[i].needModify = true;
                break;
            case 'O':
                *curPtr = 'o';
                data[i].needModify = true;
                break;
            case '0':
                *curPtr = '%';
                data[i].needModify = true;
                break;
            default:
                break;
            }
            curPtr++;
        }
        if (data[i].needModify)
            cnt++;
    }
    if (cnt)
    {
        printf("%d\n", cnt);
        for (uint i = 0; i < N; ++i)
        {
            if (data[i].needModify)
            {
                printf("%s %s\n", data[i].userName, data[i].passWord);
            }
        }
    }
    else
    {
        const char* isOrAre;
        const char* account;
        if (1 == N)
        {
            isOrAre = "is";
            account = "account";
        }
        else
        {
            isOrAre = "are";
            account = "accounts";
        }
        printf("There %s %d %s and no account is modified\n", isOrAre, N, account);
    }
    return 0;
}
