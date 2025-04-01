/*Combinați două liste înlănțuite într-una singură*/
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
void print(struct node *head_re)
{
    printf("[ ");
    while (head_re)
    {
        printf(" {%d,%d} ", head_re->key, head_re->data);
        head_re = head_re->next;
    }
    printf(" ]");
}
void insert(struct node **head_ref, int key, int data)
{
    struct node *link = (struct node *)malloc(sizeof(struct node));
    link->key = key;
    link->data = data;
    link->next = *head_ref;
    *head_ref = link;
}
struct node *merge(struct node *head1, struct node *head2)
{
    int d[100], k[100], i = 0;
    struct node *final = NULL;
    while (head1 != NULL)
    {
        d[i] = head1->data;
        k[i] = head1->key;
        head1 = head1->next;
        i++;
    }
    while (head2 != NULL)
    {
        d[i] = head2->data;
        k[i] = head2->key;
        head2 = head2->next;
        i++;
    }
    for (int j = 0; j < i; j++)
        insert(&final, k[j], d[j]);
    return final;
}
int main()
{
    int data, key;
    struct node *list1 = NULL;
    struct node *list2 = NULL;
    printf("\nIntrodu datele si cheia din prima lista: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("Setul %d de date: ", i + 1);
        scanf("%d", &data);
        printf("Cheia %d: ", i + 1);
        scanf("%d", &key);
        insert(&list1, key, data);
    }
    printf("\nIntrodu datele si cheia din a doua lista: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("Setul %d de date: ", i + 1);
        scanf("%d", &data);
        printf("Cheia %d: ", i + 1);
        scanf("%d", &key);
        insert(&list2, key, data);
    }
    printf("\nLista 1: ");
    print(list1);
    printf("\nLista 2: ");
    print(list2);
    printf("\nCele doua liste combinate: ");
    print(merge(list1, list2));
}