#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "./headers.h"

choix_t *generer_choix(FILE *f)
{
    choix_t *choice = (choix_t *)malloc(sizeof(choix_t));
    fscanf(f, "%[^\n]\n%d\n", choice->texte, &choice->page_suivante);

    return choice;
}

page_t *generer_page(FILE *f)
{
    page_t *page = (page_t *)malloc(sizeof(page_t));

    fscanf(f, "%d\n%[^\n]\n", &page->n_choix, page->texte);

    page->choix = (choix_t **)malloc(sizeof(choix_t *) * page->n_choix);

    for (int i = 0; i < page->n_choix; i++)
    {
        page->choix[i] = generer_choix(f);
    }
    return page;
}

livre_t *generer_livre(FILE *f)
{
    int n;
    livre_t *livre = (livre_t *)malloc(sizeof(livre_t));
    fscanf(f, "%d", &n);
    livre->n_pages = n;
    livre->pages = (page_t **)malloc(sizeof(page_t *) * n);

    for (int i = 0; i < n; i++)
    {
        // livre->pages[i] = (page_t *)malloc(sizeof(page_t));
        livre->pages[i] = generer_page(f);
    }
    return livre;
}

void free_livre(livre_t *livre)
{
    for (int i = 0; i < livre->n_pages; i++)
    {
        page_t *page = livre->pages[i];
        // free(page->texte);
        for (int j = 0; j < page->n_choix; j++)
        {
            // free(choix->texte);
            free(page->choix[j]);
        }
        free(page->choix);
        free(page);
    }
    free(livre->pages);
    free(livre);
}

void afficher_choix(choix_t *choix)
{
    printf("%s %d\n", choix->texte, choix->page_suivante);
}

void afficher_page(page_t *page)
{
    printf("%s %d\n", page->texte, page->n_choix);
    for (int i = 0; i < page->n_choix; i++)
        afficher_choix(page->choix[i]);
}

int main(int argc, char **argv)
{
    assert(argc == 2);
    FILE *f = fopen(argv[1], "r");
    livre_t *livre = generer_livre(f);
    page_t *cur = livre->pages[0];
    system("clear");
    while (true)
    {
        printf("%s\n\n", cur->texte);
        if (cur->n_choix == 0)
            break;

        for (int i = 0; i < cur->n_choix; i++)
        {
            printf("\t%d. %s\n", i + 1, cur->choix[i]->texte);
        }
        printf("\nChoisissez une action: ");
        int action;
        scanf("%d", &action);
        action--;
        cur = livre->pages[cur->choix[action]->page_suivante];
        system("clear");
    }
    // printf("Vous avez perdu!\n");

    free_livre(livre);
    fclose(f);
}