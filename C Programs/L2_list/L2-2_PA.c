/*Realizați o listă dublu înlănțuită, circulară, în care să căutați minimul și maximul*/
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
void insert(int data, int key)
{
    struct node *link = (struct node *)malloc(sizeof(struct node));

    link->data = data;
    link->key = key;
    if (head == NULL)
    {
        link->next = link;
        link->prev = link;
        head = link;
        last = link;
    }
    else
    {
        link->next = head;
        link->prev = last;
        last->next = link;
        head->prev = link;
        head = link;
    }
}
void print()
{
    struct node *ptr = head;
    printf("\n[ ");
    do
    {
        printf(" {%d,%d} ", ptr->key, ptr->data);
        ptr = ptr->next;
    } while (ptr != head);
    printf(" ]");
}
struct node *findmax()
{
    int maxim;
    struct node *current = head;
    maxim = current->data;
    if (head == NULL)
        return NULL;
    do
    {
        if (current->data > maxim)
            maxim = current->data;
        current = current->next;
    } while (current != head);
    do
    {
        current = current->next;
    } while (current->data != maxim);
    return current;
}
struct node *findmin()
{
    int minim;
    struct node *current = head;
    minim = current->data;
    if (head == NULL)
        return NULL;
    do
    {
        if (current->data < minim)
            minim = current->data;
        current = current->next;
    } while (current != head);
    do
    {
        current = current->next;
    } while (current->data != minim);
    return current;
}
int main()
{
    int data, key, m;
    printf("\nIntrodu datele si cheia: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("Setul %d de date: ", i + 1);
        scanf("%d", &data);
        printf("Cheia %d: ", i + 1);
        scanf("%d", &key);
        insert(data, key);
    }
    print();
    struct node *max = findmax();
    printf("\nSetul de date cu valoare maxima este %d de la cheia %d.", max->data, max->key);
    struct node *min = findmin();
    printf("\nSetul de date cu valoare minima este %d de la cheia %d.", min->data, min->key);
}