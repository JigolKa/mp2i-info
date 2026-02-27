#pragma once
#include <stdint.h>
#define L 16

typedef struct sound
{
    int n_samples;
    int16_t *samples;
} sound_t;

/**
 * Libère l'espace alloué par sound_t
 */
void free_sound(sound_t *s);

typedef struct track
{
    int n_sounds;
    sound_t **sounds;
} track_t;

/**
 * Libère l'espace alloué par track_t
 */
void free_track(track_t *t);

/**
 * Réduit une playlist en un son
 */
sound_t *reduce_track(track_t *t);