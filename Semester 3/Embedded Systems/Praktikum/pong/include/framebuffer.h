#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "FreeRTOS.h"
#include "semphr.h"

#include "display.h"

#define FONT_W 6
#define FONT_H 1
#define FONT_N 128

typedef struct {
    uint8_t buffer[DISP_W][DISP_H / 8];
    SemaphoreHandle_t mutex;
} framebuffer;

typedef enum {
    LEFT_TO_RIGHT,
    RIGHT_TO_LEFT
} print_direction;

void fb_init(framebuffer *fb);

void fb_clear(framebuffer *fb);
void fb_draw_line(framebuffer *fb, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void fb_draw_rectangle(framebuffer *fb, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void fb_print_char(framebuffer *fb, char c, uint8_t line, uint8_t column);
void fb_print(framebuffer *fb, char *string, uint8_t line, uint8_t column, print_direction dir);

void fb_paint(framebuffer *fb);

#endif

