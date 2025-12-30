#include "waveform.h"
#include "sound.h"
#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

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

        // printf("%d\n", s->samples[i]);
    }
    return s;
}

sound_t *sine(float freq, int amplitude, float T, int f_ech)
{
    sound_t *s = malloc(sizeof(sound_t));
    int n = T * f_ech;
    s->n_samples = n;
    s->samples = malloc(sizeof(int) * n);
    double o = 2 * M_PI * freq / f_ech;

    for (int i = 0; i < n; i++)
        s->samples[i] = amplitude * sin(o * i);
    return s;
}

sound_t *square(float freq, int amplitude, float duree, int f_ech)
{
    sound_t *s = malloc(sizeof(sound_t));
    int n = duree * f_ech;
    s->n_samples = n;
    s->samples = malloc(n * sizeof(int));
    for (unsigned i = 0; i < n; ++i)
    {
        double x = freq * i / f_ech;
        s->samples[i] = amplitude * (2 * (floor(x) - floor(x - 0.5)) - 1);
    }
    return s;
}

sound_t *triangle(float freq, int amplitude, float duree, int f_ech)
{

    sound_t *s = malloc(sizeof(sound_t));
    int n = duree * f_ech;
    s->n_samples = n;
    s->samples = malloc(n * sizeof(int));
    double amp = amplitude * 2 / M_PI, omega = 2 * M_PI * freq / f_ech;

    for (unsigned i = 0; i < n; ++i)
    {
        s->samples[i] = amp * asin(sin(omega * i));
    }
    return s;
}

sound_t *sawtooth(float freq, int amplitude, float duree, int f_ech)
{
    sound_t *s = malloc(sizeof(sound_t));
    int n = duree * f_ech;
    s->n_samples = n;
    s->samples = malloc(n * sizeof(int));
    for (unsigned i = 0; i < n; ++i)
    {
        double x = freq * i / f_ech - 0.5;
        s->samples[i] = amplitude * (2 * (x - floor(x)) - 1);
    }
    return s;
}
