#ifndef BUZZER_H
#define BUZZER_H

#include "platform.h"

typedef struct buzzer {
    const uint32_t pin_offset;
} buzzer_t;

typedef struct song {
    const int *freq;
    const float *duration;
    const uint8_t count;
} song_t;

typedef void (*buzzer_note_callback_t)();

extern buzzer_note_callback_t buzzer_note_callback;

void buzzer_init(const buzzer_t *buzzer);
void buzzer_play(const buzzer_t *buzzer, const song_t *song);

#endif
