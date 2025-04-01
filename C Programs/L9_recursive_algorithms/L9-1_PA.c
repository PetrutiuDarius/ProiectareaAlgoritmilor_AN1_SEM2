#include <stdio.h>
#include <stdlib.h>

int fibbonaci_recursiv(int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n <= 1)
    {
        return 1;
    }

    return fibbonaci_recursiv(n - 1) + fibbonaci_recursiv(n - 2);
}

void fibbonaci_iterativ(int n)
{
    int x = 0, y = 1, z;
    printf("%d %d ", x, y);
    for (int i = 2; i < n; i++)
    {
        z = x + y;
        x = y;
        y = z;

        printf("%d ", z);
    }
}

int main()
{
    int n, v[100], i;
    printf("Cati termeni sa aiba sirul lui Fibbonaci: ");
    scanf("%d", &n);

    printf("Sirul Fibbonaci afisat recursiv: ");
    for (i = 0; i < n; i++)
    {
        v[i] = fibbonaci_recursiv(i);
        printf("%d ", v[i]);
    }

    printf("\nSirul Fibbonaci afisat iterativ: ");
    fibbonaci_iterativ(n);
}