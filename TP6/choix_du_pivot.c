#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#define min(a, b) a > b ? b : a
#define max(a, b) a > b ? a : b

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int med(int a, int b, int c)
{
    int mini = min(a, min(b, c));
    int maxi = max(a, max(b, c));
    return a + b + c - maxi - mini;
}
/**
 * Pivot: premier
 */
int partition_entre(int *T, int n, int a, int b, int pivot)
{
    swap(&T[a], &T[pivot]);
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
/**
 * Pivot: 1er élément
 */
void tri_rapide_entre_pivot1(int *t, int n, int a, int b)
{
    if (a > b)
        return;
    int p = partition_entre(t, n, a, b, a);
    // printf("%d\n", p);
    tri_rapide_entre_pivot1(t, n, a, p - 1);
    tri_rapide_entre_pivot1(t, n, p + 1, b);
}
/**
 * Pivot: médiane
 */
void tri_rapide_entre_pivot2(int *t, int n, int a, int b)
{
    if (a > b)
        return;
    int p = partition_entre(t, n, a, b, med(t[a], t[b], t[(a + b) / 2]));
    // printf("%d\n", p);
    tri_rapide_entre_pivot2(t, n, a, p - 1);
    tri_rapide_entre_pivot2(t, n, p + 1, b);
}

float test_tri_rapide(int n)
{
    float sum = 0;
    for (int i = 0; i < 20; i++)
    {
        int *t = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            t[i] = rand() % 100;

        clock_t deb = clock();
        tri_rapide_entre_pivot1(t, n, 0, n - 1);
        clock_t fin = clock();

        sum += (fin - deb) * 1. / CLOCKS_PER_SEC;
    }
    return sum / n * 1.;
}

float test_tri_rapide2(int n)
{
    float sum = 0;
    for (int i = 0; i < 20; i++)
    {
        int *t = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            t[i] = rand() % 100;

        clock_t deb = clock();
        tri_rapide_entre_pivot2(t, n, 0, n - 1);
        clock_t fin = clock();

        sum += (fin - deb) * 1. / CLOCKS_PER_SEC;
    }
    return sum / n * 1.;
}

void main()
{
    srand(time(NULL));

    FILE *f2 = fopen("pivot1", "w"), *f1 = fopen("pivot_med", "w");
    for (int i = 1000; i <= 100000; i += 1000)
    {
        printf("%d éléments\n", i);
        fprintf(f1, "%f\n", test_tri_rapide(i));
        fprintf(f2, "%f\n", test_tri_rapide2(i));
    }
    fclose(f1), fclose(f2);
}