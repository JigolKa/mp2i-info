#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

bool egaux(int *t1, int *t2, int n)
{
    bool res = true;
    for (int i = 0; i < n; i++)
        res &= t1[i] == t2[i];
    return res;
}

int *zeros(int n)
{
    int *tab = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        tab[i] = 0;
    return tab;
}

int *zeros_uns(int n, int m)
{
    int *tab = malloc(sizeof(int) * (n + m));
    for (int i = 0; i < n; i++)
        tab[i] = 0;
    for (int i = n; i < n + m; i++)
        tab[i] = 1;
    return tab;
}

int main()
{
    int *tab = malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; i++)
        tab[i] = i;
    free(tab);

    int *zero3 = zeros(3);
    int *test = malloc(sizeof(int) * 3);
    test[0] = 0, test[1] = 0, test[2] = 0;

    assert(egaux(zero3, test, 3));
    free(test), free(zero3);

    int *zero_un3 = zeros_uns(2, 2);
    int *test2 = malloc(sizeof(int) * 4);
    test2[0] = 0, test2[1] = 0, test2[2] = 1, test2[3] = 1;
    assert(egaux(test2, zero_un3, 4));
    free(test2), free(zero_un3);
}