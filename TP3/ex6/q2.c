#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int fill_random(int t[], int n)
{
    for (int i = 0; i < n; i++)
        t[i] = (rand() % 21) - 10;
}

void print_tab(int t[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d%c", t[i], " \n"[i == n - 1]);
}

int main()
{
    int t[] = {1, 2, 3, 3, 4, 5};
    srand(time(NULL));
    fill_random(t, 6);
    print_tab(t, 6);
}