#pragma once
#include "./sound.h"
#include <stdio.h>

typedef struct mix
{
    int n_tracks;
    track_t **tracks;
    float *vols;
} mix_t;

/**
 * Libère l'espace alloué par mix_t
 */
void free_mix(mix_t *t);

/**
 * Réduit un mix en un son
 */
sound_t *reduce_mix(mix_t *m);

/**
 * Calcule la fréquence associée  à une hauteur de note
 */
float pitch_to_freq(int n);

/**
 * Lit un fichier et créé une piste
 */
track_t *read_track(FILE *file);

/**
 * Charge un mix
 */
mix_t *load_mix(char *filename);