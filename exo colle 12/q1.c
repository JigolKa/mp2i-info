#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// O(sqrt(n))
bool est_premier(int n)
{
    if (n <= 1 || (n % 2 == 0 && n > 2) || (n % 3 == 0 && n > 3))
        return false;
    for (int i = 5; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

const int N = 1e6;   // 1e9 - 1;
const int start = 1; // 1e6 + 1;
int puissances_10[] = {1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9};

// O(log(n)sqrt(n))
bool est_circulaire(int n, int taille)
{
    // int *permutations = (int *)malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; i++)
    {
        int rem = n % 10;
        assert(0 <= taille - 1 && taille - 1 < 10);
        n = (n - rem) / 10 + rem * puissances_10[taille - 1];
        if (!est_premier(n))
            return false;
    }
    return true;
}

int main()
{
    printf("start: %d, end: %d\n", start, N);
    for (int i = start; i <= N; i += 2)
    {
        if (!est_premier(i))
            continue;

        int k = i, taille = 0;
        while (k > 0)
            taille++, k /= 10;

        if (est_circulaire(i, taille))
            printf("%d est circulaire\n", i);
    }
    printf("done\n");

    return 0;
}