#include "waveform.h"
#include "sound.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1415
sound_t *white(float T, int f_ech)
{
    sound_t *s = malloc(sizeof(sound_t));
    int n = T * f_ech + 1;

    s->n_samples = n;
    s->samples = malloc(sizeof(int) * n);
    int A = 1 << L, An = A / 2;

    for (int i = 0; i < n; i++)
    {
        int v = (rand() << 1) ^ rand();
        s->samples[i] = (v % A) - An;

        // if (s->samples[i] > 0)
        //     printf("HERE\n");
        printf("%d\n", s->samples[i]);
    }
    return s;
}

sound_t *sine(float freq, int amplitude, float T, int f_ech)
{
    sound_t *s = malloc(sizeof(sound_t));
    int n = T * f_ech + 1;
    s->n_samples = n;
    s->samples = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        s->samples[i] = amplitude * sin(2 * PI * freq * i);
    return s;
}