#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

// affiche et compte les diviseurs de n
int diviseurs(int n)
{
    assert(n > 0);
    int cnt = 0;
    for (int i = 1; i * i <= n; i++)
        if (n % i == 0)
        {
            if (n % i == i)
                printf("%d ", i), cnt++;
            else
                printf("%d %d ", n % i, i), cnt += 2;
        }
    return cnt;
}

// renvoie la somme des n dés jetés
// srand(time(NULL)) supposé appelé avant la fonction
int des(int n)
{
    assert(n >= 0);
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += 1 + (rand() % 6);
    return sum;
}

// z=a+ib
float norme(int a, int b)
{
    return sqrt(a * a + b * b);
}

void triplets(int n)
{
    for (int a = 0; a <= n; a++)
        for (int b = a + 1; b <= n; b++)
        {
            int c = a * a + b * b;
            float root = sqrt(c);
            if (floorf(root) == root && root <= n)
                printf("%d %d %d\n", a, b, (int)root);
        }
}

int main()
{
    srand(time(NULL));
    triplets(10);
}