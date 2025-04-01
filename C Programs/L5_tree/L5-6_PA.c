/*Implementați o funcție prin care să verificați că un binary tree este binary search tree.*/
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
void inordertraversal(struct node *Node)
{
    if (Node != NULL)
    {
        inordertraversal(Node->leftchild);
        printf(" %d ", Node->data);
        inordertraversal(Node->rightchild);
    }
}
int search(struct node *Node)
{
}
int main()
{
    int v[10] = {8, 5, 11, 2, 7, 9, 14, 1, 6, 13};
    for (int i = 0; i < 10; i++)
        insert(v[i]);
    inordertraversal(root);
}