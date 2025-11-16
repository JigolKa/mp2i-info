#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv)
{
    assert(argc == 3);

    FILE *in = fopen(argv[1], "r"), *out = fopen(argv[2], "w");
    char word;
    while ((fscanf(in, "%c", &word)) == 1)
        fprintf(out, "%c", word);
}