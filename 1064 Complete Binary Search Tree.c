#include<stdio.h>
#include<stdlib.h>
typedef struct treenode* tree;
struct treenode
{
    int data;
    tree left;
    tree right;
};
void rearrange(int*, int);
int numberlay(int);
tree createtree(void);
tree treeinsert(int* array, int first, int last);
tree find(tree, int);
tree findinsert(tree t, int data);
int* output(tree, int);
int main(void)
{
    tree head = NULL;
    int length;
    int* array, * restarray, * mainarray, * result;
    int lay, complete = 1, rest;
    scanf("%d", &length);
    array = (int*)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
        scanf("%d", &array[i]);
    if (length > 1)
        rearrange(array, length);
    lay = numberlay(length);
    for (int i = 0; i < lay; i++)
        complete *= 2;
    complete--;
    rest = length - complete;
    restarray = (int*)malloc(sizeof(int) * rest);//最下面一排元素
    mainarray = (int*)malloc(sizeof(int) * complete);//排除最下面一排的完整二叉树
    for (int i = 0; i < rest; i++)
    {
        restarray[i] = array[i * 2];//最下面一排的数从左往右依次增大，最左边为最小的数，然后为第3小，第5小
        array[i * 2] = -1;
    }
    for (int i = 0, j = 0; j < complete; i++)
    {
        if (array[i] != -1)
        {
            mainarray[j] = array[i];
            j++;
        }
    }
    free(array);
    head = treeinsert(mainarray, 0, complete);
    free(mainarray);
    if (rest)
    {
        for (int i = 0; i < rest; i++)
        {
            head = findinsert(head, restarray[i]);
        }
    }
    free(restarray);
    result = output(head, length);
    printf("%d", result[0]);
    for (int i = 1; i < length; i++)
        printf(" %d", result[i]);
    return 0;
}
void rearrange(int* array, int length)
{
    for (int i = 1; i < length; i++)
    {
        int trans = array[i];
        int j;
        for (j = i - 1; j >= 0; j--)
        {
            if (trans < array[j])
                array[j + 1] = array[j];
            else
                break;
        }
        array[j + 1] = trans;
    }
}
int numberlay(int length)
{
    if (length == 0)
        return 0;
    int lay;
    int two = 1;
    for (lay = 1;; lay++)
    {
        two *= 2;
        if (two - 1 > length)
            break;
    }
    lay--;//求出层数
    return lay;
}
tree createtree(void)
{
    tree New = (tree)malloc(sizeof(struct treenode));
    New->left = NULL;
    New->right = NULL;
    return New;
}
tree treeinsert(int* array, int first, int last)
{
    if (first > last)
        return NULL;
    int data = array[(first + last) / 2];
    tree New = createtree();
    New->data = data;
    New->left = treeinsert(array, first, (first + last) / 2 - 1);
    New->right = treeinsert(array, (first + last) / 2 + 1, last);
    return New;
}
tree find(tree t, int data)
{
    if (data < t->data)
        t = find(t->left, data);
    else if (data > t->data)
        t = find(t->right, data);
    return t;
}
tree findinsert(tree t, int data)
{
    if (!t)
    {
        t = createtree();
        t->data = data;
    }
    else if (data < t->data)
    {
        t->left = findinsert(t->left, data);
    }
    else if (data > t->data)
    {
        t->right = findinsert(t->right, data);
    }
    return t;
}
int* output(tree node, int length)
{
    if (!length)
        return NULL;
    int* array;
    tree tem;
    array = (int*)malloc(sizeof(int) * (length));
    array[0] = node->data;
    for (int i = 0, j = 0; i < length; j++)
    {
        tem = find(node, array[j]);
        if (tem->left)
            array[++i] = tem->left->data;
        if (tem->right)
            array[++i] = tem->right->data;
    }
    return array;
}
