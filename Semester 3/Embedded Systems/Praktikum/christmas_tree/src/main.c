#include "encoding.h"
#include "platform.h"
#include "startup.h"
#include "wrap.h"

#include "buzzer.h"
#include "song.h"
#include "gpio.h"
#include "stdio.h"
#include "pcf8591.h"
#include "ws2812b.h"

#define RED   { .green = 0x00, .red = 0xFF, .blue = 0x00 } 
#define GREEN { .green = 0xFF, .red = 0x00, .blue = 0x00 }
#define BLUE  { .green = 0x00, .red = 0x00, .blue = 0xFF }
#define START_COLOR 2

const buzzer_t buzzer = {
    .pin_offset = PIN_17_OFFSET
};

const song_t _song = {
    .freq = song,
    .duration = duration,
    .count = 48
};

const pcf8591_t pcf8591 = {
    .addr = 0x9E
};

const ws2812b_t ws2812b = {
    .pin_offset = PIN_15_OFFSET
};

color_t colors[] = { RED, GREEN, BLUE, RED, GREEN, BLUE, RED, GREEN, BLUE, RED, GREEN, BLUE };
int8_t color_index = START_COLOR;

void on_buzzer_note_callback()
{
    color_t *current_colors = colors + color_index;
    ws2812b_write(&ws2812b, current_colors, 10);
    if (--color_index < 0) {
        color_index = START_COLOR;
    }
}

int main()
{
    pcf8591_init();
    ws2812b_init(&ws2812b);
    buzzer_init(&buzzer);
    buzzer_note_callback = on_buzzer_note_callback;
    
    while (1) {
        uint8_t brightness = pcf8591_read(&pcf8591, A0);
        if (brightness >= 224U) {
            buzzer_play(&buzzer, &_song);
        }

        for (volatile uint32_t i = 0; i < 10000U; i++) {
        }
    }

    return 0;
}
