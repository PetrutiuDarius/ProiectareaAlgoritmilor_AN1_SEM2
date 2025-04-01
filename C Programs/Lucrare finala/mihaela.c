#include <stdio.h>
// #include <conio.h>
int grad(int a[10][10], int n, int v)
{
    int g = 0, i;
    for (i = 0; i < n; i++)
        if (a[v][i] == 1)
            g = g + 1;

    return g;
}
int main()
{
    int a[10][10], i, j, m, n, v1, v2, v;
    printf("dati numarul de noduri");
    scanf("%d", &n);
    printf("\ndati numarul de muchii");
    scanf("%d", &m);
    printf("\n dati varful cerut");
    scanf("%d", &v);
    printf("\n");

    for (i = 0; i < m; i++)
    {
        printf("citim muchia");
        scanf("%d", &v1);
        printf("->");
        scanf("%d", &v2);
        printf("\n");
        a[v1][v2] = 1;
        a[v2][v1] = 1;
    }

    j = grad(a, n, v);
    printf("gradul varfului este %d", j);
}
