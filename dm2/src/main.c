#include <assert.h>
#include <stdio.h>
#include "./wav.h"
#include "./sound.h"
#include "./waveform.h"
#include "./melody.h"
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include "../extra/read_wav.h"
#include <string.h>

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

void test_base()
{
    int n = 3;
    int16_t samples[3] = {15387, 815, -6337};
    sound_t *s = malloc(sizeof(sound_t));
    s->n_samples = n;
    // memcp
    s->samples = malloc(sizeof(int16_t) * n);
    for (int i = 0; i < n; i++)
        s->samples[i] = samples[i];
    save_sound("./test45.wav", s);
}

void test_extra()
{
    sound_t *s = read_wav("./auclairdelalune.wav");
    reverse_sound(s);
    save_sound("./auclairdelalunereverse.wav", s);
    // free_sound(s);
}

void handle_output(sound_t *res, int duree, char *output)
{
    int length = res->n_samples / 44100;
    long int octets = res->n_samples * sizeof(int16_t);

    printf("Fichier %s généré (temps écoulé: %ldms)\n", output, duree * 1000 / CLOCKS_PER_SEC);
    printf("Durée du fichier: %s (taille %s)\n", get_time(length), get_size(octets));
}

int main(int argc, char **argv)
{
    // test_base();
    test_extra();
    // test_extra();
    srand(time(NULL));
    // test_mix();
    if (argc != 4)
    {
        printf("Utilisation correcte: ./wav_writer <mode> <fichier_entrée> <fichier_sortie>\n");
        printf("Modes différents:\n");
        printf("\t- Mode 1: Utilisation normale (fichier_entrée: .txt, fichier_sortie: .wav)\n");
        printf("\t- Mode 2: Fonctionnalité supplémentaire (renverser un son) (fichier_entrée: .wav, fichier_sortie: .wav)\n");
        return 0;
    }

    if (strcmp(argv[1], "1") == 0)
    {
        clock_t start = clock();

        mix_t *res = load_mix(argv[2]);
        sound_t *s = reduce_mix(res);
        save_sound(argv[3], s);

        clock_t end = clock();

        handle_output(s, end - start, argv[3]);
    }
    else
    {
        clock_t start = clock();

        sound_t *s = read_wav(argv[2]);
        reverse_sound(s);
        save_sound(argv[3], s);

        clock_t end = clock();

        handle_output(s, end - start, argv[3]);
    }

    return 0;
}