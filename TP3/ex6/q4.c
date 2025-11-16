#include <stdio.h>

int somme_cumulative(float *U, float *T, int n)
{
    U[0] = 0;
    for (int i = 1; i <= n; i++)
        U[i] = U[i - 1] + T[i - 1];
}

int main()
{
    float T[] = {2.5, 1.2, 72.3, .1}, U[5];
    somme_cumulative(U, T, 4);
    for (int i = 0; i < 5; i++)
        printf("%f ", U[i]);
}