#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main()
{
    srand(time(NULL));
    int x = rand() % 11 + 10;
    printf("Nombre aléatoire: %d\n",x);
    return 0;
}