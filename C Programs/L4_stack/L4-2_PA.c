#include <stdio.h>
#include <string.h>
int const n = 6;
int top = 0;
void push(char v[][50], char *x)
{
    if (top == n)
    {
        printf("\nStack Overflow.");
        return;
    }
    top = top + 1;
    strcpy(v[top], x);
}
void reverse(char v[][50], int n)
{
    int i = 0;
    char x[n][50];
    if (top == 0)
    {
        printf("\nStack is empty.");
        return;
    }
    while (top != 0)
    {
        strcpy(x[i], v[top]);
        top = top - 1;
        i++;
    }
    for (int j = 0; j < i; j++)
        push(v, x[j]);
}
void prints(char v[][50])
{
    printf("\nStack: ");
    for (int i = 1; i < top; i++)
        printf(" %s ,", v[i]);
    printf(" %s ;", v[top]);
}
int main()
{
    char v[n][50];
    push(v, "Ana");
    push(v, " ");
    push(v, "are");
    push(v, " ");
    push(v, "mere");
    push(v, ".");
    prints(v);
    reverse(v, n);
    prints(v);
}