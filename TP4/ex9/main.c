#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int *lire_entiers(char *filename, int *n)
{
    FILE *f = fopen(filename, "r");
    int nb_lus = 0, cur = 0;
    int *tab = malloc(sizeof(int) * (*n));
    while (fscanf(f, "%d", &cur) != EOF)
    {
        tab[nb_lus] = cur;
        nb_lus++;
        // printf("cur: %d\n", cur);
    }
    if (nb_lus != *n)
        *n = nb_lus;
    fclose(f);
    return tab;
    // printf("%d\n", nb_lus);
}

int main()
{
    int y = 4;
    int *x = &y;
    int *tab = lire_entiers("test", x);
    for (int i = 0; i < 3; i++)
        printf("%d ", tab[i]);
    printf("\n%d %d\n", *x, y);
    free(tab);
}