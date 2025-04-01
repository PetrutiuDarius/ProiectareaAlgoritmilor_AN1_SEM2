/*Creați o listă simplu înlănțuită cu 10 elemente la care să realizați următoarele operații:
creare,inserare,stergere,cautare,sortare,reverse*/
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
struct node *delete(int key)
{
    struct node *current = head;
    struct node *previous = NULL;
    if (head == NULL)
        return NULL;
    while (current->key != key)
    {
        if (current->next == NULL)
            return NULL;
        else
        {
            previous = current;
            current = current->next;
        }
    }
    if (current == head)
        head = head->next;
    else
        previous->next = current->next;
    return current;
}
struct node *find(int key)
{
    struct node *current = head;
    if (head == NULL)
        return NULL;
    while (current->key != key)
    {
        if (current->next == NULL)
            return NULL;
        else
            current = current->next;
    }
    return current;
}
void sort()
{
    int i, j, k, tempKey, tempData;
    struct node *current;
    struct node *next;
    int size = 10;
    k = size;
    for (i = 0; i < size - 1; i++, k--)
    {
        current = head;
        next = head->next;
        for (j = 1; j < k; j++)
        {
            if (current->data > next->data)
            {
                tempData = current->data;
                current->data = next->data;
                next->data = tempData;
                tempKey = current->key;
                current->key = next->key;
                next->key = tempKey;
            }
            current = current->next;
            next = next->next;
        }
    }
}
void reverse(struct node **head_ref)
{
    struct node *prev = NULL;
    struct node *current = *head_ref;
    struct node *next;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
int main()
{
    int data, key;
    printf("\nIntrodu datele si cheia: \n");
    for (int i = 0; i < 10; i++)
    {
        printf("Setul %d de date: ", i + 1);
        scanf("%d", &data);
        printf("Cheia %d: ", i + 1);
        scanf("%d", &key);
        insert(key, data);
    }
    print();
    printf("\nLista cu datele in ordine arata asa: ");
    sort();
    print();
    printf("\nLista inversata arata asa: ");
    reverse(&head);
    print();
    printf("\nAlege ce set de date vrei sa stergi introducand cheia: ");
    scanf("%d", &key);
    struct node *del = delete (key);
    if (del == NULL)
        printf("Nu exista aceasta cheie.");
    else
        printf("Ati sters setul de date %d de la cheia %d. \n", del->data, del->key);
    printf("\nIntrodu o cheie de la care sa gasesti datele: ");
    scanf("%d", &key);
    struct node *result = find(key);
    if (result == NULL)
        printf("Nu exista aceasta cheie.");
    else
        printf("Ati cautat setul de date %d prin cheia %d. ", result->data, result->key);
    print();
    return 0;
}