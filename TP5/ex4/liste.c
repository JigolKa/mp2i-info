#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct maillon
{
	struct maillon *suivant;
	int val;
};
typedef struct maillon maillon_t;

struct liste
{
	unsigned int taille;
	maillon_t *tete; // premier maillon
};
typedef struct liste liste_t;

/* Renvoie une liste de n entiers aléatoires entre 0 et 99 */
liste_t *liste_aleatoire(int n)
{
	assert(n >= 0);
	liste_t *res = malloc(sizeof(liste_t));
	res->taille = n;
	// si n = 0, on renvoie une liste vide
	if (n == 0)
	{
		res->tete = NULL;
		return res;
	}
	// sinon, on crée un premier maillon (la tête),
	// et on ajoute les n-1 maillons suivants à la suite
	res->tete = malloc(sizeof(maillon_t));

	// courant représente le dernier maillon ajouté
	maillon_t *courant = res->tete;
	courant->val = rand() % 100;
	for (int i = 1; i < n; ++i)
	{
		// créer un nouveau maillon et s'y positionner,
		// puis rentrer la valeur
		courant->suivant = malloc(sizeof(maillon_t));
		courant = courant->suivant;
		courant->val = rand() % 100;
	}
	// marquer la fin de la liste avec NULL
	courant->suivant = NULL;
	return res;
}

/* Affiche les valeurs de l dans l'ordre */
void liste_print(liste_t *l)
{
	assert(l != NULL);
	// parcourir la liste depuis la tête, en s'arrêtant
	// lorsque l'on atteint le NULL marquant la fin de liste
	maillon_t *m = l->tete;
	while (m != NULL)
	{
		printf("%d ", m->val);
		m = m->suivant;
	}
	printf("\n");
}

liste_t *liste_range(int n)
{
	liste_t *res = malloc(sizeof(liste_t));
	res->taille = n;
	res->tete = malloc(sizeof(maillon_t));
	maillon_t *cur = res->tete;
	for (int i = 0; i < n; i++)
	{
		cur->val = i;
		if (i != n - 1)
		{
			cur->suivant = malloc(sizeof(maillon_t));
			cur = cur->suivant;
		}
		else
			cur->suivant = NULL;
	}
	return res;
}

void free_maillon(maillon_t *cur)
{
	if (cur == NULL)
		return;
	free_maillon(cur->suivant);
	free(cur);
}
void free_liste(liste_t *liste)
{
	free_maillon(liste->tete);
	free(liste);
}

bool liste_recherche(int x, liste_t *L)
{
	maillon_t *cur = L->tete;
	while (cur != NULL && cur->val != x)
		cur = cur->suivant;
	return cur != NULL;
}

void push_front(int x, liste_t *L)
{
	maillon_t *cur = malloc(sizeof(maillon_t));
	cur->val = x;
	cur->suivant = L->tete;
	L->tete = cur;
}

void push_back(int x, liste_t *L)
{
	maillon_t *next = malloc(sizeof(maillon_t));
	next->val = x;
	next->suivant = NULL;

	if (L->taille == 0)
	{
		L->tete = next;
		return;
	}

	maillon_t *cur = L->tete;
	while (cur->suivant != NULL)
		cur = cur->suivant;
	cur->suivant = next;
}

void remove_first_occurence(int x, liste_t *L)
{
	if ((L->tete)->val == x)
	{
		maillon_t *first = L->tete;
		L->tete = first->suivant;
		free(first);
		return;
	}

	// on doit garder l'élément avant
	maillon_t *first = L->tete, *cur = (L->tete)->suivant;
	while (cur != NULL && cur->val != x)
		cur = cur->suivant, first = first->suivant;

	if (cur == NULL)
		return; // no occurence of x

	assert(cur->val == x);
	first->suivant = cur->suivant;
	free(cur);
}

int main()
{
	liste_t *res = liste_range(10);
	push_front(-1, res);
	push_back(10, res);
	liste_print(res);
	// free_liste(res);
	printf("remove: ");
	int x;
	scanf("%d", &x);
	remove_first_occurence(x, res);
	liste_print(res);
	// printf("is %d in L: %d\n", x, liste_recherche(x, res));
	free_liste(res);
}