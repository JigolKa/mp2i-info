#include "union-find.h"

union_find uf_create(size_t n)
{
    union_find ans = malloc(sizeof(size_t) * n);
    for (int i = 0; i < n; i++)
        ans[i] = i;
    return ans;
}

void uf_delete(union_find u)
{
    free(u);
}

size_t uf_parent(union_find u, size_t x)
{
    fprintf(stderr, "La fonction 'uf_parent' n'est pas implementee! Exit...\n");
    exit(1);
}

bool uf_is_root(union_find u, size_t x)
{
    return u[x] == x;
}

size_t uf_find(union_find u, size_t x)
{
    if (uf_is_root(u, x))
        return x;
    return u[x] = uf_find(u, u[x]);
}

size_t uf_unite(union_find u, size_t x, size_t y)
{
    u[uf_find(u, x)] = uf_find(u, y);
}
