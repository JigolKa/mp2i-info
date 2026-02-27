#include "../src/sound.h"
#pragma once

/**
 * Lis un fichier .wav et renvois un sound_t*
 */
sound_t *read_wav(char *filename);

/**
 * Lis cnt octets du fichier lié au pointeur f
 */
int *read_bytes(FILE *f, int cnt);

/**
 * Transforme une liste d'entiers stockés en petit-boutiste en un entier
 * ex:
 * bytes = {2F, 03}
 * cnt = 2
 * petit_boutiste_transformation(bytes, cnt) = 815
 */
long int petit_boutiste_transformation(int *bytes, int cnt);

/**
 * Retourne un son en place
 */
void reverse_sound(sound_t *s);