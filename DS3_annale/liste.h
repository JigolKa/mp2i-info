#include <stdbool.h>

struct maillon
{
    int valeur;
    maillon_t *suiv;
    maillon_t *prec;
};

struct liste
{
    maillon_t *tete;
    maillon_t *queue;
};

typedef struct maillon maillon_t;
typedef struct liste liste_t;
/* Renvoie la valeur stock é e dans le maillon m */
int valeur(maillon_t *m);
/* Renvoie le maillon suivant m */
maillon_t *suiv(maillon_t *m);
/* Renvoie le maillon pr é c é dant m */
maillon_t *prec(maillon_t *m);
/* Renvoie une liste vide */
liste_t *creer();
/* Renvoie true si l est vide , false sinon */
bool est_vide(liste_t *l);
/* Renvoie le maillon en t ^
e te de l */
maillon_t *tete(liste_t *l);
/* Renvoie le maillon en queue de l */
maillon_t *queue(liste_t *l);
/* Renvoie le premier maillon de l contenant x */
maillon_t *recherche(liste_t *l, int x);
/* Ajoute un maillon contenant x apr è s m . Renvoie le maillon cr é é */
maillon_t *ajouter_apres(maillon_t *m, int x);
/* Ajoute un maillon contenant x en t ^
e te de l . Renvoie le maillon cr é é */
maillon_t *ajouter_debut(liste_t *m, int x);
/* Supprime le maillon m de sa liste . */
void supprimer(maillon_t *m);