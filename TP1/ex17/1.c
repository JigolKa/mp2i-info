#include<stdio.h>

int main()
{
    printf("Entrez un nombre: ");
    int a;scanf("%d",&a);
    if (a==0)
        printf("Nombre nul\n");
    else printf("Nombre non nul\n");
    return 0;
}