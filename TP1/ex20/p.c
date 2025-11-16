#include<stdio.h>
#include<time.h>
int main()
{
    long int t = time(NULL);
    int y =  (t/(3600*24))/365.24, m = t/(3600*24*30.44);
    char* mois[12] = {"janvier", "février", "mars", "avril", "mai", "juin", "juillet", "août", "septembre", "octobre", "novembre", "décembre"};
    printf("Nous sommes en %s de l'année %d\n", mois[m%12], 1970+y);
    return 0;
}