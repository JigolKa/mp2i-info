#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

bool est_trie(int *T, int n)
{
    for (int i = 0; i < n - 1; i++)
        if (T[i] > T[i + 1])
            return false;
    return true;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_tab(int *t, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", t[i]);
    printf("\n");
}

void tri_selection(int *T, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int posmin = i;
        for (int j = i + 1; j < n; j++)
            if (T[posmin] > T[j])
                posmin = j;
        swap(&T[i], &T[posmin]);
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
    // if (T[s])
    // printf("%d %d\n", s, e);
}

void tri_rapide_entre(int *t, int n, int a, int b)
{
    if (a > b)
        return;
    int p = partition_entre(t, n, a, b);
    // printf("%d\n", p);
    tri_rapide_entre(t, n, a, p - 1);
    tri_rapide_entre(t, n, p + 1, b);
}

float test_tri_rapide(int n)
{
    float sum = 0;
    for (int i = 0; i < 20; i++)
    {
        int *t = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            t[i] = rand() % 100;
        // print_tab(t, n);
        clock_t deb = clock();
        tri_rapide_entre(t, n, 0, n - 1);
        clock_t fin = clock();
        sum += (fin - deb) * 1. / CLOCKS_PER_SEC;
    }
    return sum / n * 1.;
}

float test_tri_quadratique(int n)
{
    float sum = 0;
    for (int i = 0; i < 20; i++)
    {
        int *t = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            t[i] = rand() % 100;
        // print_tab(t, n);
        clock_t deb = clock();
        tri_selection(t, n);
        clock_t fin = clock();
        sum += (fin - deb) * 1. / CLOCKS_PER_SEC;
    }
    return sum / n * 1.;
}

void main()
{
    srand(time(NULL));
    int a = 5, b = 9;
    swap(&a, &b);
    // printf("%d %d\n", a, b);
    // int n = 8;
    // int t[] = {8, 2, 6, 3, 4, 1, 4, 9};
    // tri_rapide_entre(t, n, 0, n - 1);
    // // partition(t, 7);
    // // tri_selection(t, 7);
    // for (int i = 0; i < n; i++)
    //     printf("%d\n", t[i]);
    FILE *f2 = fopen("nn", "w"), *f1 = fopen("nlogn", "w");
    for (int i = 100; i <= 4000; i += 100)
    {
        printf("%d éléments\n", i);
        fprintf(f1, "%f\n", test_tri_rapide(i));
        fprintf(f2, "%f\n", test_tri_quadratique(i));
    }
    fclose(f1), fclose(f2);
}