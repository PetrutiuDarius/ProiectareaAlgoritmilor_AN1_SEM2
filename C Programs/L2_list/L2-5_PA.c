/*Realizați o listă dublu înlănțuită în care să căutați elementul de la mijloc și să îl ștergeți.*/
#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    int key;
    struct node *next;
    struct node *prev;
};
struct node *head = NULL;
struct node *last = NULL;
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
    if (head == NULL)
        last = link;
    else
        head->prev = link;
    link->next = head;
    head = link;
}
void deletemiddle()
{
    int k = 0;
    struct node *current = head;
    if (head == NULL)
        printf("Nu sunt date in lista.");
    while (current != NULL)
    {
        k++;
        current = current->next;
    }
    current = head;
    if (k % 2 == 0)
        printf("\nLista nu are un nod de mijloc.");
    else
    {
        for (int i = 0; i < k / 2; i++)
            current = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        printf("\nLista fara nodul din mijloc: ");
        print();
    }
}
int main()
{
    int data, key;
    printf("\nIntrodu datele si cheia: \n");
    for (int i = 0; i < 9; i++)
    {
        printf("Setul %d de date: ", i + 1);
        scanf("%d", &data);
        printf("Cheia %d: ", i + 1);
        scanf("%d", &key);
        insert(key, data);
    }
    print();
    deletemiddle();
}