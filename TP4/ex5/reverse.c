#include <stdio.h>
#include <assert.h>

char *renverser(char *s)
{
    int k = 0;
    // calcule la longueur de s
    while (*(s + k) != '\0')
        k++;
    for (int i = 0; i < k / 2; i++)
    {
        char temp = *(s + k - i - 1);
        *(s + k - i - 1) = *(s + i);
        *(s + i) = temp;
    }
}

int main()
{
    // char s[] = "chahus";
    // printf("%s\n", s);
    // renverser(s);
    // printf("%s\n", s);

    FILE *in = fopen("in", "r"), *out = fopen("out", "w");
    char word[100], ch;
    while ((fscanf(in, "%s", word)) == 1)
    {
        // printf("k=%s\n", word);
        renverser(word);
        fprintf(out, "%s", word);
        if (fscanf(in, "%c", &ch) == 1)
            fprintf(out, "%c", ch);
    }
    fclose(in), fclose(out);
}