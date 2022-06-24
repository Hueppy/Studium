#ifndef WS2812B_H
#define WS2812B_H 

#include "platform.h"

typedef struct color {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} color_t;

typedef struct {
    uint32_t pin_offset;
} ws2812b_t;

void ws2812b_init(const ws2812b_t *dev);
void ws2812b_write(const ws2812b_t *dev, const color_t *data, uint8_t length);

#endif //WS2812B_H
