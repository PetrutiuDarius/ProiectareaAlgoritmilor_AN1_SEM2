
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define N 12

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
    int src, dest, cost;
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
        int cost = edges[i].cost;
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->dest = dest;
        newnode->next = graph->head[src];
        graph->head[src] = newnode;
    }
    return graph;
}

void print(struct graph *graph, struct edge edges[], int n)
{
    int i, a;
    for (i = 0; i < N; i++)
    {
        struct node *ptr = graph->head[i];
        while (ptr != NULL)
        {
            // acest for este pentru a printa si costurile(nu sterge)
            for (int j = 0; j < n; j++)
            {
                if (edges[j].src == i && edges[j].dest == ptr->dest)
                {
                    a = j;
                    j = n;
                }
                else if (edges[j].src == ptr->dest && edges[j].dest == i)
                {
                    a = j;
                    j = n;
                }
            }
            printf("(%d -[%d]> %d)\t", i, edges[a].cost, ptr->dest);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void fprint(struct graph *graph, struct edge edges[], int n, FILE *out_file)
{
    int i, a;
    for (i = 0; i < N; i++)
    {
        struct node *ptr = graph->head[i];
        while (ptr != NULL)
        {
            // acest for este pentru a printa si costurile(nu sterge)
            for (int j = 0; j < n; j++)
            {
                if (edges[j].src == i && edges[j].dest == ptr->dest)
                {
                    a = j;
                    j = n;
                }
                else if (edges[j].src == ptr->dest && edges[j].dest == i)
                {
                    a = j;
                    j = n;
                }
            }
            fprintf(out_file, "(%d -[%d]> %d)\t", i, edges[a].cost, ptr->dest);
            ptr = ptr->next;
        }
        fprintf(out_file, "\n");
    }
}

// Functie pentru a citi dintr-un fisier csv muchiile unui graf
int read_import(FILE *in_file, struct edge **edges)
{
    char line[100];
    int count = 0;
    int a = N;

    while (fgets(line, sizeof(line), in_file) != NULL)
    {
        char *token = strtok(line, ",");
        if (token != NULL)
        {
            (*edges)[count].src = atoi(token);
            token = strtok(NULL, ",");
            if (token != NULL)
            {
                (*edges)[count].dest = atoi(token);
                token = strtok(NULL, ",");
                if (token != NULL)
                {
                    (*edges)[count].cost = atoi(token);
                    count++;
                    (*edges)[count].src = (*edges)[count - 1].dest;
                    (*edges)[count].dest = (*edges)[count - 1].src;
                    (*edges)[count].cost = (*edges)[count - 1].cost;
                    count++;
                    if (count >= N)
                    {
                        a *= 2;
                        *edges = realloc(*edges, a * sizeof(struct edge));
                    }
                }
            }
        }
    }
    return count;
}

int edge_cost(struct edge *edges, int src, int dest, int n)
{
    for (int i = 0; i < n; i++)
    {
        if ((edges[i].src == src && edges[i].dest == dest) ||
            (edges[i].src == dest && edges[i].dest == src))
        {
            return edges[i].cost;
        }
    }
    return INT_MAX;
}

void bellmanford(struct graph *graph, struct edge *edges, int source, int searched, int n, FILE *out_file)
{
    int cost[N];
    int parent[N];
    int unexplored[N];
    int explored[N];
    int i, j, min_dist, u;

    // Initializam nodurile
    for (i = 0; i < N; i++)
    {
        cost[i] = INT_MAX;
        parent[i] = -1;
        unexplored[i] = 1;
        explored[i] = 0;
    }

    // Costul pentru nodul sursa este 0
    cost[source] = 0;

    while (1)
    {
        // aflam nodul cu distanta minima de la sursa
        min_dist = INT_MAX;
        for (i = 0; i < N; i++)
        {
            if (unexplored[i] && cost[i] < min_dist)
            {
                min_dist = cost[i];
                u = i;
            }
        }

        // marcam nodul ca fiind explorat
        unexplored[u] = 0;
        explored[u] = 1;

        // actualizam costurile vecinilor nodului explorat
        struct node *ptr = graph->head[u];
        while (ptr != NULL)
        {
            int v = ptr->dest;
            // folosim functia edge_cost pentru a afla costul muchiei
            int ed_cost = edge_cost(edges, u, v, n);

            if (unexplored[v] && (cost[u] + ed_cost < cost[v]))
            {
                cost[v] = cost[u] + ed_cost;
                parent[v] = u;
            }
            ptr = ptr->next;
        }

        // pentru a iesi din while
        if (u == searched)
            break;
    }

    // afisam rezultatul
    printf("\nDrumul de cost minim de la nodul %d la nodul %d folosind Bellman-Ford: ", source, searched);
    fprintf(out_file, "\nDrumul de cost minim de la nodul %d la nodul %d folosind Bellman-Ford: ", source, searched);

    if (cost[searched] == INT_MAX)
    {
        printf(" nu exista drum\n");
        fprintf(out_file, " nu exista drum\n");
    }
    else
    {

        j = searched;
        while (j != source)
        {
            printf("%d <[%d]- ", j, edge_cost(edges, j, parent[j], n));
            fprintf(out_file, "%d <[%d]- ", j, edge_cost(edges, j, parent[j], n));
            j = parent[j];
        }
        printf("%d", source);
        fprintf(out_file, "%d", source);
        printf(" ; Cost: %d \n", cost[searched]);
        fprintf(out_file, " ; Cost: %d \n", cost[searched]);
    }
}

void dijkstra(struct graph *graph, struct edge *edges, int source, int searched, int n, FILE *out_file)
{

    int distance[N];
    int parent[N];
    int src, dest, cost;

    // Initilizam nodurile
    for (int i = 0; i < N; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    // Distanta de la sursa la sursa este 0
    distance[source] = 0;

    // actualizam distantele
    for (int i = 1; i <= N - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            src = edges[j].src;
            dest = edges[j].dest;
            cost = edges[j].cost;
            if (distance[src] != INT_MAX && distance[src] + cost < distance[dest])
            {
                distance[dest] = distance[src] + cost;
                parent[dest] = src;
            }
        }
    }

    // Verificam daca exista muchii negative pentru ca altfel algoritmul nu functioneaza
    for (int i = 0; i < n; i++)
    {
        src = edges[i].src;
        dest = edges[i].dest;
        cost = edges[i].cost;
        if (distance[src] != INT_MAX && distance[src] + cost < distance[dest])
        {
            printf("\nGraful contine muchii cu cost negativ.\n");
            fprintf(out_file, "\nGraful contine muchii cu cost negativ.\n");
            return;
        }
    }

    // Afisare rezultat
    printf("\nDrumul de cost minim de la nodul %d la nodul %d folosind Dijkstra: ", source, searched);
    fprintf(out_file, "\nDrumul de cost minim de la nodul %d la nodul %d folosind Dijkstra: ", source, searched);

    if (distance[searched] == INT_MAX)
    {
        printf("Niciun drum gasit.\n");
        fprintf(out_file, "Niciun drum gasit.\n");
        return;
    }

    for (int j = searched; j != -1; j = parent[j])
    {
        if (parent[j] != -1)
        {
            printf("%d <[%d]- ", j, edge_cost(edges, j, parent[j], n));
            fprintf(out_file, "%d <[%d]- ", j, edge_cost(edges, j, parent[j], n));
        }
        else
        {
            printf("%d", j);
            fprintf(out_file, "%d", j);
        }
    }
    printf(" ; Cost: %d \n", distance[searched]);
    fprintf(out_file, " ; Cost: %d \n", distance[searched]);
}

int main()
{
    FILE *graph_L7 = fopen("import_L7.csv", "r");
    FILE *graph_L8 = fopen("import_L8.csv", "r");
    FILE *out_L7 = fopen("export_L7.txt", "w");
    FILE *out_L8 = fopen("export_L8.txt", "w");
    // Citire muchii pentru graf7
    struct edge *edges7 = malloc(N * sizeof(struct edge));
    int count7 = read_import(graph_L7, &edges7);
    // Citire muchii pentru graf8
    struct edge *edges8 = malloc(N * sizeof(struct edge));
    int count8 = read_import(graph_L8, &edges8);
    // Creare grafuri
    struct graph *graph7 = create(edges7, count7);
    struct graph *graph8 = create(edges8, count8);
    // Afisare graf7
    printf("Lista de adiacenta a garfului din Laboratorul 7: \n");
    fprintf(out_L7, "Lista de adiacenta a garfului din Laboratorul 7: \n");
    print(graph7, edges7, count7);
    fprint(graph7, edges7, count7, out_L7);
    // Afisare graf8
    printf("Lista de adiacenta a garfului din Laboratorul 8: \n");
    fprintf(out_L8, "Lista de adiacenta a garfului din Laboratorul 8: \n");
    print(graph8, edges8, count8);
    fprint(graph8, edges8, count8, out_L8);

    dijkstra(graph7, edges7, 0, 11, count7, out_L7);
    dijkstra(graph8, edges8, 0, 7, count8, out_L8);

    bellmanford(graph7, edges7, 0, 11, count7, out_L7);
    bellmanford(graph8, edges8, 0, 7, count8, out_L8);

    fclose(graph_L7);
    fclose(graph_L8);
}