#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "menu.h"

void affiche_elem(menu_elem_t *e)
{
    printf("%s%s: %.2f$\n", e->nom, e->vegan ? " (V)" : "", e->prix_unite);
}

void affiche_menu(menu_t *m)
{
    printf("Menu:\n");
    for (int i = 1; i <= m->nb_elems; i++)
    {
        printf("%d. ", i);
        affiche_elem(&m->elements[i - 1]);
    }
}

void init_commande(int *commande, int nb_elems)
{
    for (int i = 0; i < nb_elems; i++)
        commande[i] = 0;
}

void prendre_commande(int *commande, int nb_elems)
{
    init_commande(commande, nb_elems);
    printf("Choisissez les plats à commander:\n");
    int c;
    while (scanf("%d", &c) != 0)
        commande[c - 1]++;
}

void resume_commande(int *commande, menu_t *m)
{
    printf("Vous avez commandé:\n");
    for (int i = 0; i < m->nb_elems; i++)
    {
        printf("%dx %s\n", commande[i], m->elements[i].nom);
    }
}

double total_commande(int *commande, menu_t *m)
{
    double res = 0;
    for (int i = 0; i < m->nb_elems; i++)
        res += commande[i] * m->elements[i].prix_unite;
    return res;
}

void ajouter_element(menu_t *m, char *nom, double prix_unite, bool vegan)
{
    menu_elem_t new;
    strcpy(new.nom, nom);
    new.prix_unite = prix_unite, new.vegan = vegan;
    assert(m->nb_elems != MAX_ELEMS);
    m->elements[m->nb_elems] = new;
    m->nb_elems++;
}

bool lire_element(FILE *f, menu_elem_t *e)
{
    assert(e != NULL);

    char *buffer = NULL;
    size_t n;
    int len = getline(&buffer, &n, f);
    if (len == EOF)
        return false;

    int vegan;
    double prix;
    char nom[50];
    sscanf(buffer, "%le %d %[^\n]", &prix, &vegan, nom);

    strcpy(e->nom, nom);
    e->prix_unite = prix, e->vegan = vegan;
    return len != EOF;
}

void lire_menu(char *filename, menu_t *m)
{
    bool res = true;
    int n = 0;
    FILE *f = fopen(filename, "r");

    while (res)
    {
        res = lire_element(f, &m->elements[n]);
        n++;
    }
    m->nb_elems = n - 1;

    fclose(f);
}

void test()
{
    menu_elem_t menu_elt = {
        .nom = "Nuggets",
        .prix_unite = 9.2,
        .vegan = false};
    menu_elem_t menu_elt2 = {
        .nom = "Salade",
        .prix_unite = 2.2,
        .vegan = true};

    affiche_elem(&menu_elt), affiche_elem(&menu_elt2);

    menu_elem_t a = {
                    .nom = "Pâtes au saumon",
                    .prix_unite = 11.99,
                    .vegan = false},
                b = {
                    .nom = "Curry de butternut",
                    .prix_unite = 8.99,
                    .vegan = true,
                },
                c = {
                    .nom = "Soupe de poulet",
                    .prix_unite = 15.99,
                    .vegan = false,
                };
    menu_t m = {
        .nb_elems = 3,
        .elements = {a, b, c}};
    // affiche_menu(&m);

    menu_t m1;
    lire_menu("menu.txt", &m1);
    affiche_menu(&m1);
    // menu_elem_t el;
    // lire_element(f, &el);
    // affiche_elem(&el);
    // printf("%f\n", menu_elt.prix_unite);
}

int main(int argc, char **argv)
{
    assert(argc == 2);
    menu_t m;
    lire_menu(argv[1], &m);
    affiche_menu(&m);
    int *commande = malloc(sizeof(int) * (m.nb_elems));
    prendre_commande(commande, m.nb_elems);
    resume_commande(commande, &m);
    printf("Total: %.2lf$\n", total_commande(commande, &m));
    // test();
}