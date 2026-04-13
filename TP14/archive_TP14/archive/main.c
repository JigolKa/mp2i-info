#include "grille.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int valeur(grille_t *g, char *chemin)
{
	int i = 0, j = 0;
	int sum = g->ordures[0][0];

	for (int k = 0; k < strlen(chemin); k++)
	{
		if (chemin[k] == 'R')
			j++;
		else
			i++;

		if (i < 0 || i >= g->n || j < 0 || j >= g->m)
			return -1;
		sum += g->ordures[i][j];
	}
	return sum;
}

char *chemin_aleatoire(grille_t *g)
{
	int down = g->n - 1, right = g->m - 1;
	char *res = malloc(sizeof(char) * (down + right));
	int i = 0;
	while (down + right > 0)
	{
		int r = rand() % 2;
		char c;
		if (down == 0)
			c = 'R', right--;
		else if (right == 0)
			c = 'D', down--;
		else
		{
			if (r == 0)
				down--,
					c = 'D';

			else
				right--,
					c = 'R';
		}
		res[i] = c;
		i++;
	}
	return res;
}

bool choix_glouton(grille_t *g, int i, int j)
{
	if (i == g->n - 1)
		return true;
	else if (j == g->m - 1)
		return false;

	return g->ordures[i + 1][j] <= g->ordures[i][j + 1];
}

char *chemin_glouton(grille_t *g)
{
	int i = 0, j = 0;
	int size = (g->n + g->m - 2);
	char *res = malloc(sizeof(char) * size);
	for (int k = 0; k < size; k++)
	{
		assert(0 <= i && i < g->n && 0 <= j && j < g->m);
		bool choix = choix_glouton(g, i, j);
		printf("%d\n", choix);
		res[k] = choix ? 'R' : 'D';
		if (choix)
			j++;
		else
			j++;
	}
	return res;
}

int main(int argc, char **argv)
{
	/* code */
	srand(time(NULL));

	assert(argc > 1);
	grille_t *g = lire_grille(argv[1]);
	char *chemin = chemin_glouton(g);
	printf("%s %d\n", chemin, valeur(g, chemin));
	printf("%d\n", choix_glouton(g, 0, 3));

	afficher_grille(g);

	liberer_grille(g);
	return 0;
}