#include "edge-sorting.h"

static void swap_edges(edge_t *e1, edge_t *e2)
{
    edge_t tmp = *e1;

    e1->ID_1 = e2->ID_1;
    e1->ID_2 = e2->ID_2;
    e1->weight = e2->weight;

    e2->ID_1 = tmp.ID_1;
    e2->ID_2 = tmp.ID_2;
    e2->weight = tmp.weight;
}

int partition(edge_t *a, int premier, int dernier)
{
    edge_t pivot = a[dernier];
    int j = premier;
    for (int i = premier; i < dernier; i++)
        if (a[i].weight >= pivot.weight)
            swap_edges(&a[i], &a[j]), j++;
    swap_edges(&a[dernier], &a[j]);
    return j;
}

void quick_sort(edge_t *a, int premier, int dernier)
{
    if (premier < dernier)
    {
        int pivot = partition(a, premier, dernier);
        quick_sort(a, premier, pivot - 1);
        quick_sort(a, pivot + 1, dernier);
    }
}

void on_place_edge_sort(edge_t *edge_arr, unsigned n)
{
    quick_sort(edge_arr, 0, n - 1);
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = i + 1; j < n; j++)
    //     {
    //         if (edge_arr[i].weight > edge_arr[j].weight)
    //             swap_edges(&edge_arr[i], &edge_arr[j]);
    //     }
    // }
}
