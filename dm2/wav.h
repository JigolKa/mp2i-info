#include <stdio.h>
#pragma once
#include "./sound.h"

/**
 * Ecris l'en-tête d'un fichier WAV
 */
void write_header(FILE *f, int n);

/**
 * Ecris un entier dans un fichier
 */
void write_int(FILE *f, int a, int size);

/**
 * Enregistre un son
 */
void save_sound(char *filename, sound_t *s);