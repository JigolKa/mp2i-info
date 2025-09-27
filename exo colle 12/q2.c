#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

bool est_premier(int n)
{
    if (n <= 1)
        return false;
    bool ans = true;
    for (int i = 2; i * i <= n; i++)
        ans &= n % i != 0;
    return ans;
}

const int N = 1e6 - 1;

int *permutations(int n, int taille)
{
    int *permutations = (int *)malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; i++)
    {
        int rem = n % 10;
        n = (n - rem) / 10 + rem * pow(10, taille - 1);
        permutations[i] = n;
    }
    return permutations;
}

int main()
{
    bool est_premier_memo[N + 1], famille_vue[N + 1]; // id
    int famille[N + 1];
    est_premier_memo[0] = false;
    est_premier_memo[1] = false;
    for (int i = 2; i <= N; i++)
        est_premier_memo[i] = est_premier(i);
    for (int i = 0; i <= N; i++)
        famille[i] = -1, famille_vue[i] = false;

    int id = 0;
    for (int i = 2; i <= N; i++)
    {
        if (!est_premier_memo[i] || famille[i] != -1)
            continue;

        int k = i, taille = 0;
        while (k > 0)
            taille++, k /= 10;
        // printf("Permutations de %d:\n",i);
        int *perm = permutations(i, taille);

        bool is_circ = true;
        for (int i = 0; i < taille; i++)
        {
            is_circ &= est_premier_memo[perm[i]];
        }

        if (!is_circ)
            continue;

        for (int i = 0; i < taille; i++)
        {
            famille[perm[i]] = id;
        }

        id++;
    }

    for (int i = 1; i <= N; i++)
    {
        if (famille[i] != -1 && !famille_vue[famille[i]])
        {
            printf("Famille %d: %d\n", famille[i], i);
            famille_vue[famille[i]] = true;
        }
    }
    printf("\n");

    return 0;
}