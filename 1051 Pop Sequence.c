#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int Capacity;
    int* Data;
    int top;
};
typedef struct Node* Stack;
int** GetInput(int, int);
Stack CreateStack(int);
void MakeEmpty(Stack);
void Push(int, Stack);
int Pop(Stack);
void Check(int[], int, Stack);
int main(void)
{
    int Capacity, Length, NumCheck;
    Stack New;
    int** Store;
    scanf("%d %d %d", &Capacity, &Length, &NumCheck);
    New = CreateStack(Capacity);
    Store = GetInput(Length, NumCheck);
    for (int i = 0; i < NumCheck; i++)
    {
        Check(Store[i], Length, New);
        MakeEmpty(New);
    }
    return 0;
}
int** GetInput(int Length, int NumCheck)
{
    int** Store;
    Store = (int**)malloc(sizeof(int*) * NumCheck);
    for (int i = 0; i < NumCheck; i++)
    {
        Store[i] = (int*)malloc(sizeof(int) * Length);
    }
    for (int i = 0; i < NumCheck; i++)
    {
        for (int j = 0; j < Length; j++)
            scanf("%d", &Store[i][j]);
    }
    return Store;
}
Stack CreateStack(int Capacity)
{
    Stack New;
    New = (Stack)malloc(sizeof(struct Node));
    New->Capacity = Capacity;
    New->top = -1;
    New->Data = (int*)malloc(sizeof(int) * Capacity);
    return New;
}
void MakeEmpty(Stack s)
{
    s->top = -1;
    return;
}
void Push(int Num, Stack S)
{
    S->top++;
    S->Data[S->top] = Num;
    return;
}
int Pop(Stack S)
{
    return S->Data[S->top--];
}
void Check(int Store[], int Length, Stack S)
{
    int Tem, j = 1, OldTop;
    for (int i = 0; i < Length; i++)
    {
        int account = S->top + 1;
        Tem = Store[i];
        if (0 == i)
        {
            for (; j <= Tem; j++)
            {
                Push(j, S);
                account++;
            }
            if (account > S->Capacity)
            {
                puts("NO");
                return;
            }
            OldTop = Pop(S);
        }
        else if (OldTop > Tem)
        {
            OldTop = Pop(S);
            if (Tem != OldTop)
            {
                puts("NO");
                return;
            }
        }
        else if (OldTop < Tem)
        {
            for (; j <= Tem; j++)
            {
                Push(j, S);
                account++;
            }
            if (account > S->Capacity)
            {
                puts("NO");
                return;
            }
            OldTop = Pop(S);
        }
    }
    puts("YES");
    return;
}
