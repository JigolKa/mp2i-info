#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char *au_moins_une(char **l, int n)
{
    // taille totale de la chaîne de caractère à générer par conjonction
    int size = 0;
    // taille individuelle de chaque formule atomique
    int *size_i = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        size_i[i] = strlen(l[i]);
        size += size_i[i];
    }
    // laisse de l'espace pour rajouter les disjonctions
    size += 3 * (n - 1) + 3;
    char *res = malloc(size * sizeof(char));

    res[0] = '(';
    int index = 1;
    for (int i = 0; i < n; i++)
    {
        strncpy(res + index, l[i], size_i[i]);
        index += size_i[i];
        if (i < n - 1)
        {
            res[index] = ' ';
            res[index + 1] = '|';
            res[index + 2] = ' ';
            index += 3;
        }
    }
    res[index] = ')';
    res[index + 1] = '\0';

    free(size_i);
    return res;
}

char *not(char *s)
{
    int n = strlen(s);
    char *res = malloc((2 + n) * sizeof(char));
    res[0] = '~';
    strncpy(res + 1, s, n);
    res[n + 1] = '\0';

    return res;
}

char *au_plus_une(char **l, int n)
{

    // taille totale de la chaîne de caractère à générer par conjonction
    int size = 0;
    // taille individuelle de chaque formule atomique
    int *size_i = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        size_i[i] = strlen(l[i]);
        size += size_i[i];
    }
    // espace nécessaire pour une conjonction avec (n-1) not
    size += 4 * (n - 1) + 3;

    // liste des conjonctions élélmentaires
    char **l_conj = malloc((n + 1) * sizeof(char *));

    // liste des not l
    char **not_l = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        not_l[i] = not(l[i]);
    }

    // creation des conjonctions non tous not
    for (int i = 0; i < (n + 1); i++)
    {
        if (i != n)
        {
            l_conj[i] = malloc(size * sizeof(char));
        }
        else
        {
            // l_conj[n] correspond à la conjonction où toutes les formules ne sont pas vraies
            l_conj[n] = malloc((size + 1) * sizeof(char));
        }

        l_conj[i][0] = '(';
        int index = 1;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                strncpy(l_conj[i] + index, not_l[j], (size_i[j] + 1));
                index += size_i[j] + 1;
            }
            else
            {
                strncpy(l_conj[i] + index, l[j], size_i[j]);
                index += size_i[j];
            }
            if (j < n - 1)
            {
                l_conj[i][index] = ' ';
                l_conj[i][index + 1] = '&';
                l_conj[i][index + 2] = ' ';
                index += 3;
            }
        }
        l_conj[i][index] = ')';
        l_conj[i][index + 1] = '\0';
    }

    char *res = au_moins_une(l_conj, (n + 1));

    // libère l'espace pris
    for (int i = 0; i < n; i++)
    {
        free(l_conj[i]);
        free(not_l[i]);
    }
    free(size_i);
    free(l_conj[n]);
    free(l_conj);
    free(not_l);

    return res;
}

char *exactement(char **l, int n)
{
    if (n == 0)
    {
        char *res = malloc(3 * sizeof(char));
        res[0] = '(';
        res[1] = ')';
        res[2] = '\0';
        return res;
    }

    // taille totale de la chaîne de caractère à générer par conjonction
    int size = 0;
    // taille individuelle de chaque formule atomique
    int *size_i = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        size_i[i] = strlen(l[i]);
        size += size_i[i];
    }
    // laisse de l'espace pour rajouter les disjonctions
    size += 3 * (n - 1) + 3;
    char *res = malloc(size * sizeof(char));

    res[0] = '(';
    int index = 1;
    for (int i = 0; i < n; i++)
    {
        strncpy(res + index, l[i], size_i[i]);
        index += size_i[i];
        if (i < n - 1)
        {
            res[index] = ' ';
            res[index + 1] = '&';
            res[index + 2] = ' ';
            index += 3;
        }
    }
    res[index] = ')';
    res[index + 1] = '\0';

    free(size_i);
    return res;
}

// --------------------------------------------------------------  TESTS

void t_au_moins_une()
{
    char *test1[3] = {"x", "y", "z"};
    char *test2[4] = {"(x & ~y)", "y", "(z | y)", "(x > ~z)"};
    char *test3[1] = {"x"};
    char *test4[0] = {};
    char *res1 = au_moins_une(test1, 3);
    char *res2 = au_moins_une(test2, 4);
    char *res3 = au_moins_une(test3, 1);
    char *res4 = au_moins_une(test4, 0);
    assert(strcmp(res1, "(x | y | z)") == 0);
    assert(strcmp(res2, "((x & ~y) | y | (z | y) | (x > ~z))") == 0);
    assert(strcmp(res3, "(x)") == 0);
    assert(strcmp(res4, "()") == 0);
    free(res1);
    free(res2);
    free(res3);
    free(res4);
}

void t_not()
{
    char *res1 = not("(x | y | z)");
    char *res2 = not("((x & ~y) | y | (z | y) | (x > ~z))");
    char *res3 = not("(x)");
    assert(strcmp(res1, "~(x | y | z)") == 0);
    assert(strcmp(res2, "~((x & ~y) | y | (z | y) | (x > ~z))") == 0);
    assert(strcmp(res3, "~(x)") == 0);
    free(res1);
    free(res2);
    free(res3);
}

void t_au_plus_une()
{
    char *test1[3] = {"x", "y", "z"};
    char *test2[4] = {"(x & ~y)", "y", "(z | y)", "(x > ~z)"};
    char *test3[1] = {"x"};
    char *test4[0] = {};
    char *res1 = au_plus_une(test1, 3);
    char *res2 = au_plus_une(test2, 4);
    char *res3 = au_plus_une(test3, 1);
    char *res4 = au_plus_une(test4, 0);
    assert(strcmp(res1, "((x & ~y & ~z) | (~x & y & ~z) | (~x & ~y & z) | (~x & ~y & ~z))") == 0);
    assert(strcmp(res2, "(((x & ~y) & ~y & ~(z | y) & ~(x > ~z)) | (~(x & ~y) & y & ~(z | y) & ~(x > ~z)) | (~(x & ~y) & ~y & (z | y) & ~(x > ~z)) | (~(x & ~y) & ~y & ~(z | y) & (x > ~z)) | (~(x & ~y) & ~y & ~(z | y) & ~(x > ~z)))") == 0);
    assert(strcmp(res3, "((x) | (~x))") == 0);
    assert(strcmp(res4, "(())") == 0);
    free(res1);
    free(res2);
    free(res3);
    free(res4);
}

void t_batterie_utils()
{
    printf("Vérification des tests utils ... \n");
    t_au_moins_une();
    t_not();
    t_au_plus_une();
    printf("Tous les tests utils ont réussi ! \n\n");
}