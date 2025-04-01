#include <stdio.h>
#include <string.h>
struct student
{
    char nume[20];
    char prenume[50];
    char oras[50];
    char liceu[50];
    char hobby[4][20];
};
void ordonare(struct student s1)
{
    int i, j;
    char k[20];
    for (i = 0; i < 4; i++)
        for (j = i + 1; j < 4; j++)
            if (strcmp(s1.hobby[i], s1.hobby[j]) > 0)
            {
                strcpy(k, s1.hobby[i]);
                strcpy(s1.hobby[i], s1.hobby[j]);
                strcpy(s1.hobby[j], k);
            }
    printf("\nHobby-urile in ordine alfabetica: ");
    for (int i = 0; i < 3; i++)
        printf(" %s,", s1.hobby[i]);
    printf(" %s .\n", s1.hobby[3]);
}
void afisare(struct student s1)
{
    printf("\nNume: %s ;\n", s1.nume);
    printf("Prenume: %s ;\n", s1.prenume);
    printf("Oras: %s ;\n", s1.oras);
    printf("Liceu: %s ;\n", s1.liceu);
    printf("Hobby-uri: ");
    for (int i = 0; i < 3; i++)
        printf(" %s,", s1.hobby[i]);
    printf(" %s .\n", s1.hobby[3]);
}

int main()
{
    int i;
    struct student s1 = {"Petrutiu", "Darius-Simion", "Pitesti", "Colegiul National \"Ion C. Bratianu\"", "Masini", "Detailing Auto", "Drumetii", "Citit"};

    afisare(s1);
    ordonare(s1);
    return 0;
}