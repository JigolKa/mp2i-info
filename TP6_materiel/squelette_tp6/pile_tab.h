#ifndef PILE_TAB_H
#define PILE_TAB_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "elem.h"

struct s_pileT{
	int N;// nombre maximal d'éléments
	int n;// nombre d'éléments dans la pile, <=N
	type_elem* tab; //tableau de N cases
	//dont seules les n premières sont significatives
};

typedef struct s_pileT pileT;

//creation libération
pileT pile_vide(int cap);
void libere_pile(pileT p);

//affichage
void affiche_pile(pileT p);

//acces
bool est_pile_non_vide(pileT p);
type_elem sommet(pileT p);

//modification
void empile(pileT* p, type_elem e);
void depile(pileT* p);



#endif
