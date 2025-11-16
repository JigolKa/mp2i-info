#include <assert.h>
#include <stdio.h>

int premier_zero(char *filename)
{
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    int n = 0, cur = 0;
    int x = 1;
    // tant qu'on est pas à la fin du fichier et que l'entier lu > 0
    while ((fscanf(f, "%d", &x)) != EOF && x > 0)
    {
        // printf("test: %d\n", x);
        n++;
    }
    fclose(f);
    return x == 0 ? n : -1;
}

int main()
{
    printf("%d\n", premier_zero("test"));
}