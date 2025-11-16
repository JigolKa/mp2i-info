#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv)
{
    assert(argc == 2);
    FILE *f = fopen(argv[1], "r");
    char *ligne = NULL;
    unsigned long int n = 0, i = 1;
    while (getline(&ligne, &n, f) != EOF)
    {
        printf("%ld. %s", i, ligne);
        i++;
    }
    printf("\n");
}