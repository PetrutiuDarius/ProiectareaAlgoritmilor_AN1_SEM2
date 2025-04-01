#include <stdio.h>
int const n = 5;
int top = 0;
int front = 1, rear = 0;
void push(int v[], int x)
{
    if (top == n)
    {
        printf("\nStack Overflow.");
        return;
    }
    top = top + 1;
    v[top] = x;
}
void pop(int v[])
{
    int x;
    if (top == 0)
    {
        printf("\nStack is empty.");
        return;
    }
    x = v[top];
    top = top - 1;
    printf("\nData %d was popped.", x);
}
void enqueue(int v[], int x)
{
    if (rear == n)
    {
        printf("\nQueue is full.");
        return;
    }
    rear = rear + 1;
    v[rear] = x;
}
void dequeue(int v[])
{
    int x;
    if (rear == 0)
    {
        printf("\nQueue is empty.");
        return;
    }
    x = v[front];
    front = front + 1;
    printf("\nData %d was dequeue.", x);
}
void prints(int v[])
{
    printf("\nStack: ");
    for (int i = 1; i < top; i++)
        printf(" %d ,", v[i]);
    printf(" %d .", v[top]);
}
void printq(int v[])
{
    printf("\nQueue: ");
    for (int i = front; i < rear; i++)
        printf(" %d ,", v[i]);
    printf(" %d .", v[rear]);
}
void issempty(int v[])
{
    if (top == 0)
        printf("\nStack is empty.");
    else
        return;
}
void isqempty(int v[])
{
    if (rear == 0)
        printf("\nQueue is empty.");
}
void issfull(int v[])
{
    if (top == n)
        printf("\nStack is full.");
    else
        return;
}
void isqfull(int v[])
{
    if (rear == n)
        printf("\nQueue is full.");
}
void peeks(int v[])
{
    if (top == 0)
    {
        printf("\nStack is empty.");
        return;
    }
    printf("\nTop data in stack is: %d .", v[top]);
}
void peekq(int v[])
{
    if (rear == 0)
    {
        printf("\nQueue is empty.");
        return;
    }
    printf("\nLast data in queue is: %d .", v[rear]);
}
int main()
{
    int v[n], w[n];
    issempty(v);
    isqempty(w);
    push(v, 6);
    push(v, 5);
    push(v, 7);
    enqueue(w, 3);
    enqueue(w, 5);
    enqueue(w, 6);
    enqueue(w, 7);
    enqueue(w, 3);
    prints(v);
    printq(w);
    isqfull(w);
    pop(v);
    dequeue(w);
    dequeue(w);
    prints(v);
    printq(w);
    peeks(v);
    peekq(w);
}