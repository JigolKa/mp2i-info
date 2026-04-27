#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"

char *au_moins_une(char **l, int n)
{
    int len_res = 0;
    for (int i = 0; i < n; i++)
    {
        // printf("%s\n", l[i]);
        len_res += strlen(l[i]);
    }
    int size_res = len_res + n - 1 + 2;
    char *res = malloc(sizeof(char) * (size_res + 1));
    int idx = 1;
    res[0] = '(';
    res[size_res - 1] = ')';
    for (int i = 0; i < n; i++)
    {
        int m = strlen(l[i]);
        for (int j = 0; j < m; j++)
        {
            res[idx] = l[i][j];
            idx++;
        }
        if (i != n - 1)
            res[idx] = '|',
            idx++;
    }
    return res;
}

char *exactement_une(char **l, int n)
{
    int len_res = 0;
    for (int i = 0; i < n; i++)
    {
        // printf("%s\n", l[i]);
        len_res += strlen(l[i]);
    }
    int size_res = len_res + n - 1 + 2;
    char *res = malloc(sizeof(char) * (size_res + 1));
    int idx = 1;
    res[0] = '(';
    res[size_res - 1] = ')';
    for (int i = 0; i < n; i++)
    {
        int m = strlen(l[i]);
        for (int j = 0; j < m; j++)
        {
            res[idx] = l[i][j];
            idx++;
        }
        if (i != n - 1)
            res[idx] = '%',
            idx++;
    }
    return res;
}

char *toutes(char **l, int n)
{
    if (n == 1)
        return l[0];

    int S = 0;
    for (int i = 0; i < n; i++)
    {
        // printf("%s %ld\n", l[i], strlen(l[i]));
        S += strlen(l[i]);
    }
    printf("here\n");
    int sz = S + 3 * (n - 1) + 2;
    // printf("sz: %d\n", size_res);
    char *res = malloc(sizeof(char) * (sz + 1));
    int idx = 1;
    res[0] = '(';
    res[sz - 1] = ')';
    for (int i = 0; i < n; i++)
    {
        int m = strlen(l[i]);
        for (int j = 0; j < m; j++)
        {
            res[idx++] = l[i][j];
        }
        if (i != n - 1)
            res[idx++] = ' ',
            res[idx++] = '&',
            res[idx++] = ' ';
    }
    // printf("idx: %d, sz: %d\n", idx, size_res);
    return res;
}

char *aucun(char **l, int n)
{
    char *s = toutes(l, n);
    int len = strlen(s);
    char *res = malloc(sizeof(char) * (len + 4));
    sprintf(res, "~(%s)", s);
    return res;
}

/**
 * pour une clause
 * n-1 ~
 * n-1 &
 * 2 ()
 * => 2n+S
 *
 * n clauses
 * => (2n+S)*n + n-1 (|)
 *
 * + ()
 *
 * + nouvelle clause
 * => n-1 + S+ 4
 *
 * => (2n+S)*n+n+1=n(2n+S+1)+1
 */
// char *au_plus_une(char **l, int n)
// {
//     if (n == 1)
//         return l[0];

//     int clauses_sum = 0;
//     for (int i = 0; i < n; i++)
//         clauses_sum += strlen(l[i]);
//     int sz = n * (2 * n + clauses_sum + 1) + n + clauses_sum + 4;
//     char *res = malloc(sizeof(char) * sz);
//     res[0] = '(';
//     int idx = 1;
//     for (int i = 0; i < n; i++)
//     {
//         res[idx] = '(';
//         idx++;
//         for (int j = 0; j < n; j++)
//         {
//             if (i == j)
//             {
//                 res[idx] = '~', idx++;
//             }

//             for (int k = 0; k < strlen(l[j]); k++)
//             {
//                 res[idx] = l[j][k], idx++;
//             }
//             if (j != n - 1)
//                 res[idx] = '&', idx++;
//         }
//         res[idx] = ')', idx++;
//         if (i != n - 1)
//             res[idx] = '|', idx++;
//     }
//     res[idx] = '|', idx++;
//     res[idx] = '(', idx++;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < strlen(l[i]); j++)
//         {
//             res[idx] = l[i][j], idx++;
//         }
//         if (i != n - 1)
//             res[idx] = '|', idx++;
//     }
//     res[idx] = ')', idx++;
//     res[idx] = ')';
//     return res;
// }

// char *au_plus_une(char **l, int n)
// {
//     if (n <= 1)
//     {
//         char *s = malloc(2);
//         strcpy(s, "1");
//         return s;
//     }

//     // Calcul de la taille exacte
//     // Chaque clause : "~(li&lj)" = 3 + len(li) + len(lj) chars
//     // Entre clauses : "&"
//     int nb_clauses = n * (n - 1) / 2;
//     size_t total = 0;
//     for (int i = 0; i < n; i++)
//         for (int j = i + 1; j < n; j++)
//             total += 3 + strlen(l[i]) + strlen(l[j]);
//     total += nb_clauses - 1; // les '&'
//     total += 1;              // '\0'

//     char *res = malloc(total * sizeof(char));
//     if (!res)
//         return NULL;

//     char *ptr = res;
//     int first = 1;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             if (!first)
//                 *ptr++ = '&';
//             ptr += sprintf(ptr, "~(%s&%s)", l[i], l[j]);
//             first = 0;
//         }
//     }
//     *ptr = '\0';
//     return res;
// }

char *make_clause(char *a, char *b)
{
    size_t len = strlen(a) + strlen(b) + 6; // "(~a|~b)" + '\0'
    char *s = malloc(len * sizeof(char));
    sprintf(s, "(~%s|~%s)", a, b);
    return s;
}

char *append_and(char *left, char *right)
{
    size_t len = strlen(left) + strlen(right) + 1 + 1; // '&' + '\0'
    char *s = malloc(len * sizeof(char));
    sprintf(s, "%s&%s", left, right);
    return s;
}

/**
 * pour l = x1, ..., xn,
 * renvoie (~x1|~x2)&(~x1|~x3)&...&(~x(n-1)|~xn)
 */
char *au_plus_une(char **l, int n)
{
    if (n <= 1)
    {
        char *s = malloc(2);
        strcpy(s, "1"); // formule toujours vraie
        return s;
    }

    char *res = NULL;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            char *clause = make_clause(l[i], l[j]);

            if (res == NULL)
            {
                res = clause;
            }
            else
            {
                char *new = append_and(res, clause);
                free(res);
                free(clause);
                res = new;
            }
        }
    }

    return res;
}