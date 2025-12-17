#include "waveform.h"
#include "sound.h"
#include <stdlib.h>
#include <stdio.h>

sound_t *white(float duree, int f_ech)
{
    sound_t *s = malloc(sizeof(sound_t));
    float t_ech = 1. / f_ech * 1.;
    int n = duree / t_ech + 1;

    s->n_samples = n;
    s->samples = malloc(sizeof(int) * n);
    int amplitude = 1 << (16 - 1); // L
    for (int i = 0; i < n; i++)
    {
        // printf("here\n");
        s->samples[i] = rand() % amplitude;
    }
    return s;
}
