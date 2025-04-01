/*Se dă o listă de 10 alergători, fiecare având un timp de terminare al cursei diferit (ex: George 10.22, Ana 8.75). Să se sorteze lista după timp, iar la afișare în loc să apară timpul, trebuie sa fie locul pe care s-au clasat.*/
#include <stdio.h>
#include <stdlib.h>
struct alergatori
{
    char nume[20];
    float timp;
    struct alergatori *next;
};
struct alergatori *head = NULL;
void insert(char nume[], float timp)
{
    struct alergatori *link = (struct alergatori *)malloc(sizeof(struct alergatori));
    strcpy(link->nume, nume);
    link->timp = timp;
    link->next = head;
    head = link;
}
void print()
{
    struct alergatori *ptr = head;
    printf("\nParticipantii si timpii acestora: ");
    while (ptr != NULL)
    {
        printf("\n%s -> %.2f secunde", ptr->nume, ptr->timp);
        ptr = ptr->next;
    }
}
void sort()
{
    int i, j, k;
    char tempnume[50];
    float temptimp;
    struct alergatori *current;
    struct alergatori *next;
    int size = 10;
    k = size;
    for (i = 0; i < size - 1; i++, k--)
    {
        current = head;
        next = head->next;
        for (j = 1; j < k; j++)
        {
            if (next != NULL)
            {
                if (current->timp > next->timp)
                {
                    temptimp = current->timp;
                    current->timp = next->timp;
                    next->timp = temptimp;
                    strcpy(tempnume, current->nume);
                    strcpy(current->nume, next->nume);
                    strcpy(next->nume, tempnume);
                }
                current = current->next;
                next = next->next;
            }
        }
    }
}
void printpodium()
{
    int i = 1;
    struct alergatori *ptr = head;
    printf("\n\nClasamentul arata asa: ");
    while (ptr != NULL)
    {
        printf("\nPe locul %d se afla %s. ", i, ptr->nume);
        ptr = ptr->next;
        i++;
    }
}
int main()
{
    float v[10] = {10.5, 9.67, 11.25, 11.45, 10.85, 9.54, 9.98, 11.58, 12.50, 10.85};
    char n[10][50] = {"Daniel", "Mihai", "Cristina", "Darius", "Andrei", "George", "Ana", "Mihaela", "Bogdan", "Radu"};
    for (int i = 1; i < 10; i++)
        insert(n[i], v[i]);
    print();
    sort();
    printpodium();
}
