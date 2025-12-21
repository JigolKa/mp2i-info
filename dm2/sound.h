#include <stdint.h>
#pragma once
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