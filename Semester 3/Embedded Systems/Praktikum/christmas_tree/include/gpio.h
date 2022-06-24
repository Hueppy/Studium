#ifndef GPIO_H
#define GPIO_H

#include "platform.h"

#define MASK(offset) (1 << offset)

void gpio_output(uint32_t mask);
void gpio_input(uint32_t mask);

void gpio_high(uint32_t mask);
void gpio_low(uint32_t mask);
void gpio_toggle(uint32_t mask);
uint32_t gpio_read(uint32_t mask);

#endif
