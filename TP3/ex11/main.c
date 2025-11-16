#include <stdio.h>

int str_len(char *s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

int occurences(char *s, char c)
{
    int cnt = 0, i = 0;
    while (s[i] != '\0')
        cnt += (s[i++] == c);
    return cnt;
}

int str_cmp(char *s1, char *s2)
{
    int i = 0, j = 0;
    while (s1[i] == s2[j] && s1[i] != '\0')
        i++, j++;
    if (s1[i] == '\0' && s2[j] == '\0')
        return 0;
    return s1[i] < s2[j] ? -42 : 42;
}

void str_cpy(char *dst, char *src)
{
    int i = 0;
    while (src[i] != '\0')
        dst[i] = src[i], i++;
}

void str_cat(char *dst, char *src)
{
    int i = 0, j = 0;
    while (dst[i] != '\0')
        i++;
    while (src[j] != '\0')
        dst[i] = src[j], i++, j++;
}

int main()
{
    char s1[40] = "Bonjour", s2[40] = "Au revoir";
    str_cat(s1, s2);
    printf("%s | %s\n", s1, s2);
}