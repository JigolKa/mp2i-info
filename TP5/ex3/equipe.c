#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
struct etudiant
{
	char *prenom;
	unsigned int age;
};
typedef struct etudiant etu_t;

typedef struct equipe
{
	unsigned int nb_membres;
	etu_t **membres;		 // tableaux de pointeurs vers les membres de l'equipe
	unsigned int indice_cpt; // indice du capitaine dans le tableau des membres
} equipe_t;

void print_etu(etu_t *e)
{
	printf("%s, %d ans\n", e->prenom, e->age);
}
void print_equipe(equipe_t *eq)
{
	printf("%d membres:\n", eq->nb_membres);
	for (int i = 0; i < eq->nb_membres; i++)
	{
		printf("%d. ", i + 1);
		if (eq->indice_cpt == i)
			printf("(Capitaine) ");
		print_etu(eq->membres[i]);
	}
}

void free_etu(etu_t *e)
{
	free(e->prenom);
	free(e);
}
void free_eq(equipe_t *eq)
{
	for (int i = 0; i < eq->nb_membres; i++)
		free_etu(eq->membres[i]);
	free(eq->membres);
	free(eq);
}

void agrandir_eq(equipe_t *e1, equipe_t *e2)
{
	// le capitaine de l'équipe reste celui de l'équipe 1
	int size = e1->nb_membres + e2->nb_membres;
	e1->membres = realloc(e1->membres, size);
	printf("A %d\n", e2->nb_membres);
	for (int i = e1->nb_membres, j = 0; i < size; i++, j++)
	{
		printf("B\n");
		assert(e2->membres[j] != NULL);
		// print_etu(e2->membres[j]);
		etu_t *cur = e2->membres[j];
		e1->membres[i] = cur;
		// free_etu(e2->membres[j]);
	}
	// free(e2->membres);
	// free(e2);
	e1->nb_membres += e2->nb_membres;
	// free_eq(e2);
}

int main()
{
	etu_t *camille = malloc(sizeof(etu_t)), *leila = malloc(sizeof(etu_t)), *thibault = malloc(sizeof(etu_t));
	camille->age = 23, camille->prenom = malloc(sizeof(char) * 8);
	strcpy(camille->prenom, "Camille");

	leila->age = 20, leila->prenom = malloc(sizeof(char) * 6);
	strcpy(leila->prenom, "Leila");

	thibault->age = 22, thibault->prenom = malloc(sizeof(char) * 9);
	strcpy(thibault->prenom, "Thibault");

	equipe_t *eq = malloc(sizeof(equipe_t)), *eq2 = malloc(sizeof(equipe_t));
	eq->nb_membres = 2, eq->indice_cpt = 1;
	eq2->nb_membres = 1, eq2->indice_cpt = 0;

	eq->membres = malloc(sizeof(etu_t) * eq->nb_membres);
	eq2->membres = malloc(sizeof(etu_t) * eq2->nb_membres);

	eq->membres[0] = camille, eq->membres[1] = leila;

	eq2->membres[0] = thibault;
	print_equipe(eq);
	agrandir_eq(eq, eq2);
	print_equipe(eq);

	free_eq(eq);

	// printf("%s\n", camille->prenom);
}