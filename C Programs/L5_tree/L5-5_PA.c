/*Implementați o funcție ca să verificați că un binary tree este echilibrat (doi subarbori ai oricărui nod nu au o diferență de nivel mai mare de 1). */
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
void preordertraversal(struct node *Node)
{
    if (Node != NULL)
    {
        printf(" %d ", Node->data);
        preordertraversal(Node->leftchild);
        preordertraversal(Node->rightchild);
    }
}
int adancime(struct node *Node)
{
    if (Node == NULL)
        return 0;

    int l = adancime(Node->leftchild);
    int r = adancime(Node->rightchild);

    return 1 + (l > r ? l : r);
}
int echilibrat(struct node *Node)
{
    if (Node == NULL)
        return 1;
    int l = adancime(Node->leftchild);
    int r = adancime(Node->rightchild);
    if (abs(l - r) <= 1 && echilibrat(Node->leftchild) && echilibrat(Node->rightchild))
        return 1;
    return 0;
}
int main()
{
    int n = 0;
    int v[10] = {8, 5, 11, 2, 7, 9, 14, 1, 6, 13};
    for (int i = 0; i < 10; i++)
        insert(v[i]);
    preordertraversal(root);
    if (echilibrat(root) == 1)
        printf("\nArborele este echilibrat.");
    else
        printf("Arborele nu este echilibrat.");
}