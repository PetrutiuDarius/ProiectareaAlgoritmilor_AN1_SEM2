#include <stdio.h>
#include <stdlib.h>
struct node
{
    int age;
    char gender[10];
    char marital_status[20];
    char occupation[20];
    char education[20];
    int years_of_experience;
    int zip_code;
    struct node *next;
    struct node *prev;
};
struct node *head = NULL;
struct node *tail = NULL;
struct node *createNode(int age, const char *gender, const char *marital_status,
                        const char *occupation, const char *education,
                        int years_of_experience, int zip_code)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->age = age;
    strcpy(newNode->gender, gender);
    strcpy(newNode->marital_status, marital_status);
    strcpy(newNode->occupation, occupation);
    strcpy(newNode->education, education);
    newNode->years_of_experience = years_of_experience;
    newNode->zip_code = zip_code;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void insertAtEnd(struct node **head, struct node **tail, struct node *newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}
void gender(struct node *head)
{
    int m = 0;
    int f = 0;

    struct node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->gender, "Male") == 0)
        {
            m++;
        }
        else if (strcmp(current->gender, "Female") == 0)
        {
            f++;
        }
        current = current->next;
    }

    printf("Number of male users: %d\n", m);
    printf("Number of female users: %d\n", f);
}
void occupation(struct node *head)
{
    int s = 0;
    int p = 0;
    int g = 0;
    struct node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->occupation, "Student") == 0)
        {
            s++;
        }
        else if (strcmp(current->occupation, "Post Graduate") == 0)
        {
            p++;
        }
        else if (strcmp(current->occupation, "Graduate") == 0)
        {
            g++;
        }
        current = current->next;
    }
    printf("Number of students: %d\n", s);
    printf("Number of post graduates: %d\n", p);
    printf("Number of graduates: %d\n", g);
}
void education(struct node *head)
{

    int p = 0;
    int g = 0;
    struct node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->education, "Post Graduate") == 0)
        {
            p++;
        }
        else if (strcmp(current->education, "Graduate") == 0)
        {
            g++;
        }
        current = current->next;
    }
    printf("Number of post graduates: %d\n", p);
    printf("Number of graduates: %d\n", g);
}
void swapNodes(struct node *a, struct node *b)
{
    int tempAge = a->age;
    a->age = b->age;
    b->age = tempAge;

    char tempGender[10];
    strcpy(tempGender, a->gender);
    strcpy(a->gender, b->gender);
    strcpy(b->gender, tempGender);

    char tempMaritalStatus[10];
    strcpy(tempMaritalStatus, a->marital_status);
    strcpy(a->marital_status, b->marital_status);
    strcpy(b->marital_status, tempMaritalStatus);

    char tempOccupation[20];
    strcpy(tempOccupation, a->occupation);
    strcpy(a->occupation, b->occupation);
    strcpy(b->occupation, tempOccupation);

    char tempEducation[20];
    strcpy(tempEducation, a->education);
    strcpy(a->education, b->education);
    strcpy(b->education, tempEducation);

    int tempFamilySize = a->familyize;
    a->familySize = b->familySize;
    b->familySize = tempFamilySize;

    int tempPinCode = a->pinCode;
    a->pinCode = b->pinCode;
    b->pinCode = tempPinCode;
}
void sortListByPinCode(struct node *head)
{
    struct node *current;
    struct node *tail = NULL;
    int swapped;

    // Verifica daca lista este goala
    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        current = head;

        while (current->next != tail)
        {
            // Compara codurile PIN ale nodurilor curente si urmatoare
            if (current->pinCode > current->next->pinCode)
            {
                // Schimba nodurile
                swapNodes(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        // Seteaza coada catre ultimul nod sortat
        tail = current;
    } while (swapped);
}
int main()
{
    FILE *file = fopen("foods.csv", "r");
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        int age, years_of_experience, zip_code;
        char gender[10], marital_status[20], occupation[20], education[20];
        sscanf(line, "%d,%9[^,],%19[^,],%19[^,],%19[^,],%d,%d", &age, gender, marital_status,
               occupation, education, &years_of_experience, &zip_code);
        struct node *newNode = createNode(age, gender, marital_status, occupation,
                                          education, years_of_experience, zip_code);
        insertAtEnd(&head, &tail, newNode);
    }
    fclose(file);
    gender(head);
    occupation(head);
    education(head);
}