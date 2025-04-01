#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Pitesti

#define N 4
int const n = 4;

int front = 1, rear = 0;

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

struct vizitatori
{
    char nume[10];
    int timp_asteptare;
};

void enqueue(char v[][10], char x[])
{
    if (rear == n)
    {
        printf("\nQueue is full.");
        return;
    }
    rear = rear + 1;
    strcpy(v[rear], x);
}
void dequeue(char v[][10])
{
    if (rear == 0)
    {
        printf("\nQueue is empty.");
        return;
    }
    front = front + 1;
}

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

char *printname(int i)
{
    if (i == 0)
    {
        return "Muzeul Judetean Arges";
    }
    else if (i == 1)
    {
        return "Parcul Trivale";
    }
    else if (i == 2)
    {
        return "Arges Mall";
    }
    else if (i == 3)
    {
        return "Parcul Lunca Argesului";
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
void kruskal(struct edge edges[], int n)
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
    int z[4] = {0, 0, 0, 0}; // Pentru a identifica punctele de pornire
    printf("\n\tCel mai scurt drum dintre ele este asa: \n\n");
    for (int i = 0; i < nodecount; i++)
    {
        printf("%s -[Distanta: %d]> %s\n", printname(tree[i].src), tree[i].cost, printname(tree[i].dest));
        s += tree[i].cost;
        z[tree[i].src]++;
        z[tree[i].dest]++;
    }
    printf("\nDistanta totala este de %d km (Kruskal).", s);
    printf("\nAcum tu iti alegi ruta pe care vrei sa o urmezi, iar punctele de unde poti incepe sunt: ");
    for (int i = 0; i < nodecount; i++)
    {
        if (z[i] == 1)
        {
            printf(" %s , ", printname(i));
        }
    }
    printf("\b\b \b.\n");
}

int random_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void timp_asteptare(int atractie, struct vizitatori viz[])
{
    printf("\n\tV-ati pus la coada la %s in aceasta ordine: ", printname(atractie));
    int indice[n];
    for (int i = 0; i < n; i++)
    {
        indice[i] = i;
    }

    for (int i = n - 1; i > 0; i--)
    {
        int j = random_int(0, i);
        int temp = indice[i];
        indice[i] = indice[j];
        indice[j] = temp;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%s, ", viz[indice[i]].nume);
    }
    printf("\b\b \b.\n");
    int j = 70;
    printf("Ati stat la coada timp de: ", printname(atractie));
    for (int i = n - 1; i >= 0; i--)
    {
        j = random_int(1, j);
        printf("\n%s: %d minute \n", viz[indice[i]].nume, j);
        viz[indice[i]].timp_asteptare += j;
    }
}

int main()
{
    printf("\n\n\tBine ati venit la Pitesti! Aici avem 4 locatii turistice: \n\tMuzeul Judetean Arges\n\tParcul Trivale\n\tArges Mall\n\tParcul Lunca Argesului\n\n");
    struct edge edges[] =
        {
            {0, 1, 4},
            {0, 2, 6},
            {0, 3, 5},
            {1, 0, 4},
            {1, 2, 10},
            {1, 3, 8},
            {2, 0, 6},
            {2, 1, 10},
            {2, 3, 3},
            {3, 0, 5},
            {3, 1, 8},
            {3, 2, 3},
        };
    // char vizitatori[4][10] = {"Andrei", "Ion", "Mihai", "Marian"};
    struct vizitatori viz[] =
        {
            {"Andrei", 0},
            {"Ion", 0},
            {"Mihai", 0},
            {"Marian", 0},
        };
    int n = sizeof(edges) / sizeof(edges[0]);
    struct graph *graph = create(edges, n);
    kruskal(edges, n);
    timp_asteptare(0, viz);
    timp_asteptare(1, viz);
    timp_asteptare(2, viz);
    timp_asteptare(3, viz);
    printf("\n\n\tTimpul total de asteptare la coada pentru fiecare persoana este: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("%s: %d minute\n", viz[i].nume, viz[i].timp_asteptare);
    }
    return 0;
}