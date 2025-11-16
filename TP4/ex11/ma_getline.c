#include <stdlib.h>
#include <stdio.h>

/**
 * buffer = NULL
 */
int ma_getline(char **buffer, unsigned long int *n, FILE *f)
{
    int size = 1, read = 0;
    *buffer = realloc(*buffer, size * sizeof(char));
    char c = '\0';
    while (read < (int)*n && fscanf(f, "%c", &c) != EOF)
    {

        (*buffer)[read] = c;
        printf("c=%c\n", c);
        if (read + 1 == size)
        {
            size *= 2;
            *buffer = realloc(*buffer, size * sizeof(char *));
        }
        read++;
    }
    (*buffer)[read] = '\0';
    printf("size=%d\n", size);
    if (read != *n)
        *n = read;
    fclose(f);
    return *n;
}

int main()
{
    char *buffer = NULL;
    unsigned long int y = 10;
    unsigned long int *n = &y;
    FILE *f = fopen("test1", "r");

    int read = ma_getline(&buffer, n, f);
    printf("read = %d\n", read);
    printf("buffer = %s\n", buffer);
}