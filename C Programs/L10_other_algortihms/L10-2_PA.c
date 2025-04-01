#include <stdio.h>
#include <stdlib.h>

struct obiect
{
    int greutate;
    int valoare;
};

void afisare_obiecte(struct obiect obiecte[5], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Obiect %d: greutate: %d, valoare: %d\n", i + 1, obiecte[i].greutate, obiecte[i].valoare);
    }
}

void sort_valoare(struct obiect *obiecte, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (obiecte[i].valoare / obiecte[i].greutate < obiecte[i + 1].valoare / obiecte[i + 1].greutate)
        {
            struct obiect aux = obiecte[i];
            obiecte[i] = obiecte[i + 1];
            obiecte[i + 1] = aux;
        }
    }
}

void valoare_maxima(struct obiect obiecte[5], int n, int greutate_rucsac)
{
    int valoare_totala = 0;
    int x = greutate_rucsac;
    for (int i = 0; i < n; i++)
    {
        if (obiecte[i].greutate <= greutate_rucsac)
        {
            valoare_totala += obiecte[i].valoare;
            greutate_rucsac -= obiecte[i].greutate;
        }
    }
    printf("Valoare totala pe care rucsacul de %d kg o poate tine: %d\n", x, valoare_totala);
}

int main()
{
    int greutate_rucsac = 15;
    struct obiect obiecte[5] =
        {
            {12, 4},
            {1, 2},
            {2, 2},
            {1, 1},
            {4, 10}};
    sort_valoare(obiecte, 5);
    afisare_obiecte(obiecte, 5);
    valoare_maxima(obiecte, 5, greutate_rucsac);
}