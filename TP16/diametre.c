#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) a > b ? b : a
#define max(a, b) a < b ? b : a

typedef struct
{
    int n;
    int **mat;
} graphe_t;

#define INF 10000000

int diametre(graphe_t *g)
{
    int **ans = malloc(sizeof(int *) * g->n);
    int maxi = 0;
    for (int i = 0; i < g->n; i++)
    {
        ans[i] = malloc(sizeof(int) * g->n);
        for (int j = 0; j < g->n; j++)
            ans[i][j] = g->mat[i][j];
    }

    for (int k = 0; k < g->n; k++)
        for (int i = 0; i < g->n; i++)
            for (int j = 0; j < g->n; j++)
            {
                ans[i][j] = min(ans[i][j], ans[i][k] + ans[k][j]);
                if (ans[i][j] != INF)
                    maxi = max(maxi, ans[i][j]);
            }

    return maxi;
}

graphe_t *GER(int n, float p)
{
    graphe_t *ans = malloc(sizeof(graphe_t));
    ans->n = n;
    ans->mat = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        ans->mat[i] = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int value = rand() % 10001;
            if (value <= 10000 * p)
                ans->mat[i][j] = 1, ans->mat[j][i] = 1;
            else
                ans->mat[i][j] = INF, ans->mat[j][i] = INF;
        }
    return ans;
}

void print_graphe(graphe_t *g)
{
    for (int i = 0; i < g->n; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < g->n; j++)
        {
            if (g->mat[i][j] == 1)
                printf("%d ", j);
        }
        printf("\n");
    }
}

void print_diametres(float p, int K, int n_max, char filename[])
{
    FILE *f = fopen(filename, "w");
    for (int n = 5; n <= n_max; n += 5)
    {
        for (int j = 0; j < K; j++)
        {
            fprintf(f, "%d %d\n", n, diametre(GER(n, p)));
        }
    }
}

int main()
{
    srand(time(NULL));
    // graphe_t *g = GER(5, 0.37);
    // print_graphe(g);
    // printf("%d\n", diametre(g));
    for (float p = 0.05; p <= 1; p += 0.05)
    {
        char filename[50];
        sprintf(filename, "p%f.txt", p);
        print_diametres(p, 5, 100, filename);
    }
}