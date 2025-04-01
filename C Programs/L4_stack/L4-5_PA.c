/*Realizați o coadă folosind 2 stive.*/
#include <stdio.h>
int topd = 0, tops = 0;
void enqueue(int vs[], int vd[], int x, int n)
{
    if (tops == n)
    {
        printf("\nQueue is full.");
        return;
    }
    else if (topd != n)
    {
        topd = topd + 1;
        vd[topd] = x;
    }
    else
    {
        tops = tops + 1;
        vs[tops] = x;
    }
}
void dequeue(int vs[], int vd[], int n)
{
    int x, y[20];
    if (topd == 0)
    {
        printf("\nQueue is empty.");
        return;
    }
    else
    {
        x = vd[topd - (topd - 1)];
        printf("\nData %d was dequeued.", x);
        x = topd;

        for (int i = 0; i < x && topd != 1; i++)
        {
            y[i] = vd[topd];
            topd--;
        }
        topd = 0;
        for (int i = x - 2; i >= 0; i--)
            enqueue(vs, vd, y[i], n);
        if (tops == 0)
            return;
        else
        {
            x = tops;
            for (int i = 0; i < x && tops != 0; i++)
            {
                y[i] = vs[tops];
                tops--;
            }
            tops = 0;
            for (int i = x - 1; i >= 0; i--)
                enqueue(vs, vd, y[i], n);
        }
    }
}

void printq(int vd[], int vs[], int n)
{
    printf("\nQueue: ");
    for (int i = 1; i < topd; i++)
        printf(" %d ,", vd[i]);
    if (tops == 0)
    {
        printf(" %d .", vd[topd]);
        return;
    }
    else
    {
        printf(" %d .", vd[topd]);
        for (int i = 1; i < tops; i++)
            printf(" %d ,", vs[i]);
        printf(" %d .", vs[tops]);
    }
}
int main()
{
    int n = 5;
    int vd[n], vs[n];
    enqueue(vs, vd, 2, n);
    enqueue(vs, vd, 3, n);
    enqueue(vs, vd, 4, n);
    enqueue(vs, vd, 5, n);
    enqueue(vs, vd, 6, n);
    enqueue(vs, vd, 8, n);
    enqueue(vs, vd, 7, n);
    printq(vd, vs, n);
    dequeue(vs, vd, n);
    dequeue(vs, vd, n);
    printq(vd, vs, n);
}