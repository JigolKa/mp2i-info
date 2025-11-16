#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define min(a, b) a > b ? b : a

/**
 * Compare 2 chaînes de caractères
 * Renvoie true si a doit se placer avant b dans la liste triée
 */
bool op(char *a, char *b)
{
    int n = strlen(a), m = strlen(b);
    // printf("a=%s, b=%s, n=%d, m=%d\n", a, b, n, m);
    int i = 0;
    while (i < min(n, m) && a[i] == b[i])
        i++;

    for (; i < min(n, m); i++)
        if (a[i] < b[i])
            return true;
        else
            return false;

    printf("reached end of loop");
    printf("a=%s, b=%s\n", a, b);
    if (n > m)
        return false;
    return true;
}

/**
 * Trie tab dans l'ordre alphabétique
 * par l'algorithme bubble sort
 */
void sort(char **tab, int n)
{
    int swaps = -1;
    int k = 0;
    while (swaps != 0)
    {
        swaps = 0;
        for (int i = k + 1; i < n; i++)
        {
            // printf("tab[k]=%s,tab[i]=%s, tab[k]>tab[i]=%d\n", tab[k], tab[i], op(tab[k], tab[i]));
            if (op(tab[i], tab[k]))
            {
                char *temp = tab[k];
                tab[k] = tab[i], tab[i] = temp;
                swaps++;
            }
        }
        k++;
    }
}

void op_tests()
{
    assert("a" < "b");
    assert(!op("ab", "aa")); // aa doit être placé avant ab
    assert(op("aa", "ac"));
    assert(op("aa", "aaa"));
    assert(!op("bc", "ab"));
    assert(op("aa", "b"));
}

void sort_test()
{
    int n = 4;
    char *tab[] = {"cde", "a", "aa", "bcd"};
    sort(tab, n);
    // for (int i = 0; i < n; i++)
    //     printf("idx %d: %s\n", i, tab[i]);
}

int main(int argc, char **argv)
{
    op_tests();
    sort_test();

    assert(argc == 3);
    FILE *f = fopen(argv[1], "r");

    int n = 0;
    char *cur = NULL;
    unsigned long int k = 0;
    while (getline(&cur, &k, f) != EOF)
        n++;

    // printf("lignes: %d\n", n);
    int i = 0;
    char **tab = malloc(sizeof(char *) * n);
    rewind(f);

    int len;
    while ((len = getline(&cur, &k, f)) != EOF)
    {
        // printf("cur=%s, len=%d\n", cur, len);
        tab[i] = malloc(sizeof(char) * len);
        strcpy(tab[i], cur);
        i++;
    }

    sort(tab, n);

    // for (int i = 0; i < n; i++)
    //     printf("i: %d, %s\n", i, tab[i]);

    fclose(f);

    f = fopen(argv[2], "w");
    for (int i = 0; i < n; i++)
        fprintf(f, "%s", tab[i]);
    fclose(f);

    for (int i = 0; i < n; i++)
        free(tab[i]);
    free(tab);
    free(cur);
    // for (int i = 0; i < n; i++)
    //     printf("len of ligne %d: %ld  %s\n", i, strlen(tab[i]), tab[i]);

    // printf("is a>b (a=%s, b=%s)? %d\n", tab[0], tab[1], op(tab[0], tab[1]));
}