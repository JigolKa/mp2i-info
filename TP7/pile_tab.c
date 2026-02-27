#include<stdbool.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
struct pile 
{
    int* elements;
    int taille_max;
    int taille;
};
typedef struct pile pile_t;

bool est_vide(pile_t* p)
{
    return p->taille==0;
}

pile_t* pile_vide()
{
    pile_t* p = malloc(sizeof(pile_t));
    p->taille=0;
    p->taille_max=10000;
    p->elements=malloc(sizeof(int)*p->taille_max);
}

void empiler(pile_t*p, int x)
{
    if (p->taille==p->taille_max)
    {
        p->taille_max*=2;
        p->elements=realloc(p->elements,p->taille_max * sizeof(int));
    }
    p->elements[p->taille] = x;
    (p->taille)++;
}

int taille(pile_t*p)
{
    return p->taille;
}

int depiler(pile_t*p)
{
    assert(!est_vide(p));
    int x = p->elements[p->taille-1];
    (p->taille)--;
    return x;
}

void free_pile(pile_t*p)
{
    free(p->elements);
    free(p);
}

void affiche_pile(pile_t*p)
{
    for (int i = 0;i<p->taille;i++)
        printf("%d ", p->elements[i]);
    printf("\n");
}