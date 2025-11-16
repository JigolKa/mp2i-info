#include<stdio.h>

int main()
{
    printf("Entrez un entier: ");
    int n; scanf("%d",&n);
    char s[7];
    s[6]='\0';
    int ptr = 0;
    if (n%3==0)s[ptr]='g',s[ptr+1]='a',ptr+=2;
    if (n%5==0)s[ptr]='b',s[ptr+1]='u',ptr+=2;
    if (n%7==0)s[ptr]='z',s[ptr+1]='o',ptr+=2;
    if (ptr==0)
        printf("%d\n",n);
    else printf("%s\n",s);
    return 0;
}