#include <stdio.h>
#include <stdlib.h>
int k = 0;
void printint(int v[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        printf(" %d ,", v[i]);
    }
    printf(" %d .\n", v[n - 1]);
}
void printfloat(float v[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        printf(" %.3f ,", v[i]);
    }
    printf(" %.3f .\n", v[n - 1]);
}
void printchar(char v[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        printf(" %c ,", v[i]);
    }
    printf(" %c .\n", v[n - 1]);
}
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
    printf("Prima lista: ");
    printint(x, n);
}
void bubblesortf(float v[], int n)

{
    float k;
    float x[n];
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
    printf("A doua lista: ");
    printfloat(x, n);
}
void bubblesortc(char v[], int n)

{
    char k;
    char x[n];
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
    printf("A treia lista: ");
    printchar(x, n);
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
    printf("Prima lista: ");
    printint(x, n);
}
void insertionf(float v[], int n)
{
    float k, x[n];
    int j;
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
    printf("A doua lista: ");
    printfloat(x, n);
}
void insertionc(char v[], int n)
{
    char k, x[n];
    int j;
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
    printf("A treia lista: ");
    printchar(x, n);
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
    printf("Prima lista: ");
    printint(x, n);
}
void selectionf(float v[], int n)
{
    float k, x[n];
    int m;
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
    printf("A doua lista: ");
    printfloat(x, n);
}
void selectionc(char v[], int n)
{
    char k, x[n];
    int m;
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
    printf("A treia lista: ");
    printchar(x, n);
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
    {
        printf("Prima lista: ");
        printint(v, n + 1);
    }
}
void mergef(float v[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    float L1[n1], L2[n2];
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
void mergesortf(float v[], int l, int n, int x)
{
    int m;
    if (l < n)
    {
        m = l + (n - l) / 2;
        mergesortf(v, l, m, x + 1);
        mergesortf(v, m + 1, n, x + 1);
        mergef(v, l, m, n);
    }
    if (x == 0)
    {
        printf("A doua lista: ");
        printfloat(v, n + 1);
    }
}
void mergec(char v[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    char L1[n1], L2[n2];
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
void mergesortc(char v[], int l, int n, int x)
{
    int m;
    if (l < n)
    {
        m = l + (n - l) / 2;
        mergesortc(v, l, m, x + 1);
        mergesortc(v, m + 1, n, x + 1);
        mergec(v, l, m, n);
    }
    if (x == 0)
    {
        printf("A treia lista: ");
        printchar(v, n + 1);
    }
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
        printf("Prima lista: ");
        printint(v, h + 1);
    }
}
float partitionf(float v[], int l, int h)
{
    float k;
    float p = v[h];
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
void quicksortf(float v[], int l, int h, int x)
{
    if (l < h)
    {
        float p = partitionf(v, l, h);
        quicksortf(v, l, p - 1, x + 1);
        quicksortf(v, p + 1, h, x + 1);
    }
    if (x == 0)
    {
        printf("A doua lista: ");
        printfloat(v, h + 1);
    }
}
float partitionc(char v[], int l, int h)
{
    char k;
    char p = v[h];
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
void quicksortc(char v[], int l, int h, int x)
{
    if (l < h)
    {
        char p = partitionc(v, l, h);
        quicksortc(v, l, p - 1, x + 1);
        quicksortc(v, p + 1, h, x + 1);
    }
    if (x == 0)
    {
        printf("A treia lista: ");
        printchar(v, h + 1);
    }
}
int main()
{
    int a[10] = {-47, 46, -91, -64, 100, 92, -20, 83, -12, 10}, x[10], l = 0;
    float b[10] = {90.675, -60.980, 86.10, 4.99, 30.2682854, -29.178584028, -86.58683, -51.1535, -76.40793, 32.169}, y[10];
    char c[10] = {'C', 'Y', 'E', 'B', 'D', 'W', 'a', 'O', 's', 'Y'}, z[10];
    printf("Prima lista: ");
    printint(a, 10);
    printf("A doua lista: ");
    printfloat(b, 10);
    printf("A treia lista: ");
    printchar(c, 10);
    printf("\nSortari folosind Bubble Sort:\n");
    bubblesorti(a, 10);
    bubblesortf(b, 10);
    bubblesortc(c, 10);
    printf("\nSortari folosind Insertion Sort:\n");
    insertioni(a, 10);
    insertionf(b, 10);
    insertionc(c, 10);
    printf("\nSortari folosind Selection Sort:\n");
    selectioni(a, 10);
    selectionf(b, 10);
    selectionc(c, 10);
    printf("\nSortari folosind Merge Sort:\n");
    for (int i = 0; i < 10; i++)
        x[i] = a[i];
    mergesorti(x, 0, 10 - 1, l);
    for (int i = 0; i < 10; i++)
        y[i] = b[i];
    mergesortf(y, 0, 10 - 1, l);
    for (int i = 0; i < 10; i++)
        z[i] = c[i];
    mergesortc(z, 0, 10 - 1, l);
    printf("\nSortari folosind Quick Sort:\n");
    for (int i = 0; i < 10; i++)
        x[i] = a[i];
    quicksorti(x, 0, 10 - 1, l);
    for (int i = 0; i < 10; i++)
        y[i] = b[i];
    quicksortf(y, 0, 10 - 1, l);
    for (int i = 0; i < 10; i++)
        z[i] = c[i];
    quicksortc(z, 0, 10 - 1, l);
    return 0;
}