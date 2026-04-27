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
    return 3 + taille_entier(i) + taille_entier(j);
}

// taille = O(ceil(log10n))
char *variable(int i, int j)
{
    char *res = malloc(sizeof(char) * (sz_var(i, j) + 1));
    sprintf(res, "X_%d_%d", i, j);
    return res;
}

/**
 * Contrainte 1:
 * Exactement 1 reine sur chaque ligne
 */
char *contrainte_une_ligne(int i, int n)
{
    char **variables = malloc(sizeof(char *) * n);
    for (int j = 0; j < n; j++)
    {
        variables[j] = variable(i, j);
    }
    char *res = exactement_une(variables, n);
    for (int i = 0; i < n; i++)
        free(variables[i]);
    free(variables);
    return res;
}

char *contrainte_toutes_lignes(int n)
{
    char **contraintes = malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
    {
        contraintes[i] = contrainte_une_ligne(i, n);
    }
    char *res = toutes(contraintes, n);
    for (int i = 0; i < n; i++)
        free(contraintes[i]);
    free(contraintes);
    return res;
}

/**
 * Contrainte 2:
 * Au plus une reine sur chaque colonne
 */
char *contrainte_une_colonne(int j, int n)
{
    char **variables = malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
    {
        variables[i] = variable(i, j);
    }
    char *res = au_plus_une(variables, n);
    for (int i = 0; i < n; i++)
        free(variables[i]);
    free(variables);

    return res;
}

char *contrainte_toutes_colonnes(int n)
{
    char **contraintes = malloc(sizeof(char *) * n);
    for (int j = 0; j < n; j++)
    {
        contraintes[j] = contrainte_une_colonne(j, n);
    }
    char *res = toutes(contraintes, n);
    for (int i = 0; i < n; i++)
        free(contraintes[i]);
    free(contraintes);
    return res;
}

/**
 * Contrainte 3:
 * Au plus une reine sur toutes les diagonales
 */
/**
 * la diagonale va de haut en bas vers la droite
 * [\,0,0,0]
 * [0,\,0,0]
 * [0,0,\,0]
 * [0,0,0,\]
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
        variables[k] = variable(i + k, j + k);
        // printf("%s\n", variables[k]);
        k++;
    }
    char *res = au_plus_une(variables, sz);
    for (int i = 0; i < sz; i++)
        free(variables[i]);
    free(variables);
    return res;
}

/**
 * la diagonale va de bas en haut vers la droite
 * [0,0,0,/]
 * [0,0,/,0]
 * [0,/,0,0]
 * [/,0,0,0]
 */
char *contrainte_diagonales_B(int i, int j, int n)
{
    int sz = i + 1 - j;
    char **variables = malloc(sizeof(char *) * sz);
    int k = 0;
    while (i - k >= 0 && i - k < n && j + k < n && j + k >= 0)
    {
        // printf("(%d,%d)\n", i - k, j + k);
        variables[k] = variable(i - k, j + k);
        // printf("%s\n", variables[k]);
        k++;
    }
    char *res = au_plus_une(variables, sz);
    for (int i = 0; i < sz; i++)
        free(variables[i]);
    free(variables);
    return res;
}

char *contrainte_toutes_diagonales(int n)
{
    int sz = 4 * n - 2 - 4;
    char **contraintes = malloc(sizeof(char *) * sz);
    int idx = 0;
    for (int j = 0; j < n - 1; j++)
    {
        contraintes[idx] = contrainte_diagonales_A(j, 0, n);
        idx++;
    }
    for (int j = 1; j < n - 1; j++)
    {
        contraintes[idx] = contrainte_diagonales_A(0, j, n);
        idx++;
    }
    for (int j = 1; j < n; j++)
    {
        contraintes[idx] = contrainte_diagonales_B(j, 0, n);
        idx++;
    }
    // printf("here %d %d\n", idx, sz);
    for (int j = 1; j < n - 1; j++)
    {
        contraintes[idx] = contrainte_diagonales_B(n - 1, j, n);
        idx++;
    }
    // printf("here\n");
    char *res = toutes(contraintes, sz);
    for (int i = 0; i < sz; i++)
    {
        free(contraintes[i]);
    }
    free(contraintes);
    return res;
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
    free(a), free(b), free(c);
    free(res);
    fclose(f);
}

int main()
{
    int n;
    char filename[50];
    printf("n=");
    scanf("%d", &n);
    printf("nom de fichier=");
    scanf("%s", filename);

    gen_formule_n_dames(n, filename);
}