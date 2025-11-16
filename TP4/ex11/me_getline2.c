#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * buffer != NULL
 */
int ma_getline(char **buffer, unsigned long int *n, FILE *f)
{
    int initial_size = strlen(*buffer);

    int size = initial_size * 2, read = initial_size;
    *buffer = realloc(*buffer, size * sizeof(char));
    char c = '\0';
    while (read < (int)*n && fscanf(f, "%c", &c) != EOF)
    {

        if (read + 1 == size)
        {
            size *= 2;
            *buffer = realloc(*buffer, size * sizeof(char));
        }

        printf("c=%c\n", c);
        (*buffer)[read] = c;
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
    // char *word = "abc";
    char *buffer = malloc(3 * sizeof(char));
    strcpy(buffer, "abc");
    unsigned long int y = 10;
    unsigned long int *n = &y;
    FILE *f = fopen("test1", "r");

    int read = ma_getline(&buffer, n, f);
    printf("read = %d\n", read);
    printf("buffer = %s\n", buffer);
}