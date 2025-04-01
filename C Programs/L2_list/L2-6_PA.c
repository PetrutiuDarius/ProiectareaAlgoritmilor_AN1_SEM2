/*Inversați o listă înlănțuită folosind un algoritm recursiv și unul iterativ.*/
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
void reversei(struct node **head_ref)
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
void reverser(struct node **head_ref)
{
    struct node *current = *head_ref;
    struct node *rev = current->next;
    if (rev == NULL)
        return;
    reverser(&rev);
    current->next->next = current;
    current->next = NULL;
    *head_ref = rev;
}
int main()
{
    int data, key;
    printf("\nIntrodu datele si cheia: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("Setul %d de date: ", i + 1);
        scanf("%d", &data);
        printf("Cheia %d: ", i + 1);
        scanf("%d", &key);
        insert(key, data);
    }
    print();
    printf("\nLista inversata arata asa: ");
    reversei(&head);
    print();
    reverser(&head);
    print();
}