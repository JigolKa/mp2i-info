#include <stdio.h>
#include <stdlib.h>

int **grid()
{
    int **g = malloc(3 * sizeof(int *));

    for (int i = 0; i < 3; i++)
    {
        g[i] = malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++)
            g[i][j] = (i == j);
    }
    return g;
}

void print_mat(int **g)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            printf("%d%c", g[i][j], j == 2 ? '\n' : ' ');
}

int main()
{
    int **g = grid();
    int x = 7;
    print_mat(g);
    g[2][1] = x;
    print_mat(g);

    g[1] = &x;
    print_mat(g);
}