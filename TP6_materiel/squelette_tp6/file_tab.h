#ifndef FILE_TAB_H
#define FILE_TAB_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "elem.h"

struct s_fileT{
	int N;// nombre emaximal d'éléments
	int deb;// indice du premier element
	int fin;// indice du dernier elem +1
	type_elem* tab; //tableau de N cases
	//dont seules celle d'indices dans [deb..fin[ sont significatives
};

typedef struct s_fileT fileT;

//creation 
fileT file_vide(int cap);
void libere_file(fileT p);

//affichage
void affiche_file(fileT p);

//acces
bool est_file_non_vide(fileT p);
type_elem tete(fileT p);

//modification
void enfile(fileT* p, type_elem e);
void defile(fileT* p);



#endif
