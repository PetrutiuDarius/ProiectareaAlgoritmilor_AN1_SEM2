/*Realizați un algoritm care să calculeze distanța dintre cel mai mare și cel mai mic nod dintr-un graf neorientat ce ține ca date în noduri numere. Tratați și cazurile în care mai multe noduri au aceeași valoare.*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 9
struct node
{
    int dest;
    struct node *next;
};
struct graph
{
    int visited[N];
    int data[N];
    struct node *head[N];
};
struct edge
{
    int src, dest;
};
struct queue
{
    int data[N];
    int front;
    int rear;
};
struct queue *createQueue()
{
    struct queue *q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}
int isEmpty(struct queue *q)
{
    if (q->rear == -1)
        return 1;
    else
        return 0;
}
void enqueue(struct queue *q, int value)
{
    if (q->rear == N - 1)
        printf("\nQueue is Full!!");
    else
    {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->data[q->rear] = value;
    }
}
int dequeue(struct queue *q)
{
    int item;
    if (isEmpty(q))
    {
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = q->data[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            q->front = q->rear = -1;
        }
    }
    return item;
}
struct graph *create(struct edge edges[], int n, int d[])
{
    unsigned i;
    struct graph *graph = (struct graph *)malloc(sizeof(struct graph));
    for (i = 0; i < N; i++)
    {
        graph->head[i] = NULL;
        graph->visited[i] = 0;
        graph->data[i] = d[i];
    }
    for (i = 0; i < n; i++)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->dest = dest;
        newnode->next = graph->head[src];
        graph->head[src] = newnode;
    }
    return graph;
}
void print(struct graph *graph)
{
    int i;
    for (i = 0; i < N; i++)
    {
        struct node *ptr = graph->head[i];

        while (ptr != NULL)
        {
            int x = ptr->dest;
            printf("[%d ( %d ) -> %d ( %d )]\t", i, graph->data[i], x, graph->data[x]);
            ptr = ptr->next;
        }
        printf("\n");
    }
}
void distance(struct graph *graph, int m, int M)
{
    struct queue *qd = createQueue();
    enqueue(qd, m);
    int distance[N];
    for (int i = 1; i < N; i++)
    {
        distance[i] = INT_MAX;
        graph->visited[i] = 0;
    }
    distance[m] = 0;
    while (!isEmpty(qd))
    {
        int currentvertex = dequeue(qd);
        struct node *temp = graph->head[currentvertex];
        while (temp)
        {
            int headvertex = temp->dest;
            if (graph->visited[headvertex] == 0)
            {
                graph->visited[headvertex] = 1;
                distance[headvertex] = distance[currentvertex] + 1;
                if (headvertex == M)
                {
                    printf("Distanta cea mai mica de la nodul %d la nodul %d este %d.\n", m, M, distance[M]);
                    return;
                }
                enqueue(qd, headvertex);
            }
            temp = temp->next;
        }
    }
    printf("Nicio ruta nu duce din nodul %d in nodul %d.\n", m, M);
}
void dmM(struct graph *graph, int vertex)
{
    struct queue *q = createQueue();
    enqueue(q, vertex);
    int m = vertex, M = vertex;
    while (!isEmpty(q))
    {
        int currentvertex = dequeue(q);
        struct node *temp = graph->head[currentvertex];
        while (temp)
        {
            int headvertex = temp->dest;
            if (graph->visited[headvertex] == 0)
            {
                graph->visited[headvertex] = 1;
                if (graph->data[headvertex] > graph->data[M])
                    M = headvertex;
                if (graph->data[headvertex] < graph->data[m])
                    m = headvertex;
                enqueue(q, headvertex);
            }
            temp = temp->next;
        }
    }
    // m este index-ul nodului cu cel mai mic numar
    // M este index-ul nodului cu cel mai mare numar
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (graph->data[i] == graph->data[m] && graph->data[j] == graph->data[M])
            {
                printf("Nodul %d are valoarea cea mai mica(%d).\n", i, graph->data[i]);
                printf("Nodul %d are valoarea cea mai mare(%d).\n", j, graph->data[j]);
                distance(graph, i, j);
            }
        }
}
int main()
{
    struct edge edges[] =
        {
            {0, 1},
            {0, 2},
            {1, 2},
            {1, 0},
            {2, 3},
            {2, 0},
            {2, 1},
            {3, 2},
            {3, 4},
            {4, 3},
            {4, 5},
            {5, 4},
            {5, 6},
            {6, 5},
            {6, 7},
            {6, 8},
            {7, 6},
            {7, 8},
            {8, 6},
            {8, 7}};
    int data[N] = {
        8,
        5,
        30,
        12,
        45,
        5,
        13,
        60,
        99};
    int n = sizeof(edges) / sizeof(edges[0]);
    struct graph *graph = create(edges, n, data);
    printf("Lista de adiacenta a garfului: \n");
    print(graph);
    dmM(graph, 0); /*Apelarea functiei care imi afla distanta/distantele de la nodul cu nr cel mai mic la nodul cu nr cel mai mare.*/
}