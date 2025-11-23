#include <stdio.h>
#include <stdlib.h>

struct eleve
{
    char nom_complet[51];
    int jour, mois, annee; // date de naissance
    char metier[51];
};
typedef struct eleve eleve_t;

eleve_t *lire_eleve(FILE *f)
{
    eleve_t *cur = (eleve_t *)malloc(sizeof(eleve_t));

    fscanf(f, "%[^\n]\n", cur->nom_complet);
    fscanf(f, "%d %d %d\n", &cur->jour, &cur->mois, &cur->annee);
    fscanf(f, "%[^\n]\n", cur->metier);

    return cur;
}

eleve_t **lire_promo(FILE *f, int *n)
{
    fscanf(f, "%d\n", n);
    eleve_t **res = (eleve_t **)malloc(sizeof(eleve_t *) * *n);
    for (int i = 0; i < *n; i++)
        res[i] = lire_eleve(f);
    return res;
}

int main()
{
    FILE *f = fopen("promo_2015.txt", "r");
    int n;
    eleve_t **promo = lire_promo(f, &n);
    printf("Nombre d'élèves: %d\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("%s né le %d/%d/%d est devenu %s\n", promo[i]->nom_complet, promo[i]->jour, promo[i]->mois, promo[i]->annee, promo[i]->metier);
    }
}
