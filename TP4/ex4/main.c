#include <stdio.h>
#include <assert.h>

int somme(char *nom_fichier)
{
    FILE *f = fopen(nom_fichier, "r"); // ouverture en mode lecture
    assert(f != NULL);
    int x = 0;   // pour lire dans le fichier
    int tot = 0; // pour stocker la somme
    int nb_lus = 0;
    while (nb_lus != EOF)
    {
        tot += x;
        nb_lus = fscanf(f, "%d", &x); // nb_lus vaut ou EOF
    }
    fclose(f);
    return tot;
}

int main()
{
    printf("entier lu: %d\n", somme("test"));
}