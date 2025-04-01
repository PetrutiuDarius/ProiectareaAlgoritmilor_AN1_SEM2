#include <stdio.h>
#include <stdlib.h>

void print_sudoku(int v[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        if(i==0 || i%3==0)
        {
            printf("______________________\n");
        }
        for (int j = 0; j < 9; j++)
        {
            if(j==0 || j%3==0)
            {
                printf("|");
            }
            if(v[i][j] == 0)
            {
                printf("* ");
            }
            else
            {
                printf("%d ", v[i][j]);
            }
            if(j==8)
            {
                printf("|");
            }
        }
        if(i==8)
        {
            printf("\n______________________\n");
        }
        printf("\n");
    }
}

int unassigned(int v[9][9],int *i,int *j)
{
    for(*i=0;*i<9;(*i)++)
    {
        for(*j=0;*j<9;(*j)++)
        {
            if(v[*i][*j]==0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int is_safe(int v[9][9],int a,int i,int j)
{
    for(int k=0;k<9;k++)
    {
        if(v[i][k]==a || v[k][j]==a)
        {
            return 0;
        }
    }
    int x=(i/3)*3;
    int y=(j/3)*3;
    for(int k=x;k<x+3;k++)
    {
        for(int b=y;b<y+3;b++)
        {
            if(v[k][b]==a)
            {
                return 0;
            }
        }
    }
    return 1;
}

int solve_sudoku(int v[9][9])
{
    int i,j;
    if(!unassigned(v,&i,&j))
    {
        return 1;
    }
    for(int a=1;a<=9;a++)
    {
        if(is_safe(v,a,i,j))
        {
            v[i][j]=a;
            if(solve_sudoku(v))
            {
                return 1;
            }
            v[i][j]=0;
        }
    }
    return 0;
}

int main()
{
    int v[9][9] = {0, 0, 0, 0, 0, 0, 0, 0, 8,
                   1, 8, 0, 0, 0, 2, 3, 0, 0,
                   0, 6, 0, 0, 5, 7, 0, 0, 1,
                   0, 7, 0, 9, 6, 0, 0, 0, 0,
                   0, 9, 0, 7, 0, 4, 0, 1, 0,
                   0, 0, 0, 0, 8, 1, 0, 4, 0,
                   6, 0, 0, 2, 4, 0, 0, 8, 0,
                   0, 0, 4, 5, 0, 0, 0, 9, 3,
                   5, 0, 0, 0, 0, 0, 0, 0, 0};
    printf("Aceasta este forma initiala a Sudoku-lui:\n");
    print_sudoku(v);
    if (solve_sudoku(v))
    {
        printf("Aceasta este forma finala a Sudoku-lui:\n");
        print_sudoku(v); 
    }
    else
    {
        printf("Nu exista solutie pentru Sudoku-ul dat.\n");
    }
         
}