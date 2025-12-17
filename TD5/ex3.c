#include <stdio.h>

int *zeroes(int n)
{
    int t[100];
    for (int i = 0; i < n; i++)
        t[i] = 0;
    return t;
}

int main()
{
    int *t = zeroes(6);
    printf("%d\n", t[3]);
}