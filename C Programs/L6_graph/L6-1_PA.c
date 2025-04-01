#include <stdio.h>
#include <stdlib.h>
#define N 9
struct node
{
    int dest;
    struct node *next;
};
struct graph
{
    int visited[N];
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
struct queue *createQueue();
void enqueue(struct queue *q, int);
int dequeue(struct queue *q);
int isEmpty(struct queue *q);
struct graph *create(struct edge edges[], int n)
{
    unsigned i;
    struct graph *graph = (struct graph *)malloc(sizeof(struct graph));
    for (i = 0; i < N; i++)
    {
        graph->head[i] = NULL;
        graph->visited[i] = 0;
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
            printf("(%d -> %d)\t", i, ptr->dest);
            ptr = ptr->next;
        }
        printf("\n");
    }
}
void dfs(struct graph *graph, int vertex)
{
    struct node *adjlist = graph->head[vertex];
    struct node *temp = adjlist;
    graph->visited[vertex] = 1;
    printf(" %d; ", vertex);
    while (temp != NULL)
    {
        int connectedvertex = temp->dest;
        if (graph->visited[connectedvertex] == 0)
            dfs(graph, connectedvertex);
        temp = temp->next;
    }
}
void bfs(struct graph *graph, int vertex)
{
    struct queue *q = createQueue();
    graph->visited[vertex] = 1;
    enqueue(q, vertex);
    while (!isEmpty(q))
    {
        int currentvertex = dequeue(q);
        printf(" %d; ", currentvertex);
        struct node *temp = graph->head[currentvertex];
        while (temp)
        {
            int headvertex = temp->dest;
            if (graph->visited[headvertex] == 0)
            {
                graph->visited[headvertex] = 1;
                enqueue(q, headvertex);
            }
            temp = temp->next;
        }
    }
}
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
int main()
{
    struct edge edges[] =
        {
            {0, 7},
            {1, 2},
            {0, 3},
            {0, 1},
            {3, 6},
            {4, 5},
            {3, 4},
            {7, 8}};
    int n = sizeof(edges) / sizeof(edges[0]);
    struct graph *graph = create(edges, n);
    printf("Lista de adiacenta a garfului: \n");
    print(graph);
    printf("Graful parcurs folosind Depth First Search:\n");
    for (int i = 0; i < N; i++)
    {
        if (graph->visited[i] == 0)
            dfs(graph, i);
    }
    for (int i = 0; i < N; i++)
        graph->visited[i] = 0;
    printf("\nGraful parcurs folosind Breadth First Search:\n");
    for (int i = 0; i < N; i++)
    {
        if (graph->visited[i] == 0)
            bfs(graph, i);
    }
    return 0;
}