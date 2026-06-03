#include "graphe.h"
#include <assert.h>

graphe_t *graphe_vide(int n)
{
	graphe_t *g = malloc(sizeof(graphe_t));
	g->lv = malloc(n * sizeof(adj_t *));
	g->n = n;
	for (int i = 0; i < n; ++i)
	{
		g->lv[i] = NULL;
	}
	return g;
}

void ajouter(graphe_t *g, int u, int v, bool oriente)
{
	adj_t *p = g->lv[u];
	while (p != NULL && p->voisin != v)
	{
		p = p->suiv;
	}
	if (p == NULL)
	{
		adj_t *nouveau_p = malloc(sizeof(adj_t));
		nouveau_p->voisin = v;
		nouveau_p->suiv = g->lv[u];
		g->lv[u] = nouveau_p;
	}
	if (!oriente)
	{
		ajouter(g, v, u, true);
	}
}

graphe_t *lire_graphe(char *filename)
{
	FILE *f = fopen(filename, "r");
	assert(f != NULL);
	int n, m, oriente;
	fscanf(f, "%d %d %d", &n, &m, &oriente);

	graphe_t *g = graphe_vide(n);
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		fscanf(f, "%d %d", &u, &v);
		ajouter(g, u, v, oriente);
	}

	fclose(f);
	return g;
}

void afficher_graphe(graphe_t *g)
{
	for (int i = 0; i < g->n; ++i)
	{
		printf("%d: ", i);
		// Explorer la liste des successeurs de i
		adj_t *p = g->lv[i];
		if (p == NULL)
		{
			printf("-");
		}
		else
		{
			while (p != NULL)
			{
				printf("%d, ", p->voisin);
				p = p->suiv;
			}
		}
		printf("\n");
	}
}

void liberer_graphe(graphe_t *g)
{
	for (int i = 0; i < g->n; ++i)
	{
		adj_t *p = g->lv[i];
		while (p != NULL)
		{
			adj_t *prev = p;
			p = p->suiv;
			free(prev);
		}
	}
	free(g->lv);
	free(g);
}