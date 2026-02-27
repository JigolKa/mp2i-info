#include <stdio.h>
#include "../src/sound.h"
#include <stdlib.h>
#include <assert.h>
#undef L

int *read_bytes(FILE *f, int cnt)
{
    int *res = malloc(sizeof(int) * cnt);
    int c;
    for (int i = 0; i < cnt && (c = getc(f)) != EOF; i++)
        res[i] = c;
    return res;
}

long int petit_boutiste_transformation(int *bytes, int cnt)
{
    long int exp = 1, res = 0;

    for (int i = 0; i < cnt; i++)
    {
        // printf("%x\n", bytes[i]);
        res += bytes[i] * exp;
        exp *= 16 * 16;
    }
    return res;
}

void print_tab(int16_t *t, int n)
{
    printf("-----------\n");
    for (int i = 0; i < n; i++)
        printf("%d ", t[i]);
    printf("\n-----------\n");
}

sound_t *read_wav(char *filename)
{
    FILE *f = fopen(filename, "rb");
    sound_t *res = malloc(sizeof(sound_t));
    assert(f != NULL);

    read_bytes(f, 24);

    int *bytes = read_bytes(f, 4);
    int f_ech = petit_boutiste_transformation(bytes, 4);
    // printf("%d\n", f_ech);

    read_bytes(f, 6);

    bytes = read_bytes(f, 2);
    // print_tab(bytes2, 2);
    int L = petit_boutiste_transformation(bytes, 2);
    // printf("L=%d\n", L);

    read_bytes(f, 4);
    int value = petit_boutiste_transformation(read_bytes(f, 4), 4); // LN/8
    int N = 8 * value / L;
    // printf("N=%d\n", N);

    int bytes_per_sample = L / 8;
    res->samples = malloc(sizeof(int) * N);
    res->n_samples = N;
    int maxi = 1 << (L - 1);

    for (int i = 0; i < N; i++)
    {
        int *sample_bytes = read_bytes(f, bytes_per_sample);
        res->samples[i] = petit_boutiste_transformation(sample_bytes, bytes_per_sample);
        if (res->samples[i] >= maxi)
            res->samples[i] = res->samples[i] - 2 * maxi;
    }

    // print_tab(res->samples, N);
    // reverse_tab(res->samples, N);
    // print_tab(res->samples, N);

    fclose(f);
    return res;
}

void reverse_sound(sound_t *s)
{
    for (int i = 0; i < s->n_samples / 2; i++)
    {
        int tmp = s->samples[i];
        s->samples[i] = s->samples[s->n_samples - i - 1];
        s->samples[s->n_samples - 1 - i] = tmp;
    }
}