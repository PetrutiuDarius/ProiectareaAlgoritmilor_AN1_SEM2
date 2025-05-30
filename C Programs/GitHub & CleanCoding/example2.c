/*parcurgerge  graf cu DFS/BFS*/

// Imi cer scuze in avans

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GRAPH;

/// utils

NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GRAPH *create_graph(int vertices)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GRAPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

int insert_edges(GRAPH *graph, int nr_of_vertices, int nr_of_edges)
{
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices - 1);
    for (int i = 0; i < nr_of_edges; i++)
    {
        printf("De la: ");
        scanf("%d", &src);
        printf("Pana la: ");
        scanf("%d", &dest);
        add_edge(graph, src, dest);
    }
}

/// bfs utils
int is_empty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = create_node(data);
    if (is_empty(*queue))
    {
        *queue = new_node;
    }
    else
    {
        NODE *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    return data;
}

void wipe_visited_list(GRAPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(GRAPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);
    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{

    int nr_of_vertices, nr_of_edges, starting_vertex;

    printf("Introdu cate noduri are graful: ");
    scanf("%d", &nr_of_vertices);

    printf("Introdu cate muchii are graful: ");
    scanf("%d", &nr_of_edges);

    GRAPH *graph = create_graph(nr_of_vertices);

    insert_edges(graph, nr_of_vertices, nr_of_edges);

    printf("Introdu de unde plecam in DFS: ");
    scanf("%d", &starting_vertex); // =)))

    printf("parcurgere cu DFS:");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph, nr_of_vertices);
    printf("\n");

    printf("Introdu de unde plecam in BFS: ");
    scanf("%d", &starting_vertex);

    printf("parcurgere cu BFS:");
    BFS(graph, starting_vertex);

    return 0;
}
