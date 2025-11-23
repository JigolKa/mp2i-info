#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

struct cours {
	char intitule[50];
	char prof[50];
	int salle; // identifiant unique de la salle
	int jour;  // 0 (lundi) - 6 (dimanche)
}; 

typedef struct cours cours_t;

int main(){
	printf("Taille du type: %ld octets\n", sizeof(cours_t));

	cours_t maths = {
		.intitule = "Mathématiques",
		.prof     = "O.G.",
		.salle    = 0xDE02,
		.jour     = 1
	};

	cours_t phy;
	strcpy(phy.intitule, "Physique");
	strcpy(phy.prof, "A.B.");
	phy.salle = 0xA212;
	phy.jour = 2;

	return 0;
}