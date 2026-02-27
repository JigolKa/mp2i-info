#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "pile.h"
typedef struct a { int aa; struct a* aaa; } a_t; struct pile{ a_t* a; }; pile_t* pile_vide(){ printf("Création d'une pile implémentée par mystère\n"); pile_t* p = malloc(sizeof(pile_t)); p->a = NULL; } bool est_vide(pile_t* p){ return (p->a == NULL); } void empiler(pile_t* p, int x){ a_t* m = p->a; a_t* a = malloc(sizeof(a_t)); a->aa = x; a->aaa = p->a; p->a = a; } int depiler(pile_t* p){ assert(!est_vide(p)); int res = p->a->aa; a_t* a = p->a->aaa; free(p->a);  p->a = a; return res; } void free_a(a_t* m){ if (m != NULL){ free_a(m->aaa); free(m); } } void free_pile(pile_t* p){ free_a(p->a); free(p); } void affiche_pile(pile_t* p){ for (a_t* m = p->a; m != NULL; m = m->aaa) { printf("%d ", m->aa); } printf("\n"); } 