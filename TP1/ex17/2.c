#include<stdio.h>

int main()
{
    printf("Entrez un flottant: ");
    float a; scanf("%f",&a);
    int res = 0;
    if (-0.33<=a&&a<=7.89)res=1;
    else if (a>7.89)res=2;
    printf("cas %c\n", (char)(65+res));
    return 0;
}