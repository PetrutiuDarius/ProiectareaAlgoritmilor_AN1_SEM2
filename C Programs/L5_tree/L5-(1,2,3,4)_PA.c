#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *leftchild;
    struct node *rightchild;
};
struct node *root = NULL;
void insert(int data)
{
    struct node *tempnode = (struct node *)malloc(sizeof(struct node));
    struct node *current;
    struct node *parent;
    tempnode->data = data;
    tempnode->leftchild = NULL;
    tempnode->rightchild = NULL;
    if (root == NULL)
        root = tempnode;
    else
    {
        current = root;
        parent = NULL;
        while (1)
        {
            parent = current;
            if (data < parent->data)
            {
                current = current->leftchild;
                if (current == NULL)
                {
                    parent->leftchild = tempnode;
                    return;
                }
            }
            else
            {
                current = current->rightchild;
                if (current == NULL)
                {
                    parent->rightchild = tempnode;
                    return;
                }
            }
        }
    }
}
/*Exercitiul 1*/
void inordertraversal(struct node *Node)
{
    if (Node != NULL)
    {
        inordertraversal(Node->leftchild);
        printf(" %d ", Node->data);
        inordertraversal(Node->rightchild);
    }
}
void preordertraversal(struct node *Node)
{
    if (Node != NULL)
    {
        printf(" %d ", Node->data);
        preordertraversal(Node->leftchild);
        preordertraversal(Node->rightchild);
    }
}
void postordertraversal(struct node *Node)
{
    if (Node != NULL)
    {
        postordertraversal(Node->leftchild);
        postordertraversal(Node->rightchild);
        printf(" %d ", Node->data);
    }
}
/*Exercitiul 2*/
void mirrortree(struct node *Node)
{
    if (Node != NULL)
    {
        mirrortree(Node->rightchild);
        printf(" %d ", Node->data);
        mirrortree(Node->leftchild);
    }
}
/*Exercitiul 3*/
int suma(struct node *Node, int s)
{
    if (Node != NULL)
    {
        s += Node->data;
        s = suma(Node->leftchild, s);
        s = suma(Node->rightchild, s);
    }
    return s;
}
/*Exercitiul 4*/
int adancime(struct node *Node, int i, int *n)
{
    if (Node != NULL)
    {
        i++;
        *n = adancime(Node->leftchild, i, n);
        *n = adancime(Node->rightchild, i, n);
        i--;
    }
    else
    {
        if (i > *n)
            *n = i;
    }
    return *n;
}
int main()
{
    int v[10] = {8, 5, 11, 2, 7, 9, 14, 1, 6, 13};
    for (int i = 0; i < 10; i++)
        insert(v[i]);
    /*Exercitiul 1*/
    printf("\nArborele afisat folosind In Order: ");
    inordertraversal(root);
    printf("\nArborele afisat folosind Pre Order: ");
    preordertraversal(root);
    printf("\nArborele afisat folosind Post Order: ");
    postordertraversal(root);
    /*Exercitiul 2*/
    printf("\nArborele afisat in oglinda folosind In Order: ");
    mirrortree(root);
    /*Exercitiul 3*/
    int s = suma(root, 0);
    printf("\nSuma valorilor din arbore este: %d", s);
    /*Exercitiul 4*/
    int n = 0;
    n = adancime(root, 0, &n);
    printf("\nAdancimea arborelui este de %d.", n);
}