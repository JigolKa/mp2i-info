#include "sound.h"
#pragma once

/* génère un bruit blanc */
sound_t *white(float duree, int f_ech);

/* renvoie un son sinusoïdal  */
sound_t *sine(float freq, int amplitude, float duree, int f_ech);

/* renvoie un son en créneaux */
sound_t *square(float freq, int amplitude, float duree, int f_ech);

/* renvoie un son en triangle */
sound_t *triangle(float freq, int amplitude, float duree, int f_ech);

/* renvoie un son en dent de scie */
sound_t *sawtooth(float freq, int amplitude, float duree, int f_ech);