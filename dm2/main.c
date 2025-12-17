#include <stdio.h>
#include "./wav.h"
#include "./sound.h"
#include "./waveform.h"
#include <time.h>
#include <stdlib.h>
// #include <stdlib.h>

int main()
{
    srand(time(NULL));
    // printf("here\n");
    // int16_t t[3] = {15387, 815, 6337};
    // sound_t s = {
    //     .n_samples = 3,
    //     .samples = t,
    // };
    // printf("here2\n");
    // save_sound("test", &s);
    sound_t *s = white(2, 44100);
    save_sound("white.wav", s);
}