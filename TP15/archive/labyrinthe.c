#include "graphe.h"
#include "labyrinthe.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

lab_t *lire_labyrinthe(char *fn)
{
	int n, m;
	FILE *f = fopen(fn, "r");
	assert(f != NULL);
	fscanf(f, "%d %d", &n, &m);
	char c;
	fscanf(f, "%c", &c);
	// printf("[%d, %d]\n", n, m);
	bool **grille = malloc(n * sizeof(bool *));
	for (int i = 0; i < n; ++i)
	{
		grille[i] = malloc(m * sizeof(bool));
		for (int j = 0; j < m; ++j)
		{
			fscanf(f, "%c", &c);
			grille[i][j] = (c == 'X');
			// printf("%d %d %d\n", i, j, grille[i][j]);
		}
		// lire le retour ligne
		fscanf(f, "%c", &c);
	}
	lab_t *L = malloc(sizeof(lab_t));
	L->n = n;
	L->m = m;
	L->grille = grille;
	fclose(f);
	return L;
}

graphe_t *graphe_labyrinthe(lab_t *L)
{
	int n = L->n;
	int m = L->m;
	graphe_t *g = graphe_vide(n * m);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (!L->grille[i][j])
			{
				for (int di = -1; di <= 1; di++)
					for (int dj = -1; dj <= 1; dj++)
					{
						if (di * dj == 0 && (di != 0 || dj != 0))
						{
							if (0 <= i + di && i + di < n && 0 <= j + dj && j + dj < m && !L->grille[i + di][j + dj])
							{
								ajouter(g, i * m + j, (i + di) * m + (j + dj), true);
							}
						}
					}
			}
		}
	}
	return g;
}