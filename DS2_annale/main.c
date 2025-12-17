#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void strcpyco(char *dst, char *src)
{
    int size = 0;
    while (src[size] != '\0')
        size++;
    // printf("size of src: %d\n", size);
    for (int i = 0; i < size; i++)
    {
        dst[i] = src[size - 1 - i];
    }
}

struct stylo
{
    char *couleur;
    float pourcentage;
    bool effacable;
};

int **produits(int n)
{
    int **res = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        res[i] = malloc(sizeof(int) * n);

    int *pre_fact = malloc(sizeof(int) * (n + 1));
    pre_fact[0] = 1;
    for (int i = 1; i <= n; i++)
        pre_fact[i] = pre_fact[i - 1] * i;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > j)
                res[i][j] = 1;
            else
                res[i][j] = i == 0 ? pre_fact[j] : pre_fact[j] / pre_fact[i - 1];
        }
    }
    return res;
}

struct festival
{
    char nom[40];
    int d; // d ´e but
    int f; // fin
};
typedef struct festival fes_t;

bool contient(fes_t *A, int x)
{
    return A->d <= x && x <= A->f;
}

bool intersect(fes_t *A, fes_t *B)
{
    return A->f >= B->d || B->f >= A->d;
}

int main()
{
    char *s = "blabla";
    char dst[20];
    strcpyco(dst, s);

    struct stylo s1 = {
                     .couleur = "vert",
                     .effacable = true,
                     .pourcentage = 50,
                 },
                 s2 = {
                     .couleur = "rouge",
                     .effacable = false,
                     .pourcentage = 0,
                 };
    struct stylo *stylos = malloc(sizeof(struct stylo) * 2);
    stylos[0] = s1, stylos[1] = s2;

    int n = 10;
    int **res = produits(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            printf("%d%c", res[i][j], j == n - 1 ? '\n' : '\t');

    printf("%s\n", dst);
}