#include "gpio.h"

void gpio_output(uint32_t mask)
{
	GPIO_REG(GPIO_IOF_EN)     &= ~mask;
    GPIO_REG(GPIO_INPUT_EN)   &= ~mask;
	GPIO_REG(GPIO_OUTPUT_EN)  |=  mask;
	GPIO_REG(GPIO_OUTPUT_VAL) |=  mask;
}

void gpio_input(uint32_t mask)
{
	GPIO_REG(GPIO_IOF_EN)     &= ~mask;
    GPIO_REG(GPIO_INPUT_EN)   |=  mask;
	GPIO_REG(GPIO_OUTPUT_EN)  &= ~mask;
	GPIO_REG(GPIO_OUTPUT_VAL) &= ~mask;    
}

void gpio_high(uint32_t mask)
{
    GPIO_REG(GPIO_OUTPUT_VAL) |= mask;
}

void gpio_low(uint32_t mask)
{
    GPIO_REG(GPIO_OUTPUT_VAL) &= ~mask;
}

void gpio_toggle(uint32_t mask)
{
    GPIO_REG(GPIO_OUTPUT_VAL) ^= mask;
}

uint32_t gpio_read(uint32_t mask)
{
    return GPIO_REG(GPIO_INPUT_VAL) & mask;
}
