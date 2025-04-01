#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char *data;
    struct node *leftchild;
    struct node *rightchild;
};
struct node *root = NULL;

void insert(char *data)
{
    struct node *tempnode = (struct node *)malloc(sizeof(struct node));
    struct node *current;
    struct node *parent;

    // Allocate memory for the string data
    tempnode->data = (char *)malloc(strlen(data) + 1);
    strcpy(tempnode->data, data);

    tempnode->leftchild = NULL;
    tempnode->rightchild = NULL;

    if (root == NULL)
    {
        root = tempnode;
    }
    else
    {
        current = root;
        parent = NULL;
        while (1)
        {
            parent = current;
            if (strcmp(data, parent->data) < 0)
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

void inorderTraversal(struct node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->leftchild);
        if (strcmp(root->data, "lipie") != 0)
            printf("%s ", root->data);
        inorderTraversal(root->rightchild);
    }
}

void preordertraversal(struct node *root)
{
    if (root != NULL)
    {
        printf(" %s ", root->data);
        preordertraversal(root->leftchild);
        preordertraversal(root->rightchild);
    }
}

void postordertraversal(struct node *root)
{
    if (root != NULL)
    {
        postordertraversal(root->leftchild);
        postordertraversal(root->rightchild);
        if (strcmp(root->data, "lipie") != 0)
            printf(" %s ", root->data);
    }
}

void stergere(struct node *root, char tasta, char tasta_1)
{
    printf("Introduceti ingredientul pe care doriti sa il scoateti: ");
    char ingredient[20];
    scanf("%s", ingredient);
    struct node *current = root;
    struct node *parent = NULL;
    while (current != NULL)
    {
        if (strcmp(ingredient, current->data) == 0)
        {
            if (current->leftchild == NULL && current->rightchild == NULL)
            {
                if (parent == NULL)
                {
                    root = NULL;
                }
                else
                {
                    if (parent->leftchild == current)
                    {
                        parent->leftchild = NULL;
                    }
                    else
                    {
                        parent->rightchild = NULL;
                    }
                }
                free(current);
                break;
            }
            else if (current->leftchild == NULL)
            {
                if (parent == NULL)
                {
                    root = current->rightchild;
                }
                else
                {
                    if (parent->leftchild == current)
                    {
                        parent->leftchild = current->rightchild;
                    }
                    else
                    {
                        parent->rightchild = current->rightchild;
                    }
                }
                free(current);
                break;
            }
            else if (current->rightchild == NULL)
            {
                if (parent == NULL)
                {
                    root = current->leftchild;
                }
                else
                {
                    if (parent->leftchild == current)
                    {
                        parent->leftchild = current->leftchild;
                    }
                    else
                    {
                        parent->rightchild = current->leftchild;
                    }
                }
                free(current);
                break;
            }
            else
            {
                struct node *temp = current->rightchild;
                struct node *temp_parent = current;
                while (temp->leftchild != NULL)
                {
                    temp_parent = temp;
                    temp = temp->leftchild;
                }
                strcpy(current->data, temp->data);
                if (temp_parent->leftchild == temp)
                {
                    temp_parent->leftchild = temp->rightchild;
                }
                else
                {
                    temp_parent->rightchild = temp->rightchild;
                }
                free(temp);
                break;
            }
        }
        else if (strcmp(ingredient, current->data) < 0)
        {
            parent = current;
            current = current->leftchild;
        }
        else
        {
            parent = current;
            current = current->rightchild;
        }
    }
    printf("\nIncredientul %s a fost scos din shaorma comandata.\n", ingredient);
    printf("\nPoti vedea ingredientele ramase din shaorma: ");
    if (tasta_1 == '1')
        inorderTraversal(root);
    else if (tasta_1 == '2')
        preordertraversal(root);
    else if (tasta_1 == '3')
        postordertraversal(root);
}

int main()
{
    FILE *file = fopen("comenzi.txt", "w");
    insert("lipie");

    insert("pui");
    insert("vita");

    insert("cartofi");
    insert("orez");
    insert("salata");
    insert("rosii");

    insert("castraveti");
    insert("ardei");
    insert("ceapa");
    insert("usturoi");
    insert("masline");
    insert("branza");
    insert("sos");
    insert("jalapenos");

    int i = 0;
    do
    {

        fprintf(file, "Comanda %d: ", i + 1);
    menu:
        char tasta;
        char tasta_1;
        printf("\n\t\tBine ati venit la shaormeria noastra! \n ");
        printf("\n\t\tMeniu(tasteaza): \n ");
        printf("\n\t\t1. Shaorma in-order\n ");
        printf("\n\t\t2. Shaorma pre-order\n ");
        printf("\n\t\t3. Shaorma post-order\n ");
        printf("\n\t\tq. Iesire\n ");
        tasta_1 = getchar();
        getchar();
        if (tasta_1 == '1')
        {
            printf("ingrediente: ");
            printf(" lipie ");
            inorderTraversal(root);
            printf("\n");
            fprintf(file, "In-order: ");
        }
        else if (tasta_1 == '2')
        {
            printf("Ingrediente: ");
            preordertraversal(root);
            printf("\n");
            fprintf(file, "Pre-order: ");
        }
        else if (tasta_1 == '3')
        {
            printf("Ingresiente: ");
            printf(" lipie ");
            postordertraversal(root);
            printf("\n");
            fprintf(file, "Post-order: ");
        }
        else if (tasta_1 == 'q')
        {
            printf("Va multumim! \n");
            break;
        }
    stergere_ingredient:
        printf("\n\t\tDoriti sa scoateti un ingredient din shaorma? (y/n) ");
        tasta = getchar();
        printf("%c", tasta);
        getchar();
        if (tasta == 'y')
        {
            stergere(root, tasta, tasta_1);
            goto stergere_ingredient;
        }
        else if (tasta == 'n')
        {
            printf("Doriti si altceva?(y/n) \n");
            tasta = getchar();
            getchar();
            if (tasta == 'y')
            {
                goto menu;
            }
        }
        i++;

    } while (1);

    return 0;
}