#include <stdbool.h>
#include <stdio.h>
#include "archive_TP7/file.h"
#include <stdlib.h>
typedef struct maillon
{
    int elem;
    struct maillon *suivant;
} maillon_t;

typedef struct file
{
    maillon_t *tete;
    maillon_t *queue;
} file_t;

file_t *file_vide()
{
    file_t *res = malloc(sizeof(file_t));
    res->queue = NULL;
    res->tete = NULL;
}

bool est_file_vide(file_t *f)
{
    return f->queue == NULL && f->tete == NULL;
}

void enfiler(file_t *f, int x)
{
    maillon_t *new = malloc(sizeof(maillon_t));
    new->elem = x;

    if (est_file_vide(f))
    {
        f->queue = new;
        f->tete = new;
    }
    else
    {
        f->queue->suivant = new;
    }
    new->suivant = NULL;
}

void affiche_file(file_t *f)
{
    maillon_t *cur = f->tete;
    while (cur != NULL)
    {
        printf("%d%s", cur->elem, (cur->suivant == NULL ? "\n" : " <- "));
        cur = cur->suivant;
    }
}

int main()
{
    file_t *f = file_vide();
    enfiler(f, 2);
    enfiler(f, 4);
    affiche_file(f);
}