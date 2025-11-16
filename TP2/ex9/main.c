#include <stdio.h>
#define abs(x) (x) < 0 ? -(x) : (x)

// affiche les n premiers entiers dans l'ordre décroissant
void decroissant(int n)
{
    if (n < 0)
        return;
    printf("%d\n", n);
    decroissant(n - 1);
}

// affiche en ordre croissant
void croissant(int n)
{
    if (n < 0)
        return;
    croissant(n - 1);
    printf("%d\n", n);
}

// affiche les chiffres d'un nombre (n!=0 en entrée)
void chiffres(int n)
{
    if (n == 0)
        return;
    if (0 > n && n > -10)
        printf("-\n");

    chiffres(n / 10);
    printf("%d\n", abs(n % 10));
}

void ligne(int n)
{
    // printf("called with n=%d\n", n);
    if (n <= 0)
        return (void)printf("\n");
    printf("O");
    ligne(n - 1);
}

void q5(int n)
{
    if (n == 0)
        return;
    if (0 > n && n > -10)
        printf("-\n");

    q5(n / 10);
    ligne(abs(n % 10));
}
