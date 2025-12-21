#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void tri_par_insertion_entre(int *t, int n, int a, int b)
{
    for (int i = a + 1; i <= b; i++)
    {
        int x = t[i];
        int j = i;
        while (j > a && t[j - 1] > x)
        {
            t[j] = t[j - 1], j--;
        }
        t[j] = x;
    }
}

int partition_entre(int *T, int n, int a, int b)
{
    int p = T[a];
    int i = a + 1, s = b;

    while (i <= s)
    {
        if (T[i] <= p)
        {
            i++;
        }
        else
        {
            swap(&T[s], &T[i]);
            s--;
        }
    }
    swap(&T[a], &T[s]);
    return s;
}

void tri_hybride_entre(int *t, int n, int a, int b, int K)
{
    if (a > b)
        return;
    int sz = b - a + 1;
    if (sz <= K)
    {
        tri_par_insertion_entre(t, n, a, b);
        return;
    }

    int p = partition_entre(t, n, a, b);
    // printf("%d\n", p);
    tri_hybride_entre(t, n, a, p - 1, K);
    tri_hybride_entre(t, n, p + 1, b, K);
}

float test_tri_hybride(int n, int K)
{
    float sum = 0;
    for (int i = 0; i < 20; i++)
    {
        int *t = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            t[i] = rand() % 100;
        // print_tab(t, n);
        clock_t deb = clock();
        tri_hybride_entre(t, n, 0, n - 1, K);
        clock_t fin = clock();
        sum += (fin - deb) * 1. / CLOCKS_PER_SEC;

        free(t);
    }
    return sum / n * 1.;
}

int main()
{
    int n = 12;
    int tab[] = {9, 4, 4, 3, 1, 9, 8, 2, 12, 4, 39, 3};
    // tri_par_insertion_entre(tab, n, 2, 4);

    tri_hybride_entre(tab, n, 0, n - 1, 3);

    for (int i = 0; i < n; i++)
        printf("%d\n", tab[i]);

    srand(time(NULL));

    // FILE *f2 = fopen("nn", "w"), *f1 = fopen("nlogn", "w");
    for (int k = 30; k <= 100; k += 5)
    {
        char filename[50];
        sprintf(filename, "tri_hybride_k%d", k);
        printf("%s\n", filename);
        FILE *f = fopen(filename, "w");
        for (int i = 1000; i <= 100000; i += 1000)
        {
            printf("%d éléments\n", i);
            fprintf(f, "%f\n", test_tri_hybride(i, k));
        }
        fclose(f);
    }
}