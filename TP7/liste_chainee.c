#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

typedef struct maillon
{
    int elem;
    struct maillon* suivant;
} maillon_t;

typedef struct pile
{
    maillon_t* sommet;
} pile_t;

pile_t* pile_vide()
{
    pile_t*p=malloc(sizeof(pile_t));
    p->sommet=NULL;
    return p;
}

bool est_vide(pile_t*p)
{
    return p->sommet==NULL;
}

void empiler(pile_t* p, int x)
{
    maillon_t* new = malloc(sizeof(maillon_t));
    new->elem=x;
    maillon_t* cur = p->sommet;
    while (cur->suivant != NULL)
        cur=cur->suivant;
    cur->suivant=new;
}

int depiler(pile_t*p)
{
    assert(!est_vide(p));

    maillon_t* cur = p->sommet;
    // while
}

void free_pile(pile_t*p)
{
    maillon_t* cur = p->sommet;
    while (cur!=NULL)
    {
        maillon_t*next = cur->suivant;
        free(cur);
        cur=next;
    }
    free(p);
}

