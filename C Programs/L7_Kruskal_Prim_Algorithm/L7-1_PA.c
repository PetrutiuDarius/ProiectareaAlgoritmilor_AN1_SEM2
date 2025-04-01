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
void swap(struct edge *a, struct edge *b)
{
    struct edge temp = *a;
    *a = *b;
    *b = temp;
}
int find(int parent[], int i)
{
    // aceasta functie returneaza nodul de plecare, in caz ca exista a unui nod pe care vrem sa il introducem in arbore
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}
void kruskal(struct edge edges[], int n, FILE *out_file)
{
    int s = 0;
    // Sortarea muchiilor
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (edges[j].cost > edges[j + 1].cost)
            {
                swap(&edges[j], &edges[j + 1]);
            }
        }
    }
    // Definirea unui arbore
    struct edge tree[N];
    int nodecount = 0;
    int parent[N];
    // Initializam fiecare parinte cu -1 pentru inceput, acest parinte ne ajuta la identificarea daca arborele se transforma in graf
    for (int i = 0; i < N; i++)
    {
        parent[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int srcParent = find(parent, edges[i].src);
        int destParent = find(parent, edges[i].dest);
        // aici verificam daca parintii celor doua noduri sunt aceiasi, ceea ce va insemna ca se formeaza o bucla in arbore si nu e bine
        if (srcParent != destParent)
        {
            tree[nodecount++] = edges[i];
            parent[srcParent] = destParent;
        }
    }
    printf("Arborele de cost minim folosind algoritmul Kruskal:\n");
    fprintf(out_file, "Arborele de cost minim folosind algoritmul Kruskal:\n");
    for (int i = 0; i < nodecount; i++)
    {
        printf("(%d -[%d]> %d)\n", tree[i].src, tree[i].cost, tree[i].dest);
        fprintf(out_file, "%d, %d, %d(cost),\n", tree[i].src, tree[i].cost, tree[i].dest);
        s += tree[i].cost;
    }
    printf("Costul total este de %d (Kruskal).", s);
    fprintf(out_file, "Costul total este de %d (Kruskal).\n", s);
}
void prim(struct graph *graph, struct edge edges[], int n, int startvertex, FILE *out_file)
{
    struct edge tree[N];
    int nodecount = 0, s = 0;
    int visited[N];
    for (int i = 0; i < N; i++)
    {
        visited[i] = 0;
    }
    // Lista de prioritati pentru a vedea costul minim al mai multor muchii
    struct edge priorityqueue[N];
    int pqsize = 0;
    visited[startvertex] = 1;
    for (int i = 0; i < n; i++)
    {
        if ((edges[i].src == startvertex && !visited[edges[i].dest]) || (edges[i].dest == startvertex && !visited[edges[i].src]))
        {
            priorityqueue[pqsize++] = edges[i];
        }
    }
    while (nodecount < N - 1 && pqsize > 0)
    {
        int mincost = INT_MAX;
        int minindex = -1;
        // acum aflam muchia cu costul cel mai mic din lista
        for (int i = 0; i < pqsize; i++)
        {
            if (priorityqueue[i].cost < mincost && !visited[priorityqueue[i].dest])
            {
                mincost = priorityqueue[i].cost;
                minindex = i;
            }
        }
        // va iesi din for daca nu gaseste o muchie
        if (minindex == -1)
        {
            break;
        }
        // adaugam muchia in arbore
        tree[nodecount++] = priorityqueue[minindex];
        visited[priorityqueue[minindex].dest] = 1;
        // stergem muchia din lista
        for (int i = minindex; i < pqsize - 1; i++)
        {
            priorityqueue[i] = priorityqueue[i + 1];
        }
        pqsize--;
        // adaugam in lista noile muchii
        for (int i = 0; i < n; i++)
        {
            if ((edges[i].src == tree[nodecount - 1].dest && !visited[edges[i].dest]) || (edges[i].dest == tree[nodecount - 1].src && !visited[edges[i].dest]))
            {
                priorityqueue[pqsize++] = edges[i];
            }
        }
    }
    printf("\nArborele de cost minim folosind algoritmul Prim:\n");
    fprintf(out_file, "Arborele de cost minim folosind algoritmul Prim:\n");
    for (int i = 0; i < nodecount; i++)
    {
        printf("(%d -[%d]> %d)\n", tree[i].src, tree[i].cost, tree[i].dest);
        fprintf(out_file, "%d, %d, %d(cost),\n", tree[i].src, tree[i].cost, tree[i].dest);
        s += tree[i].cost;
    }
    printf("Costul total este de %d (Prim).", s);
    fprintf(out_file, "Costul total este de %d (Prim).\n", s);
}
int main()
{
    FILE *in_file;
    FILE *out_file_kruskal;
    FILE *out_file_prim;
    FILE *analiza;
    in_file = fopen("import.csv", "r");
    out_file_kruskal = fopen("export_kruskal.csv", "w");
    out_file_prim = fopen("export_prim.csv", "w");
    analiza = fopen("analiza.txt", "w");
    char line[100];
    int count = 0;
    int a = N;
    struct edge *edges = malloc(a * sizeof(struct edge));
    while (fgets(line, sizeof(line), in_file) != NULL)
    {
        char *token = strtok(line, ",");
        if (token != NULL)
        {
            edges[count].src = atoi(token);
            token = strtok(NULL, ",");
            if (token != NULL)
            {
                edges[count].dest = atoi(token);
                token = strtok(NULL, ",");
                if (token != NULL)
                {
                    edges[count].cost = atoi(token);
                    count++;
                    edges[count].src = edges[count - 1].dest;
                    edges[count].dest = edges[count - 1].src;
                    edges[count].cost = edges[count - 1].cost;
                    count++;
                    if (count >= N)
                    {
                        a *= 2;
                        edges = realloc(edges, a * sizeof(struct edge));
                    }
                }
            }
        }
    }
    struct graph *graph = create(edges, count);
    printf("Lista de adiacenta a garfului: \n");
    print(graph, edges, count);
    fclose(in_file);
    kruskal(edges, count, out_file_kruskal);
    prim(graph, edges, count, 0, out_file_prim);
    fprintf(analiza, "Algoritmul Kruskal se bazeaza pe sortarea muchiilor în ordine crescătoare a costului, aspect evident în bucla dublă care parcurge muchiile și le sortează. Acest lucru sugerează o atenție deosebită acordată prioritizării costului în alegerea muchiilor pentru arborele minim.\nPe de altă parte, algoritmul Prim incepe de la un nod de pornire și adauga în mod gradual muchiile în arborele minim. Acest lucru este evident în modul în care se explorează prioritățile pentru fiecare nod, selectând cea mai ieftină muchie către un nod nevizitat, după cum sugerează parcurgerea listei de priorități.\n");
    fprintf(analiza, "Beneficiile și problematicile:\nImplementarea algoritmului Kruskal este notabilă pentru simplitatea sa și eficiența în tratarea grafurilor dense. Pe de altă parte, algoritmul Prim, deși poate fi mai eficient pentru grafuri rare sau mici, poate necesita o implementare mai elaborată și poate fi mai sensibil la selecția nodului de pornire.");
    return 0;
}