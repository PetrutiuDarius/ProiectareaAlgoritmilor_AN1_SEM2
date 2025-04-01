#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_KEY_LEN 20
#define MAX_EXPL_LEN 200

struct dictionary
{
    char key[MAX_KEY_LEN];
    char explanation[MAX_EXPL_LEN];
};

int hash(char key[], int size)
{
    int sum = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        sum += key[i];
    }
    return sum % size;
}

void cautare(struct dictionary word[], char key[], int hash_table[])
{
    while (1)
    {
        printf("\nPentru a iesi in meniul principal scrieti cuvantul exit.\n");
        printf("Introduceti cuvantul pe care doriti sa il cautati: ");
        scanf("%s", key);
        if (strcmp(key, "exit") == 0)
        {
            break;
        }
        int index = hash(key, MAX_SIZE);
        if (hash_table[index] == -1)
        {
            printf("Cuvantul %s nu a fost gasit in dictionar.\n", key);
        }
        else
        {
            printf(" %s : %s\n", word[hash_table[index]].key, word[hash_table[index]].explanation);
        }
    }
    system("cls");
}

void adaugare_manuala(struct dictionary word[], int *n, int hash_table[], char key[], char explanation[])
{
    strcpy(word[*n].key, key);
    strcpy(word[*n].explanation, explanation);
    int index = hash(word[*n].key, MAX_SIZE);
    hash_table[index] = *n;
    (*n)++;
}

void adaugare(struct dictionary word[], int *n, int hash_table[])
{
    printf("Introduceti cuvantul pe care doriti sa il adaugati: ");
    scanf("%s", word[*n].key);
    printf("Introduceti explicatia cuvantului: ");
    scanf("%s", word[*n].explanation);
    int index = hash(word[*n].key, MAX_SIZE);
    hash_table[index] = *n;
    (*n)++;
}

void stergere(struct dictionary word[], int *n, int hash_table[], char key[])
{
    printf("Introduceti cuvantul pe care doriti sa il stergeti: ");
    scanf("%s", key);
    int index = hash(key, MAX_SIZE);
    if (hash_table[index] == -1)
    {
        printf("Cuvantul %s nu a fost gasit in dictionar.\n", key);
        stergere(word, n, hash_table, key);
    }
    else
    {
        hash_table[index] = -1;
        (*n)--;
    }
}

int main()
{
    int hash_table[MAX_SIZE];
    int n = 0;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        hash_table[i] = -1;
    }

    struct dictionary word[MAX_SIZE];

    adaugare_manuala(word, &n, hash_table, "bios", "software-ul de baza al unui calculator, care controleaza in mod direct modul in care functioneaza componentele hardware.");
    adaugare_manuala(word, &n, hash_table, "cpu", "unitatea centrala de procesare, este un microprocesor care executa instructiunile unui program de calculator.");
    adaugare_manuala(word, &n, hash_table, "ram", "memoria RAM este un tip de memorie volatila care stocheaza datele si programele pe care le utilizeaza calculatorul in timp real.");
    adaugare_manuala(word, &n, hash_table, "rom", "memoria ROM este un tip de memorie nevolatila care stocheaza datele si programele pe care le utilizeaza calculatorul in timp real.");
    adaugare_manuala(word, &n, hash_table, "gpu", "unitatea de procesare grafica, este un microprocesor care executa instructiunile unui program de calculator.");
    adaugare_manuala(word, &n, hash_table, "bit", "unitatea de baza pentru cantitatea de informatie in comunicatii digitale; poate avea doar una din doua valori (0 si 1) si prin urmare poate fi pus in aplicare fizic de catre un dispozitiv care poate avea doar doua stari.");
    adaugare_manuala(word, &n, hash_table, "byte", "unitate de informatie care reprezinta o succesiune de opt biti si care constituie cea mai mica unitate de memorie adresabila; sinonim: octet.");
    adaugare_manuala(word, &n, hash_table, "hdd", "un dispozitiv de stocare a datelor care utilizeaza un disc magnetic rotativ pentru a stoca datele.");

    char key[MAX_KEY_LEN];
    char tasta;
    do
    {
        printf("\n\t\tBine ati venit la dictionaurul de la PA!\n\n");
        printf("\tIn dictionar sunt %d cuvinte.\n\n", n);
        printf("\tPentru cautarea unui cuvant apasati tasta f.\n");
        printf("\tPentru a adauga un cuvant apasati tasta a.\n");
        printf("\tPentru a sterge un cuvant apasati tasta d.\n");
        printf("\tPentru iesirea din program apasati tasta q.\n");
        tasta = getchar();
        if (tasta == 'f')
        {
            if (n == 0)
            {
                printf("Dictionarul este gol.\n");
                continue;
            }
            cautare(word, key, hash_table);
        }
        else if (tasta == 'a')
        {
            adaugare(word, &n, hash_table);
        }
        else if (tasta == 'd')
        {
            if (n == 0)
            {
                printf("Dictionarul este gol.\n");
                continue;
            }
            stergere(word, &n, hash_table, key);
        }
        system("cls");
    } while (tasta != 'q');
    return 0;
}
