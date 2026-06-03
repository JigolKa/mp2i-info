#include "graphe.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(){
	graphe_t* g0 = lire_graphe("g0.txt");
	afficher_graphe(g0);
	liberer_graphe(g0);
	return 0;
}