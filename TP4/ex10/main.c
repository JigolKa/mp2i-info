#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <limits.h>

int **zeroes(int n, int m)
{
    int **mat = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        mat[i] = malloc(sizeof(int) * m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[i][j] = 0;
    return mat;
}

int **rand_mat(int n, int m, int a, int b)
{
    int **mat = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        mat[i] = malloc(sizeof(int) * m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[i][j] = rand() % (b - a + 1) + a;

    return mat;
}

void print_mat(int **g, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            printf("%d%c", g[i][j], j == m - 1 ? '\n' : ' ');
}

void free_mat(int **g, int n)
{
    for (int i = 0; i < n; i++)
        free(g[i]);
    free(g);
}

int **somme_mat(int **g1, int **g2, int n, int m)
{
    int **sum = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        sum[i] = malloc(sizeof(int) * m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            sum[i][j] = g1[i][j] + g2[i][j];
    return sum;
}

int **prod_mat(int **g1, int **g2, int n1, int m1, int n2, int m2)
{
    assert(m1 == n2);
    int **prod = malloc(sizeof(int *) * n1);
    for (int i = 0; i < n1; i++)
        prod[i] = malloc(sizeof(int) * m2);

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++)
        {
            prod[i][j] = 0;
            for (int k = 0; k < m1; k++)
                prod[i][j] += g1[i][k] * g2[k][j];
        }
    return prod;
}

int di[4] = {0, 0, 1, -1, 1, -1, 1, -1};
int dj[4] = {1, -1, 0, 0, 1, -1, -1, 1};
float moy_aux(int **g, int n, int m, int i, int j)
{
    int sum = g[i][j], c = 1;
    for (int k = 0; k < 8; k++)
    {
        int ni = i + di[k], nj = j + dj[k];
        if (0 <= ni && ni < n && 0 <= nj && nj & m)
            sum += g[ni][nj], c++;
    }
    return sum * 1. / c * 1.;
}

int *min_moy(int **g, int n, int m)
{
    float mini = INT_MAX, i0 = -1, j0 = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            float moy = moy_aux(g, n, m, i, j);
            if (moy < mini)
                moy = mini, i0 = i, j0 = j;
        }
    // printf("i0 = %d, j0 = %d\n", i0, j0);
    int res[2] = {i0, j0};
    return res;
}

int main()
{
    srand(time(NULL));
    int **z = zeroes(3, 4), **g = rand_mat(3, 3, 5, 10);
    print_mat(z, 3, 4);
    print_mat(g, 3, 3);
    free_mat(z, 3), free_mat(g, 3);
    // int A[2][3] = {{1, 2, 0},
    //                {4, 3, -1}};
    // int B[3][2] = {{5, 1},
    //                {2, 3},
    //                {3, 4}};
    // int **res = prod_mat(A, B, 2, 3, 3, 2);
}