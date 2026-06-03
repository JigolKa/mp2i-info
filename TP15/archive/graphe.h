#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// liste chainée pour stocker les voisins d'un sommet
struct adj{
	int voisin;
	struct adj* suiv;
};
typedef struct adj adj_t;

struct graphe {
	int n;
	adj_t** lv; // listes des voisins		
};
typedef struct graphe graphe_t;

/* Crée un graphe à n sommets, sans arêtes. */
graphe_t* graphe_vide(int n);

/* Ajoute l'arc (u, v) à g. Si oriente vaut false,
   ajoute aussi l'arc (v, u). */ 
void ajouter(graphe_t* g, int u, int v, bool oriente);

/* Renvoie le graphe décrit par le fichier filename */ 
graphe_t* lire_graphe(char* filename);

/* Affiche chaque sommet de g, et ses successeurs. */
void afficher_graphe(graphe_t* g);

/* Libère la mémoire allouée pour g. */
void liberer_graphe(graphe_t* g);

#endif