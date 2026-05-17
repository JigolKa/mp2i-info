#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

// renvoie le nombre de chiffres d'un nombre n en base b
// remarque : b doit être non nul
int nb_chiffres(int n, int b)
{
    int res = 1;
    while ((n = (int)n / b) != 0)
    {
        res++;
    }
    return res;
}

// renvoie la variable associée à l'indice (i,j) sous la forme "X_[i]_[j]"
char *variable(int i, int j)
{
    // correspondance entre le nombre de caractères requis et le logarithme en base 10 (nombre de chiffres)
    char *var = malloc((6 + nb_chiffres(i, 10) + nb_chiffres(j, 10)) * sizeof(char));
    sprintf(var, "X_%d_%d", i, j);
    return var;
}

// renvoie la contrainte au problèmes des n_dames sur la ligne i
char *contrainte_une_ligne(int i, int n)
{
    char **ligne = malloc(n * sizeof(char *));
    for (int j = 0; j < n; j++)
    {
        ligne[j] = variable(i, j);
    }
    char *au_moins_une_dame = au_moins_une(ligne, n);
    char *au_plus_une_dame = au_plus_une(ligne, n);

    char *res = malloc((strlen(au_moins_une_dame) + strlen(au_plus_une_dame) + 6) * sizeof(char));
    sprintf(res, "(%s & %s)", au_moins_une_dame, au_plus_une_dame);

    // frees
    for (int j = 0; j < n; j++)
    {
        free(ligne[j]);
    }
    free(ligne);
    free(au_moins_une_dame);
    free(au_plus_une_dame);

    return res;
}

// renvoie la contrainte des n_dames sur toutes les lignes
char *contraintes_toutes_lignes(int n)
{
    char **lignes = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        lignes[i] = contrainte_une_ligne(i, n);
    }
    char *res = exactement(lignes, n);

    // frees
    for (int i = 0; i < n; i++)
    {
        free(lignes[i]);
    }
    free(lignes);

    return res;
}

// renvoie la contrainte au problèmes des n_dames sur la colonne j
char *contrainte_une_colonne(int j, int n)
{
    char **colonne = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        colonne[i] = variable(i, j);
    }
    char *res = au_plus_une(colonne, n);

    // frees
    for (int i = 0; i < n; i++)
    {
        free(colonne[i]);
    }
    free(colonne);

    return res;
}

// renvoie la contrainte des n_dames sur toutes les colonnes
char *contraintes_toutes_colonnes(int n)
{
    char **colonnes = malloc(n * sizeof(char *));
    for (int j = 0; j < n; j++)
    {
        colonnes[j] = contrainte_une_colonne(j, n);
    }
    char *res = exactement(colonnes, n);

    // frees
    for (int j = 0; j < n; j++)
    {
        free(colonnes[j]);
    }
    free(colonnes);

    return res;
}

// renvoie la contrainte sur la diagonale partant i,j de c cases de direction d
// remarque : la direction +1 correspond aux diagonales mmontantes, tandis que -1 les diagonales descendantes
char *contrainte_une_diagonale(int i, int j, int c, int d)
{
    char **diagonale = malloc(c * sizeof(char *));
    for (int l = 0; l < c; l++)
    {
        diagonale[l] = variable(i - l * d, j + l);
    }
    char *res = au_plus_une(diagonale, c);

    for (int l = 0; l < c; l++)
    {
        free(diagonale[l]);
    }
    free(diagonale);
    return res;
}

// renvoie la contrainte des n_dames sur toutes les diagonales
char *contraintes_toutes_diagonales(int n)
{
    char **diagonales = malloc((2 * (2 * n - 1)) * sizeof(char *));
    for (int k = 0; k < n; k++)
    {
        diagonales[k] = contrainte_une_diagonale(k, 0, k + 1, 1);
    }
    for (int k = 1; k < n; k++)
    {
        diagonales[k + n - 1] = contrainte_une_diagonale(n - 1, k, n - k, 1);
    }
    for (int k = 0; k < n; k++)
    {
        diagonales[k + 2 * n - 1] = contrainte_une_diagonale(n - k - 1, 0, k + 1, -1);
    }
    for (int k = 1; k < n; k++)
    {
        diagonales[k + 3 * n - 2] = contrainte_une_diagonale(0, k, n - k, -1);
    }

    char *res = exactement(diagonales, 2 * (2 * n - 1));

    for (int k = 0; k < 2 * (2 * n - 1); k++)
    {
        free(diagonales[k]);
    }
    free(diagonales);

    return res;
}

// génère la formule qui modélise le problème des n_dames et le stocke dans un fichier filename
// affiche également la taille de fichier généré et son nom
void gen_formule_n_dames(int n, char *filename)
{
    char *contrainte_ligne = contraintes_toutes_lignes(n);
    char *contrainte_colonne = contraintes_toutes_colonnes(n);
    char *contrainte_diagonale = contraintes_toutes_diagonales(n);
    char *contraintes[3] = {contrainte_ligne, contrainte_colonne, contrainte_diagonale};
    char *res = exactement(contraintes, 3);

    FILE *f = fopen(filename, "w");
    assert(f != NULL);

    fprintf(f, "%s", res);

    printf("fichier %s créé (%ld octets)\n\n", filename, strlen(res));

    free(contrainte_ligne);
    free(contrainte_colonne);
    free(contrainte_diagonale);
    free(res);

    fclose(f);
}

// --------------------------------------------------------------  TESTS

void t_variable()
{
    char *test1 = variable(1, 2);
    char *test2 = variable(4, 3);
    assert(strcmp(test1, "X_1_2") == 0);
    assert(strcmp(test2, "X_4_3") == 0);
    free(test1);
    free(test2);
}

void t_batterie_n_dames()
{
    printf("Vérification des tests n_dames... \n");
    t_variable();
    printf("Tous les tests n_dames ont réussi ! \n\n");
}

int main(int argc, char *argv[])
{
    // en argument seulement le nombre de dames/taille de l'échiquier
    assert(argc == 2);

    t_batterie_utils();
    t_batterie_n_dames();

    int n = atoi(argv[1]);

    // filename : n_dames.txt
    char *filename = malloc((nb_chiffres(n, 10) + 11) * sizeof(char));
    sprintf(filename, "%d_dames.txt", n);

    gen_formule_n_dames(n, filename);

    free(filename);
    return 0;
}