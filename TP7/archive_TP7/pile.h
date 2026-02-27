#include <stdbool.h>

typedef struct pile pile_t;

/* Renvoie une pile vide */
pile_t* pile_vide();

/* Renvoie un booléen indiquant si p est vide */
bool est_vide(pile_t* p);

/* Empile x au sommet de p */
void empiler(pile_t* p, int x);

/* Dépile le sommet de p et le renvoie */
int depiler(pile_t* p);

/* Libère l'espace alloué à p */
void free_pile(pile_t* p);

void affiche_pile(pile_t* p);

int taille(pile_t*p);