/*Realizați un program care să șteargă duplicatele dintr-o listă simplu înlănțuită nesortată.*/
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
void deleteduplicates()
{
    int k;
    struct node *each = head;

    /*if (head == NULL)
        return NULL;*/
    while (each != NULL)
    {
        struct node *current = head;
        struct node *previous = NULL;
        k = each->data;
        while (current != NULL)
        {
            if (current->data == k && current != each)
            {
                if (current == head)
                {

                    head = head->next;
                    current = head;
                }
                else
                {

                    previous->next = current->next;
                    current = previous->next;
                }
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }
        each = each->next;
    }
}
int main()
{
    int data, key;
    printf("\nIntrodu datele si cheia: \n");
    for (int i = 0; i < 6; i++)
    {
        printf("Setul %d de date: ", i + 1);
        scanf("%d", &data);
        printf("Cheia %d: ", i + 1);
        scanf("%d", &key);
        insert(key, data);
    }
    print();
    deleteduplicates();
    printf("\nLista fara date duplicate este: ");
    print();
}