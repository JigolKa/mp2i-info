#include <string.h>
#include <stdio.h>
#include "sound.h"
#include "waveform.h"
#include <math.h>
#include <stdlib.h>
#include "melody.h"

float pitch_to_freq(int n)
{
    return 440 * pow(2, n * 1. / 12.);
}

track_t *read_track(FILE *file)
{
    int n;
    char type[50];
    fscanf(file, "%d %s", &n, type);
    track_t *res = malloc(sizeof(track_t));
    res->n_sounds = n;
    res->sounds = malloc(sizeof(sound_t) * n);

    // printf("type: #%s#\n", type);

    int A = 2 << (L - 1) - 1;
    for (int i = 0; i < n; i++)
    {
        int hauteur;
        float duree, volume;
        fscanf(file, "%d %f %f", &hauteur, &duree, &volume);

        sound_t *(*f)(float, int, float, int) = sine;

        if (strcmp(type, "sawtooth"))
            f = sawtooth;
        else if (strcmp(type, "triangle"))
            f = triangle;
        else if (strcmp(type, "square"))
            f = square;

        res->sounds[i] = f(pitch_to_freq(hauteur), (int)(volume * A), duree, 44100);
    }

    return res;
}

mix_t *load_mix(char *filename)
{
    FILE *f = fopen(filename, "r");

    int n;
    fscanf(f, "%d", &n);
    float *vols = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        fscanf(f, "%f", &vols[i]);

    mix_t *res = malloc(sizeof(mix_t));
    res->n_tracks = n;
    res->vols = vols;
    res->tracks = malloc(sizeof(track_t) * n);
    for (int i = 0; i < n; i++)
        res->tracks[i] = read_track(f);
    fclose(f);

    return res;
}