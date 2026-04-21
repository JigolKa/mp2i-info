#include "./utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

int taille_entier(int x)
{
    int r = 1;
    while (x >= 10)
        r++, x /= 10;
    return r;
}

int sz_var(int i, int j)
{
    return 4 + taille_entier(i) + taille_entier(j);
}

// taille = O(ceil(log10n))
char *variable(int i, int j)
{
    char *res = malloc(sizeof(char) * sz_var(i, j));
    sprintf(res, "X_%d_%d", i, j);
    return res;
}

// taille = O(n²*log10n)
char *contrainte_une_ligne(int i, int n)
{
    char **variables = malloc(sizeof(char *) * n);
    for (int j = 0; j < n; j++)
    {
        variables[j] = malloc(sizeof(char) * sz_var(i, j));
        char *t = variable(i, j);
        strcpy(variables[j], t);
    }
    char *dis = au_moins_une(variables, n);
    char *con = au_plus_une(variables, n);

    printf("sz: %ld\n", strlen(dis));

    printf("sz: %ld\n", strlen(con));

    char *s[2] = {con, dis};
    return toutes(s, 2);
}

// taille = O(n³log10n)
char *contrainte_toutes_lignes(int n)
{
    char **contraintes = malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
    {
        contraintes[i] = malloc(sizeof(char) * 500);
        contraintes[i] = contrainte_une_ligne(i, n);
    }
    return toutes(contraintes, n);
}

// taille = O(n²*log10n)
char *contrainte_une_colonne(int j, int n)
{
    char **variables = malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
    {
        variables[i] = malloc(sizeof(char) * sz_var(i, j)); // 10 = 2log10n+3
        variables[i] = variable(i, j);
    }
    return au_plus_une(variables, n);
}

// taille = O(n³log10n)
char *contrainte_toutes_colonnes(int n)
{
    char **contraintes = malloc(sizeof(char *) * n);
    for (int j = 0; j < n; j++)
    {
        contraintes[j] = malloc(sizeof(char) * 500);
        contraintes[j] = contrainte_une_colonne(j, n);
    }
    return toutes(contraintes, n);
}

// taille = O(n²*log10n)?
/**
 * la diagonale va de haut en bas
 * et part de (i,j)
 */
char *contrainte_diagonales_A(int i, int j, int n)
{
    assert(i == 0 || j == 0);
    int sz = min(n - i, n - j);
    char **variables = malloc(sizeof(char *) * sz);
    int k = 0;
    while (i + k >= 0 && i + k < n && j + k < n && j + k >= 0)
    {
        // printf("(%d,%d)\n", i + k, j + k);
        variables[k] = malloc(sizeof(char) * sz_var(i, j)); // 10 = 2log10n+3
        variables[k] = variable(i + k, j + k);
        // printf("%s\n", variables[k]);
        k++;
    }
    return au_plus_une(variables, sz);
}

// taille = O(n²*log10n)?
/**
 * la diagonale va de haut en bas
 * et part de (i,j)
 */
char *contrainte_diagonales_B(int i, int j, int n)
{
    int sz = i + 1 - j;
    char **variables = malloc(sizeof(char *) * sz);
    int k = 0;
    while (i - k >= 0 && i - k < n && j + k < n && j + k >= 0)
    {
        // printf("(%d,%d)\n", i - k, j + k);
        variables[k] = malloc(sizeof(char) * sz_var(i, j)); // 10 = 2log10n+3
        variables[k] = variable(i - k, j + k);
        // printf("%s\n", variables[k]);
        k++;
    }
    return au_plus_une(variables, sz);
}

// taille = O(n³log10n)
char *contrainte_toutes_diagonales(int n)
{
    int sz = 4 * n - 2;
    char **contraintes = malloc(sizeof(char *) * sz);
    int idx = 0;
    int threshold = 500;
    for (int j = 0; j < n; j++)
    {
        contraintes[idx] = malloc(sizeof(char) * threshold);
        contraintes[idx] = contrainte_diagonales_A(j, 0, n);
        idx++;
    }
    for (int j = 1; j < n; j++)
    {
        contraintes[idx] = malloc(sizeof(char) * threshold);
        contraintes[idx] = contrainte_diagonales_A(0, j, n);
        idx++;
    }
    for (int j = 0; j < n; j++)
    {
        contraintes[idx] = malloc(sizeof(char) * threshold);
        contraintes[idx] = contrainte_diagonales_B(j, 0, n);
        idx++;
    }
    // printf("here %d %d\n", idx, sz);
    for (int j = 1; j < n; j++)
    {
        contraintes[idx] = malloc(sizeof(char) * threshold);
        contraintes[idx] = contrainte_diagonales_B(n - 1, j, n);
        idx++;
    }
    // printf("here\n");
    return toutes(contraintes, sz);
}

void gen_formule_n_dames(int n, char *filename)
{
    FILE *f = fopen(filename, "w");
    char *a = contrainte_toutes_lignes(n);
    char *b = contrainte_toutes_colonnes(n);
    char *c = contrainte_toutes_diagonales(n);
    char *r[3] = {a, b, c};
    char *res = toutes(r, 3);
    fprintf(f, "%s", res);
    fclose(f);
}

int main()
{
    // printf("%s\n", contrainte_une_ligne(0, 25));
    // for (int i = 0; i < 25; i++)
    //     for (int j = 0; j < 25; j++)
    //         printf("%s\n", variable(i, j));
    int x;
    char filename[50];
    printf("n=");
    scanf("%d", &x);
    printf("nom de fichier=");
    scanf("%s", filename);

    assert(x <= 9);

    gen_formule_n_dames(x, filename);
}