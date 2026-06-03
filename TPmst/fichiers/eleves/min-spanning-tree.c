#include "min-spanning-tree.h"
#include "../city_graph.h"
#include "./edge-sorting.h"
#include <assert.h>

// -------------------- MSP computation -------------------- //
edge_t *kruskal(city_node_t *vertices, unsigned n)
{
    int N = (n * (n - 1) / 2);
    edge_t *aretes = malloc(sizeof(edge_t) * N);
    edge_t *ans = malloc(sizeof(edge_t) * (n - 1));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            aretes[i * n + j].weight = distance(vertices[i], vertices[j]),
                           aretes[i * n + j].ID_1 = i,
                           aretes[i * n + j].ID_2 = j;
    on_place_edge_sort(aretes, N);
    union_find uf = uf_create(n);
    int idx = 0;
    for (int i = 0; i < N; i++)
    {
        edge_t cur = aretes[i];
        printf("%f\n", cur.weight);
        if (uf_find(uf, cur.ID_1) == uf_find(uf, cur.ID_2))
            continue;
        ans[idx++] = cur;
        uf_unite(uf, cur.ID_1, cur.ID_2);
    }
    return ans;
}

edge_t *prim(city_node_t *vertices, unsigned n)
{
    fprintf(stderr, "La fonction 'prim' n'est pas implementee! Exit...\n");
    exit(1);
}
