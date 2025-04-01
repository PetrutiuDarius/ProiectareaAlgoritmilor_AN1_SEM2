/*Găsiți o pereche de numere într-un vector, care adunate să dea valoarea unui număr introdus de la tastatură. Utilizatorul poate să adauge numere de mai multe ori. Tratați și cazul în care nu găsește nimic.*/
#include <stdio.h>
void sum(int v[], int a, int n)
{
    int c, ok = 0;
    for (int i = 0; i < n && ok == 0; i++)
    {
        c = 0;
        if (v[i] <= a)
            c = a - v[i];
        for (int j = 0; j < n && ok == 0; j++)
            if (c == v[j] && j != i)
            {
                printf("Perechea este %d si %d. ", v[i], c);
                ok = 1;
            }
    }
    if (ok == 0 && a == 0)
        printf("La revedere!");
    else if (ok == 0)
        printf("Nu exista o asemenea pereche.");
}
int main()
{
    int v[50], n, a, b[50];
    printf("Introdu numarul de numere din vector: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Valoarea de pe pozitia %d : ", i + 1);
        scanf("%d", &v[i]);
    }
    printf("Vectorul: ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    while (a != 0)
    {
        printf("\nIntrodu numarul(0 pentru a iesi): ");
        scanf("%d", &a);
        sum(v, a, n);
    }
}
