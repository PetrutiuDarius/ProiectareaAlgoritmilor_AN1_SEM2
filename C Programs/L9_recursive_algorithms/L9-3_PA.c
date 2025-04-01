#include <stdlib.h>
#include <stdio.h>

int afisare_vector(int v[], int n)
{
    if (n < 0)
    {
        return 0;
    }
    else
    {
        afisare_vector(v, n - 1);
    }
    printf("%d ", v[n]);
}

int main()
{
    int v[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("\nVectorul afisat recursiv este: ");
    afisare_vector(v, 9);
}