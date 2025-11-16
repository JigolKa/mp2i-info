#include <stdio.h>
#include <assert.h>

int somme2(char *nom_fichier)
{
    FILE *f = fopen(nom_fichier, "r"); // ouverture en mode lecture
    assert(f != NULL);
    int x, y;
    int nb_lus = fscanf(f, "%d %d ", &x, &y); // lire deux entiers dans f
    assert(nb_lus == 2);
    fclose(f);
    return x + y;
}

int main()
{
    printf("entier lu: %d\n", somme2("test"));
    return 0;
}