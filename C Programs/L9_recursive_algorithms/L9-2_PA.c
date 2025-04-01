#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void hanoi_recursiv(int n, const char *src, const char *dest, const char *aux)
{
    if (n == 1)
    {
        printf("Mutare disc %d de la %s la %s\n", n, src, dest);
        return;
    }

    hanoi_recursiv(n - 1, src, aux, dest);
    printf("Mutare disc %d de la %s la %s\n", n, src, dest);
    hanoi_recursiv(n - 1, aux, dest, src);
}

void hanoi_programare_dinamica(int n)
{
    int total_moves = pow(2, n) - 1; // numarul total de mutari necesare pentru n discuri este 2^n - 1
    char rods[3][10] = {"sursa", "auxiliar", "destinatie"};

    // pentru n par, interschimbam stivele 2 si 3
    if (n % 2 == 0)
    {
        char temp[10];
        strcpy(temp, rods[1]);
        strcpy(rods[1], rods[2]);
        strcpy(rods[2], temp);
    }

    // pentru fiecare mutare, calculam de unde si unde trebuie sa mutam discul
    for (int i = 1; i <= total_moves; i++)
    {
        int from = (i & i - 1) % 3;     // se calculeaza de unde trebuie sa mutam discul
        int to = ((i | i - 1) + 1) % 3; // se calculeaza unde trebuie sa mutam discul
        printf("Mutare disc de la %s la %s  \n", rods[from], rods[to]);
    }
}
int main()
{
    int n;
    printf("Cate discuri sa aiba turnul lui Hanoi: ");
    scanf("%d", &n);
    printf("\nTurnul lui Hanoi cu programare recursiva:\n");
    hanoi_recursiv(n, "sursa", "destinatie", "auxiliar");
    printf("\nTurnul lui Hanoi cu programare dinamica:\n");
    hanoi_programare_dinamica(n);
}