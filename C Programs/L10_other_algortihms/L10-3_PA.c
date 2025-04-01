#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <string.h>

#define ROW 5
#define COL 6

typedef struct
{
    int first;
    int second;
} Pair;

typedef struct
{
    double first;
    Pair second;
} qPair;

typedef struct
{
    int parent_i, parent_j;
    double f, g, h;
} cell;

typedef struct
{
    int top;
    Pair array[ROW * COL];
} Stack;

void push(Stack *stack, Pair item)
{
    stack->array[++stack->top] = item;
}

Pair pop(Stack *stack)
{
    return stack->array[stack->top--];
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

bool isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col)
{
    return grid[row][col] == 1;
}

bool isDestination(int row, int col, Pair dest)
{
    return row == dest.first && col == dest.second;
}

double calculateHValue(int row, int col, Pair dest)
{
    return ((double)sqrt(
        (row - dest.first) * (row - dest.first) +
        (col - dest.second) * (col - dest.second)));
}

void tracePath(cell cellDetails[][COL], Pair dest)
{
    printf("\nDrumul este: ");
    int row = dest.first;
    int col = dest.second;

    Stack Path;
    Path.top = -1;

    while (!(cellDetails[row][col].parent_i == row &&
             cellDetails[row][col].parent_j == col))
    {
        push(&Path, (Pair){row, col});
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    push(&Path, (Pair){row, col});
    while (!isEmpty(&Path))
    {
        Pair p = pop(&Path);
        printf("-> (%d,%d) ", p.first + 1, p.second + 1);
    }

    return;
}

void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
    if (isValid(src.first, src.second) == false)
    {
        printf("Punctul de start este invalid.\n");
        return;
    }

    if (isValid(dest.first, dest.second) == false)
    {
        printf("Destinatia este invalida.\n");
        return;
    }

    if (isUnBlocked(grid, src.first, src.second) == false ||
        isUnBlocked(grid, dest.first, dest.second) == false)
    {
        printf("Punctul de start sau destinatia sunt blocate.\n");
        return;
    }

    if (isDestination(src.first, src.second, dest) == true)
    {
        printf("Esti deja la destinatie.\n");
        return;
    }

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    cell cellDetails[ROW][COL];

    int i, j;
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    qPair openList[ROW * COL];
    int openListSize = 0;

    openList[openListSize++] = (qPair){0.0, {i, j}};

    bool foundDest = false;

    while (openListSize > 0)
    {
        qPair p = openList[0];
        for (int k = 1; k < openListSize; k++)
        {
            if (openList[k].first < p.first)
            {
                p = openList[k];
            }
        }

        for (int k = 0; k < openListSize; k++)
        {
            if (openList[k].second.first == p.second.first && openList[k].second.second == p.second.second)
            {
                for (int m = k; m < openListSize - 1; m++)
                {
                    openList[m] = openList[m + 1];
                }
                openListSize--;
                break;
            }
        }

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        // Cadranul de Nord
        if (isValid(i - 1, j) == true)
        {
            if (isDestination(i - 1, j, dest) == true)
            {
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i - 1][j] == false && isUnBlocked(grid, i - 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew)
                {
                    openList[openListSize++] = (qPair){fNew, {i - 1, j}};
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        // Cadranul de Sud
        if (isValid(i + 1, j) == true)
        {
            if (isDestination(i + 1, j, dest) == true)
            {
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i + 1][j] == false && isUnBlocked(grid, i + 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew)
                {
                    openList[openListSize++] = (qPair){fNew, {i + 1, j}};
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        // Cadranul de Est
        if (isValid(i, j + 1) == true)
        {
            if (isDestination(i, j + 1, dest) == true)
            {
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i][j + 1] == false && isUnBlocked(grid, i, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew)
                {
                    openList[openListSize++] = (qPair){fNew, {i, j + 1}};
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        // Cadranul de vest
        if (isValid(i, j - 1) == true)
        {
            if (isDestination(i, j - 1, dest) == true)
            {
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i][j - 1] == false && isUnBlocked(grid, i, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew)
                {
                    openList[openListSize++] = (qPair){fNew, {i, j - 1}};
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }
    }

    if (foundDest == false)
    {
        printf("Nu s-a putut ajunge la destinatie.\n");
    }

    return;
}
int main()
{
    int m[ROW][COL] =
        {
            {1, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 1},
            {1, 0, 1, 1, 0, 1},
            {1, 1, 1, 1, 0, 1}};

    printf("Traseul:\n");
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (m[i][j] == 1)
            {
                printf("+");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
    Pair src = {0, 0};
    Pair dest = {4, 5};

    aStarSearch(m, src, dest);

    return (0);
}