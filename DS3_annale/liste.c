#include "liste.h"
#include <stdio.h>
#include <stdlib.h>


void afficher(liste_t *l)
{
    maillon_t *cur = l->tete;
    while (cur != NULL)
    {
        printf("%d ", cur->valeur);
        cur = cur->suiv;
    }
    printf("\n");
}

void aux_afficher(maillon_t *t)
{
    if (t == NULL)
        return;
    printf("%d ", t->valeur);
    aux_afficher(t->suiv);
}
void afficher2(liste_t *l)
{
    aux_afficher(l->tete);
}

void filtrer(liste_t *l)
{
    for (maillon_t *m = l->tete->suiv; m->suiv != NULL; m = m->suiv)
    {
        if (m->valeur % 2 == 0)
            continue;
        maillon_t *suiv = m->suiv;
        m->prec->suiv = suiv;
    }
    if (l->tete->valeur % 2 == 1)
    {
        l->tete = l->tete->suiv;
    }
    if (l->queue->valeur % 2 == 1)
    {
        // l->queue->valeur = l->queue->prec->valeur + 23;
        maillon_t *last = l->queue;
        l->queue = last->prec;
        free(l->queue->suiv);
        // last->prec->suiv = NULL;

        // free(l->queue);
        // l->queue = l->queue->prec;
    }
}

int main()
{
    liste_t *l = malloc(sizeof(liste_t));
    maillon_t *a = malloc(sizeof(maillon_t));
    maillon_t *b = malloc(sizeof(maillon_t));
    maillon_t *c = malloc(sizeof(maillon_t));
    a->valeur = 5, b->valeur = 1, c->valeur = 3;
    a->suiv = b, b->prec = a, b->suiv = c, c->prec = b;

    l->tete = a, l->queue = c;

    afficher(l);
    filtrer(l);
    afficher(l);
}