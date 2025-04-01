/*Implementați două stive folosind un singur vector. Trebuie să folosiți operațiile de push si pop ca să umpleți stivele și să le goliți.*/
#include <stdio.h>
void push(int v[], int x,int n,int *top)
{
    if (*top == n)
    {
        printf("\nStack Overflow.");
        return;
    }
    *top = *top + 1;
    v[*top] = x;
}
void pop(int v[],int *top)
{
    int x;
    if (*top == 0)
    {
        printf("\nStack is empty.");
        return;
    }
    x = v[*top];
    *top = *top - 1;
    printf("\nData %d was popped.", x);
}
int main()
{
    int n = 20;
    int top1 = 0, top2 = 9;
    int v[n];
    push(v, 2, 10, &top1);
    push(v, 3, 10, &top1);
    push(v, 5, 10, &top1);
    push(v, 7, 10, &top1);
    push(v, 2, 10, &top1);
    push(v, 6, n, &top2);
    push(v, 1, n, &top2);
    push(v, 9, n, &top2);
    push(v, 10, n, &top2);
    push(v, 8, n, &top2);
    push(v, 4, n, &top2);
    push(v, 5, n, &top2);
    printf("\nStack 1: ");
     for (int i = 1; i < top1; i++)
         printf(" %d ,", v[i]);
     printf(" %d .", v[top1]);
     printf("\nStack 2: ");
     for (int i = 10; i < top2; i++)
         printf(" %d ,", v[i]);
     printf(" %d .", v[top2]);
     pop(v, &top1);
     pop(v, &top2);
}