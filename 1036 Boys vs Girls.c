#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
typedef unsigned int uint;
typedef struct info studentInfo;
struct info
{
    char name[11];
    char ID[11];
    int grade;
};
int main(void)
{
    uint N;
    scanf("%u", &N);
    studentInfo man;
    man.grade = 101;
    studentInfo woman;
    woman.grade = -1;
    char name[11], ID[11],gender;
    int grade;
    for (uint i = 0; i < N; ++i)
    {
        scanf("%s %c %s %d", name, &gender, ID, &grade);
        if ('M' == gender)
        {
            if (grade < man.grade)
            {
                strcpy(man.name, name);
                strcpy(man.ID, ID);
                man.grade = grade;
            }
        }
        else
        {
            if (grade > woman.grade)
            {
                strcpy(woman.name, name);
                strcpy(woman.ID, ID);
                woman.grade = grade;
            }
        }
    }
    uint flag = 0;
    if (-1 == woman.grade)
        printf("Absent\n");
    else
    {
        printf("%s %s\n", woman.name, woman.ID);
        flag |= 1;
    }
    if (101 == man.grade)
        printf("Absent\n");
    else
    {
        printf("%s %s\n", man.name, man.ID);
        flag |= 2;
    }
    if (3 == flag)
        printf("%d\n", woman.grade - man.grade);
    else
        printf("NA\n");
    return 0;
}
