#include <stdio.h>
#include <stdlib.h>
int *merge(int *a, int *b, int n, int m)
{
    int size = n + m;
    int *c;
    c = (int *)malloc(sizeof(int) * size);
    int ptr = 0, i = 0, j = 0;
    while (i < n && j < m)
    {
        if (a[i] < b[j])
            c[ptr++] = a[i++];
        else
            c[ptr++] = b[j++];
    }
    while (i < n)
        c[ptr++] = a[i++];
    while (j < m)
        c[ptr++] = b[j++];

    return c;
}

int *fusion(int *a, int n)
{
    // printf("n=%d\n",n);
    if (n <= 1)
    {
        return a;
    }

    int mid = n / 2;
    int *left, *right;
    left = (int *)malloc(sizeof(int) * mid), right = (int *)malloc(sizeof(int) * (mid + n % 2));
    for (int i = 0; i < mid; i++)
        left[i] = a[i];
    for (int i = mid; i < n; i++)
        right[i - mid] = a[i];

    int *res_left = fusion(left, mid), *res_right = fusion(right, mid + n % 2);
    return merge(res_left, res_right, mid, mid + n % 2);
}

int main()
{
    printf("Entrez un nombre d'éléments: ");
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    printf("Entrez les nombres de la liste:\n");
    for (int i = 0; i < n; i++)
    {
        int c;
        scanf("%d", &c);
        arr[i] = c;
    }
    // printf("here %d\n",5);
    int *res = fusion(arr, n);
    // printf("here\n");
    for (int i = 0; i < n; i++)
        printf("%d ", res[i]);
    printf("\n");
    return 0;
}