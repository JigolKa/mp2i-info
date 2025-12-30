#include <assert.h>
#include "sound.h"
#include <stdlib.h>
#include <stdio.h>
#include "melody.h"
#define max(a, b) a > b ? a : b

void free_sound(sound_t *s)
{
    free(s->samples);
    free(s);
}

void free_track(track_t *t)
{
    for (int i = 0; i < t->n_sounds; i++)
        free(t->sounds[i]);
    free(t->sounds);
    free(t);
}

sound_t *reduce_track(track_t *t)
{
    sound_t *res = malloc(sizeof(sound_t));
    res->n_samples = 0;
    for (int i = 0; i < t->n_sounds; i++)
        res->n_samples += (t->sounds[i])->n_samples;
    res->samples = malloc(sizeof(int) * res->n_samples);

    // printf("size: %d, number of sounds:%d\n", res->n_samples, t->n_sounds);

    int j = 0;
    for (int i = 0; i < t->n_sounds; i++)
    {
        // printf("%d %d\n", j, (t->sounds[i])->n_samples);
        for (int k = 0; k < (t->sounds[i])->n_samples; k++)
            res->samples[j] = (t->sounds[i])->samples[k], j++;
    }

    return res;
}

void free_mix(mix_t *m)
{
    free(m->vols);
    for (int i = 0; i < m->n_tracks; i++)
        free_track(m->tracks[i]);
    free(m);
}

sound_t *reduce_mix(mix_t *m)
{
    sound_t **sounds = malloc(m->n_tracks * sizeof(sound_t *));
    float volume_somme = 0;
    int l_maxi = 0;
    for (int i = 0; i < m->n_tracks; i++)
    {
        sounds[i] = reduce_track(m->tracks[i]);
        l_maxi = max(l_maxi, sounds[i]->n_samples);
    }

    sound_t *res = malloc(sizeof(sound_t));
    res->n_samples = l_maxi, res->samples = malloc(sizeof(int) * l_maxi);

    for (int i = 0; i < l_maxi; i++)
    {
        float sum = 0, weight = 0; // Pas un int car le volume est un réel

        // On prend en compte que les pistes qui ont encore des samples
        // dans le calcul de la moyenne (pour diviser par weight et non la somme des volumes)
        for (int j = 0; j < m->n_tracks; j++)
            if (sounds[j]->n_samples > i)
                sum += sounds[j]->samples[i] * m->vols[j], weight += m->vols[j];

        // Silence si toutes les samples sont du silence
        res->samples[i] = weight != 0 ? sum / weight : 0;
    }

    return res;
}