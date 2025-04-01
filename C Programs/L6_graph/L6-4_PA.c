/*Realizați un algoritm care să detecteze dacă într-un graf orientat există un drum între două noduri date*/
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
void path(struct graph *graph, int start, int end, int *found)
{
    struct node *adjlist = graph->head[start];
    struct node *temp = adjlist;
    graph->visited[start] = 1;
    if (start == end)
    {
        *found = 1;
        return;
    }
    while (temp != NULL && !(*found))
    {
        int connectedvertex = temp->dest;
        if (graph->visited[connectedvertex] == 0)
            path(graph, connectedvertex, end, found);
        temp = temp->next;
    }
}
int main()
{
    struct edge edges[] =
        {
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
    int x, y, z = N - 1;
    printf("Introduceti indexul nodurilor intre care sa se verifice daca exista drum(de la 0 la %d): ", z);
    printf("\nNodul 1: ");
    scanf("%d", &x);
    printf("Nodul 2: ");
    scanf("%d", &y);
    int found = 0;
    path(graph, x, y, &found);
    if (found)
        printf("Exista drum intre nodurile %d si %d.", x, y);
    else
        printf("Nu exista drum intre nodurile %d si %d.", x, y);
}