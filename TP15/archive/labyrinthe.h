#ifndef LABY_H
#define LABY_H

#include "graphe.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


typedef struct labyrinthe {
	int n;
	int m;
	bool** grille;
} lab_t;


/* Renvoie le labyrinthe stocké dans fn */
lab_t* lire_labyrinthe(char* fn);

/* Renvoie le graphe correspondant à L.
   Deux cases sont connectées dans le graphe si elles sont libres et ont 
   un côté en commun. */
graphe_t* graphe_labyrinthe(lab_t* L);

#endif