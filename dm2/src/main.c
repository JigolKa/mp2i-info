#include <assert.h>
#include <stdio.h>
#include "./wav.h"
#include "./sound.h"
#include "./waveform.h"
#include "./melody.h"
#include <time.h>
#include <stdlib.h>
#include <time.h>

void tests_fonctions()
{
    sound_t *s = sine(440, 30000, 2, 44100);
    save_sound("sine.wav", s);

    save_sound("square.wav", square(440, 30000, 2, 44100));
    save_sound("triangle.wav", triangle(440, 30000, 2, 44100));
    save_sound("sawtooth.wav", sawtooth(440, 30000, 2, 44100));
}

void test_track()
{
    sound_t *l[9];
    float freq[9] = {440, 440, 440, 440, 440, 440, 493.88, 554.36, 493.88};
    float durees[9] = {0.5, 0.4, 0.1, 0.4, 0.1, 0.5, 0.5, 1, 1};
    int amp[9] = {0, 16000, 0, 16000, 0, 16000, 16000, 16000, 16000};
    for (int i = 0; i < 9; i++)
    {
        l[i] = sine(freq[i], amp[i], durees[i], 44100);
        // printf("size %d: %d\n", i, l[i]->n_samples);
        // char filename[6];
        // sprintf(filename, "%d.wav", i);
        // filename[5] = '\0';
        // save_sound(filename, l[i]);
    }
    track_t *t = malloc(sizeof(track_t));
    t->n_sounds = 9;
    t->sounds = l;
    sound_t *s = reduce_track(t);
    save_sound("track.wav", s);
}

void test_file()
{
    FILE *f = fopen("../archive/question_15/sonata_une_piste.txt", "r");
    track_t *res = read_track(f);
    sound_t *s = reduce_track(res);
    save_sound("../auclairdelalune.wav", s);
}

void test_mix()
{
    mix_t *res = load_mix("../archive/question_19/test5.txt");
    sound_t *s = reduce_mix(res);
    save_sound("../mixtest5.wav", s);
}

char *get_time(int duree)
{
    char *buf = malloc(sizeof(char) * 20);
    if (duree < 60)
        sprintf(buf, "%ds", duree);
    else
        sprintf(buf, "%dm%ds", duree / 60, duree % 60);
    return buf;
}

char *get_size(int octets)
{
    char *buf = malloc(sizeof(char) * 20);
    if (octets < 1000000)
        sprintf(buf, "%dKo", octets / 1000);
    else
        sprintf(buf, "%dMo", octets / 1000000);
    return buf;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    // test_mix();
    if (argc != 3)
    {
        printf("Utilisation correcte: ./wav_writer fichier_entrée fichier_sortie");
        return;
    }
    // assert(argc == 3);

    clock_t start = clock();
    mix_t *res = load_mix(argv[1]);
    sound_t *s = reduce_mix(res);
    save_sound(argv[2], s);
    clock_t end = clock();

    int duree = s->n_samples / 44100;
    long int octets = s->n_samples * sizeof(int16_t);

    printf("Fichier %s généré (temps écoulé: %ldms)\n", argv[2], (end - start) * 1000 / CLOCKS_PER_SEC);
    printf("Durée du fichier: %s (taille %s)\n", get_time(duree), get_size(octets));
}