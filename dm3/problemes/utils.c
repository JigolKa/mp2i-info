#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"

char *au_moins_une(char **l, int n)
{
    int len_res = 0;
    for (int i = 0; i < n; i++)
        len_res += strlen(l[i]);
    int size_res = len_res + n + 1;
    char *res = malloc(sizeof(char) * size_res);
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

char *au_plus_une(char **l, int n)
{
    int *char_cnt = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        char_cnt[i] = strlen(l[i]);
    // int size_res = len_res + n + 1;
    // char *res = malloc(sizeof(char) * size_res);
}

int main()
{
    char *f[2] = {"(x&y)", "y"};
    printf("%s\n", au_moins_une(f, 2));
}