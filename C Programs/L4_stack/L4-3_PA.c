#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int front = 1, rear = 0;
void enqueue(char v[][20], char *x, int n)
{
    rear = rear + 1;
    strcpy(v[rear], x);
}
void printq(char v[][20])
{
    printf("\nLista jucatori: ");
    for (int i = front; i < rear; i++)
        printf(" %s ,", v[i]);
    printf(" %s ;", v[rear]);
}
void game(char nume[][20], int n)
{
    int i = 0;
    while (i < n)
    {
        char x[20];
        int r = rand() % 10;
        while (r != 0)
        {
            strcpy(x, nume[front]);
            front = front + 1;
            enqueue(nume, x, n);
            r--;
        }
        printf("\nJucatorul de pozitia %d este : %s", n - i, nume[front]);
        front = front + 1;
        i++;
    }
}
int main()
{
    int n;
    printf("Introduceti numarul de jucatori: ");
    scanf(" %d", &n);
    char nume[n][20], x[20];
    for (int i = 0; i < n; i++)
    {
        printf("Introdu numele jucatorului %d :", i + 1);
        scanf("%19s", &x);
        enqueue(nume, x, n);
    }
    printq(nume);
    game(nume, n);
    return 0;
}