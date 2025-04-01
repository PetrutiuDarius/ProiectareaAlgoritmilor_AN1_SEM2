/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct graph
{
    int node_number;
    int *visited;
    struct Node **head;
} GRAPH;

typedef struct stack
{
    int top;
    int stack_capacity;
    int *stack_area;
} STACK;

NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

void add_edge(GRAPH *graph, int src, int dest)
{
    NODE *newNode = create_node(dest);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
}

GRAPH *create_graph(int node_number)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->node_number = node_number;
    graph->head = malloc(node_number * sizeof(NODE *));
    graph->visited = malloc(node_number * sizeof(int));

    for (int i = 0; i < node_number; i++)
    {
        graph->head[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK *create_stack(int stack_capacity)
{
    STACK *s = malloc(sizeof(STACK));
    s->stack_area = malloc(stack_capacity * sizeof(int));
    s->top = -1;
    s->stack_capacity = stack_capacity;

    return s;
}

void push(int x, STACK *s)
{
    s->top = s->top + 1;
    s->stack_area[s->top] = x;
}

void DFS(GRAPH *graph, STACK *s, int vertex)
{
    NODE *adj_list = graph->head[vertex];
    NODE *aux = adj_list;
    graph->visited[vertex] = 1;
    push(vertex, s);
    while (aux != NULL)
    {
        int current_vertex = aux->data;
        if (graph->visited[current_vertex] == 0)
            DFS(graph, s, current_vertex);
        aux = aux->next;
    }
}

void insert_edges(GRAPH *graph, int edge_number, int node_number)
{
    int src, dest;
    printf("adauga %d munchii (de la 0 la %d)\n", edge_number, node_number - 1);
    for (int i = 0; i < edge_number; i++)
    {
        printf("De la: ");
        scanf("%d", &src);
        printf("Pana la: ");
        scanf("%d", &dest);
        add_edge(graph, src, dest);
    }
}

void reset_visited(GRAPH *graph, int node_number)
{
    for (int i = 0; i < node_number; i++)
    {
        graph->visited[i] = 0;
    }
}

int path_verification(GRAPH *graph, int node_number, STACK *s1, STACK *s2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int path_exists = 0;
    for (int i = 0; i < node_number; i++) // aici i tine loc de numar adica de restaurant
    {
        for (int j = 0; j < node_number; j++)
        {
            if (i != j)
            {
                reset_visited(graph, node_number);
                DFS(graph, s1, i);
                reset_visited(graph, node_number);
                DFS(graph, s2, j);

                int found_path = 0;
                for (int k = 0; k <= s1->top && !found_path; k++)
                {
                    for (int l = 0; l <= s2->top && !found_path; l++)
                    {
                        if (s1->stack_area[k] == s2->stack_area[l])
                        {
                            found_path = 1;
                            break;
                        }
                    }
                }
                if (found_path)
                {
                    path_exists = 1;
                    break;
                }
            }
        }
    }
    return path_exists;
}

int main()
{

    int node_number;
    int edge_number;

    printf("Cate noduri are graful: ");
    scanf("%d", &node_number);

    printf("Cate muchii are graful: ");
    scanf("%d", &edge_number);

    GRAPH *graph = create_graph(node_number);

    STACK *s1 = create_stack(2 * node_number);
    STACK *s2 = create_stack(2 * node_number);

    insert_edges(graph, edge_number, node_number);

    if (path_verification(graph, node_number, s1, s2))
        printf("Exista drum.");
    else
        printf("Nu exista drum.");
}