#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int fill_random(int t[], int n)
{
    for (int i = 0; i < n; i++)
        t[i] = (rand() % 21) - 10;
}

int main()
{
    int t[] = {1, 2, 3, 3, 4, 5};
    srand(time(NULL));
    fill_random(t, 6);
    for (int i = 0; i < 6; i++)
        printf("%d ", t[i]);
    printf("\n");
}