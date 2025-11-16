#include<stdio.h>

int max(int a, int b)
{
    return a>b?a:b;
}
int min(int a, int b)
{
    return a>b?b:a;
}

int main()
{
    printf("Entrez 3 nombres séparés d'espaces: ");
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    int maxi = max(a, max(b,c)), mini = min(a,min(b,c));
    printf("Médian: %d\n", a+b+c-maxi-mini);
    return 0;
}