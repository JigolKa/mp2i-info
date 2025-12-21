#include "wav.h"
#include "./sound.h"
#include <stdio.h>

const int fech = 44100;

void write_int(FILE *f, int a, int size)
{
    // printf("%d %d\n", a, size);
    for (int i = 0; i < size; i++)
        fputc(a & 0xff, f), a >>= 8;
    // int cnt = 0;
    // while (a > 0)
    // {
    //     // printf("cnt:%d\n", cnt);
    //     fprintf(f, "%c", a % 256);
    //     a /= 256;
    //     cnt++;
    // }
    // while (cnt < size)
    // {
    //     fprintf(f, "%c", 0x00);
    //     cnt++;
    // }
    // printf("end: write_int\n");
}

void write_header(FILE *f, int n)
{
    write_int(f, 'R', 1);
    write_int(f, 'I', 1);
    write_int(f, 'F', 1);
    write_int(f, 'F', 1);

    write_int(f, 36 + L / 8 * n, 4);

    write_int(f, 'W', 1);
    write_int(f, 'A', 1);
    write_int(f, 'V', 1);
    write_int(f, 'E', 1);
    write_int(f, 'f', 1);
    write_int(f, 'm', 1);
    write_int(f, 't', 1);
    write_int(f, ' ', 1);

    write_int(f, 16, 4);
    write_int(f, 1, 2);
    write_int(f, 1, 2);
    write_int(f, fech, 4);

    write_int(f, fech * L / 8, 4);
    write_int(f, L / 8, 2);
    write_int(f, L, 2);

    write_int(f, 'd', 1);
    write_int(f, 'a', 1);
    write_int(f, 't', 1);
    write_int(f, 'a', 1);

    write_int(f, L * n / 8, 4);
}

void save_sound(char *filename, sound_t *s)
{
    FILE *f = fopen(filename, "w");

    write_header(f, s->n_samples);
    // printf("here3\n");
    for (int i = 0; i < s->n_samples; i++)
    {
        write_int(f, s->samples[i], 2);
    }

    fclose(f);
}