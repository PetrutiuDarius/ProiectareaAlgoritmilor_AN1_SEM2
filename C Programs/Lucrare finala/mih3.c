// recursiv, determina rezultatul ridicarii unei matrice de dimesniune n la o putere p data
#include <stdio.h>
#include <stdlib.h>

void putere(int v[][100], int x[][100], int p, int n)
{
    if (p == 1)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf(" %d ", v[i][j]);
            }
        }
        return;
    }
    int s = 0, y[100][100];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                s += v[i][k] * x[k][j];
            }
            y[i][j] = s;
            s = 0;
        }
    }
    putere(y, v, p--, n);
}

int main()
{
    int n, x;
    printf("Indicati dimensiunea matricei:");
    scanf("%d", &n);
    int v[100][100];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            printf("Scrieti numarul din matrice de pe pozitia %d %d : ", i, j);
            scanf("&d", &x);
            v[i][j] = x;
        }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf(" %d ", v[i][j]);
        }
        printf("\n");
    }
    int p;
    printf("Indicati puterea la care doriti sa ridicati matricea: ");
    scanf("%d", &p);
    putere(v, v, p, n);
}