/*Realizați un algoritm care să detecteze dacă există cicluri într-un graf neorientat.*/
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
struct graph *create(struct edge edges[], int n, int d[])
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
            int x = ptr->dest;
            printf("[%d -> %d]\t", i, x);
            ptr = ptr->next;
        }
        printf("\n");
    }
}
int cycle(struct graph *graph, int vertex, int parent)
{
    struct node *adjlist = graph->head[vertex];
    struct node *temp = adjlist;
    graph->visited[vertex] = 1;
    while (temp != NULL)
    {
        int connectedvertex = temp->dest;
        if (graph->visited[connectedvertex] == 0)
        {
            if (cycle(graph, connectedvertex, vertex))
                return 1;
        }
        else if (connectedvertex != parent)
            return 1;
        temp = temp->next;
    }
    return 0;
}
int main()
{
    struct edge edges[] =
        {
            {0, 1},
            {0, 2},
            //{1, 2},
            {1, 0},
            {2, 3},
            {2, 0},
            //{2, 1},
            {3, 2},
            {3, 4},
            {4, 3},
            {4, 5},
            {5, 4},
            {5, 6},
            {6, 5},
            {6, 7},
            //{6, 8},
            {7, 6},
            {7, 8},
            //{8, 6},
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
    if (cycle(graph, 0, -1))
        printf("Graful are cicluri.\n");
    else
        printf("Graful nu are cicluri.\n");
}