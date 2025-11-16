#include <stdio.h>
#include <assert.h>

int main()
{
    FILE *f = fopen("hello.txt", "w");
    assert(f != NULL);
    fprintf(f, "Hello World %d!\n", 2025);
    fclose(f);
}