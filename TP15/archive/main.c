#include "./graphe.h"
#include "./labyrinthe.h"

bool est_arc(graphe_t *g, int u, int v)
{
    adj_t *p = g->lv[u];
    bool ans = false;
    while (p != NULL)
    {
        ans |= p->voisin == v;
        p = p->suiv;
    }
    return ans;
}

/* Parcourt g en largeur depuis s, et renvoie l'arborescence
du parcours sous forme de tableau des pr´ed´ecesseurs */
int *bfs(graphe_t *g, int s)
{
    int n = g->n;
    int *pred = malloc(n * sizeof(int));
    // bool *visited = malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++)
        pred[i] = -1; //, visited[i] = false;
    pred[s] = s;
    // visited[s] = true;

    int *file = malloc(n * sizeof(int));
    int tete = 0;
    int queue = 1;
    file[0] = s;

    while (tete != queue)
    {
        int u = file[tete];
        tete++;
        adj_t *p = g->lv[u];
        while (p != NULL)
        {
            if (pred[p->voisin] == -1)
            {
                file[queue] = p->voisin;
                pred[p->voisin] = u;
                queue++;
            }
            p = p->suiv;
        }
    }
    return pred;
}

int *plus_court_chemin(graphe_t *g, int u, int v)
{
    int *pr = bfs(g, u);
    if (pr[v] == -1)
        return NULL;

    int *path = malloc(sizeof(int) * g->n);
    int idx = 0;
    int cur = v;
    while (cur != u)
    {
        // printf("%d\n", cur);
        path[idx] = cur;
        cur = pr[cur];
        idx++;
    }
    path[idx++] = u;
    int *rev_path = malloc(sizeof(int) * idx);
    for (int i = idx - 1, j = 0; i >= 0; i--, j++)
        rev_path[j] = path[idx - j - 1];
    return rev_path;
}

void chemin_lab(char *fn)
{
    lab_t *l = lire_labyrinthe(fn);
    graphe_t *g = graphe_labyrinthe(l);

    // afficher_graphe(g);

    int end = l->n * l->m - 1;
    int *path = plus_court_chemin(g, 0, end);
    assert(path != NULL);

    FILE *f = fopen("solution.txt", "w");
    int i = 0;
    while (path[i] != end)
    {
        int ni = path[i] / l->m;
        int mi = path[i] % l->m;
        fprintf(f, "%d %d\n", ni, mi);
        i++;
    }
    fprintf(f, "%d %d", l->n - 1, l->m - 1);
    fclose(f);
}

int main(int argc, char **argv)
{

    assert(argc == 2);
    chemin_lab(argv[1]);
    // graphe_t *g0 = lire_graphe("./test.txt");
    // int n = g0->n;
    // int *path = plus_court_chemin(g0, 0, 8);
    // FILE *f = fopen("./lab/petit.txt", "r");
    // int n, m;
    // fscanf(f, "%d %d", &n, &m);
    // char **grid = malloc(sizeof(char *) * n);
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //         fscanf(f, "%c", grid[i][j]);
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //         printf("%c ", grid[i][j]);
    //     printf("\n");
    // }
    lab_t *l0 = lire_labyrinthe("./lab/petit.txt");
}