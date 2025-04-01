/*Creati un vector cu 10000 de valori random. Să se afișeze timpul de rulare al fiecărui algoritm și care a fost cel mai performant.*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void bubblesorti(int v[], int n)
{
    int k, x[n];
    for (int i = 0; i < n; i++)
        x[i] = v[i];
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++)
            if (x[j] > x[j + 1])
            {
                k = x[j];
                x[j] = x[j + 1];
                x[j + 1] = k;
            }
    printf("\nBubble Sort: ");
}
void insertioni(int v[], int n)
{
    int k, x[n], j;
    for (int i = 0; i < n; i++)
        x[i] = v[i];
    for (int i = 1; i < n; i++)
    {
        k = x[i];
        j = i - 1;
        while (j >= 0 && x[j] > k)
        {
            x[j + 1] = x[j];
            j--;
        }
        x[j + 1] = k;
    }
    printf("\nInsertion Sort: ");
}
void selectioni(int v[], int n)
{
    int k, x[n], m;
    for (int i = 0; i < n; i++)
        x[i] = v[i];
    for (int i = 0; i < n - 1; i++)
    {
        m = i;
        for (int j = i + 1; j < n; j++)
        {
            if (x[j] < x[m])
                m = j;
        }
        k = x[m];
        x[m] = x[i];
        x[i] = k;
    }
    printf("\nSelection Sort: ");
}
void mergei(int v[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int L1[n1], L2[n2];
    for (int i = 0; i < n1; i++)
        L1[i] = v[p + i];
    for (int j = 0; j < n2; j++)
        L2[j] = v[q + 1 + j];
    int i = 0, j = 0, k;
    k = p;
    while (i < n1 && j < n2)
    {
        if (L1[i] <= L2[j])
        {
            v[k] = L1[i];
            i++;
        }
        else
        {
            v[k] = L2[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        v[k] = L1[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        v[k] = L2[j];
        j++;
        k++;
    }
}
void mergesorti(int v[], int l, int n, int x)
{
    int m;
    if (l < n)
    {
        m = l + (n - l) / 2;
        mergesorti(v, l, m, x + 1);
        mergesorti(v, m + 1, n, x + 1);
        mergei(v, l, m, n);
    }
    if (x == 0)
        printf("\nMerge Sort: ");
}
int partitioni(int v[], int l, int h)
{
    int k;
    int p = v[h];
    int i = l - 1;
    for (int j = l; j < h; j++)
        if (v[j] <= p)
        {
            i++;
            k = v[i];
            v[i] = v[j];
            v[j] = k;
        }
    k = v[i + 1];
    v[i + 1] = v[h];
    v[h] = k;
    return (i + 1);
}
void quicksorti(int v[], int l, int h, int x)
{
    if (l < h)
    {
        int p = partitioni(v, l, h);
        quicksorti(v, l, p - 1, x + 1);
        quicksorti(v, p + 1, h, x + 1);
    }
    if (x == 0)
    {
        printf("\nQuick Sort: ");
    }
}
int main()
{
    printf("Am incercat cu 50000 de valori pentru a se vedea diferenta mai bine.");
    int n = 50001;
    int v[n], l = 0, x[n];
    double tt;
    clock_t t;
    for (int i = 0; i < n - 1; i++)
    {
        v[i] = rand();
    }
    t = clock();
    bubblesorti(v, n);
    t = clock() - t;
    tt = ((double)t) / CLOCKS_PER_SEC;
    printf(" %f secunde pentru executie.", tt);
    t = clock();
    insertioni(v, n);
    t = clock() - t;
    tt = ((double)t) / CLOCKS_PER_SEC;
    printf(" %f secunde pentru executie.", tt);
    t = clock();
    selectioni(v, n);
    t = clock() - t;
    tt = ((double)t) / CLOCKS_PER_SEC;
    printf(" %f secunde pentru executie.", tt);
    for (int i = 0; i < n - 1; i++)
        x[i] = v[i];
    t = clock();
    mergesorti(x, 0, n, l);
    t = clock() - t;
    tt = ((double)t) / CLOCKS_PER_SEC;
    printf(" %f secunde pentru executie.", tt);
    for (int i = 0; i < n - 1; i++)
        x[i] = v[i];
    t = clock();
    quicksorti(x, 0, n, l);
    t = clock() - t;
    tt = ((double)t) / CLOCKS_PER_SEC;
    printf(" %f secunde pentru executie.", tt);
}