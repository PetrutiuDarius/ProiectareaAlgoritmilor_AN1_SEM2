/*Realizați un algoritm care să verifice că o listă simplu înlănțuită este palindrom*/
#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    int key;
    struct node *next;
};
struct node *head = NULL;
struct node *current = NULL;
void print()
{
    struct node *ptr = head;
    printf("\n[ ");
    while (ptr != NULL)
    {
        printf(" {%d,%d} ", ptr->key, ptr->data);
        ptr = ptr->next;
    }
    printf(" ]");
}
void insert(int key, int data)
{
    struct node *link = (struct node *)malloc(sizeof(struct node));
    link->key = key;
    link->data = data;
    link->next = head;
    head = link;
}
void palindrom()
{
    int v[100], i = 0, k = 0;
    struct node *current = head;
    struct node *previous = NULL;
    if (head == NULL)
        printf("Nu sunt date in lista.");
    while (current != NULL)
    {
        v[i] = current->data;
        current = current->next;
        i++;
    }
    int d = i - 1;
    for (int j = 0; j <= i / 2; j++, d--)
    {
        if (v[j] == v[d])
            k = 1;
        else
            k = 0;
    }
    if (k == 1)
        printf("\nLista formeaza un palindrom.");
    else
        printf("\nLista nu formeaza un palindrom.");
}
int main()
{
    int data, key;
    printf("\nIntrodu datele si cheia: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("Setul %d de date: ", i + 1);
        scanf("%d", &data);
        printf("Cheia %d: ", i + 1);
        scanf("%d", &key);
        insert(key, data);
    }
    print();
    palindrom();
}