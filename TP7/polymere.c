#include "archive_TP7/pile.h"
#include <stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
char* taille_stable(char*polymere)
{
    pile_t* p = pile_vide();

    int i = 0;
    while (polymere[i]!='\0')
    {
        if (est_vide(p))
        {
            empiler(p,polymere[i]);
        } 
        else
        {
            int last = depiler(p);
            if (polymere[i]>='a'&&polymere[i]<='z') // minuscule
            {
                if (last != polymere[i]-'a'+'A')
                    empiler(p,last),empiler(p,polymere[i]);
            } 
            else if (polymere[i]>='A'&&polymere[i]<='Z')
            {
                if (last != polymere[i]-'A'+'a')
                    empiler(p,last),empiler(p,polymere[i]);
            }
        }
        i++;
    }
    // affiche_pile(p);
    char* s = malloc(sizeof(int)*taille(p));
    for (int i = taille(p)-1;i>=0;i--)
    {
        s[i]=depiler(p);
    }

    free_pile(p);
    
    return s;

}

int main()
{
    FILE* f = fopen("archive_TP7/polymere.txt","r");
    assert(f!=NULL);
    char s[2000005];
    fscanf(f,"%s",s);
    printf("%s",s);
    // taille_stable(s);
    char* res = taille_stable(s);
    printf("%s %ld\n", res, strlen(res));
}