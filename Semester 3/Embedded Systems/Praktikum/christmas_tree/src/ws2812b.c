#include "gpio.h"
#include "ws2812b.h"

void ws2812b_init(const ws2812b_t *dev)
{
    gpio_output(MASK(dev->pin_offset));
}

void ws2812b_write_raw(uint32_t pin_mask, const uint8_t *data, uint8_t length)
{
    uint32_t state = GPIO_REG(GPIO_OUTPUT_VAL);

    // HERE BE DRAGONS
    asm volatile(
                 "sw   %[low],  0(%[output])\n" // reset
             "byte_loop:\n"
                 "li   t1, 0x80\n"              // t1: bit mask
             "bit_loop:\n"
                 "lb   t0, 0(%[data])\n"        // t0: current byte
                                                // yes we load the byte again for every bit even though this is not necessary
                 "sw   %[high], 0(%[output])\n"
                 "and  t2, t1, t0\n"
                 "srli t1, t1, 1\n"
                 "beqz t2, check_next\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
             "check_next:\n"                    // check if next byte needs to be loaded
                 "beqz t1, next\n"
                 "j    low\n"
             "next:\n"                             //preload next byte
                 "addi %[data],   %[data],    1\n"
                 "addi %[length], %[length], -1\n"
             "low:\n"
                 "sw   %[low],  0(%[output])\n"
                 "bnez t2, iter_end\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
             "iter_end:\n"
                 "bnez t1, bit_loop\n"
                 "bnez %[length], byte_loop\n"
             "end:"
                 "sw   %[high], 0(%[output])\n"
                 "sw   %[low],  0(%[output])\n" // reset
                 :
                 : [output] "r" (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL),
                   [high]   "r" (state |  pin_mask),
                   [low]    "r" (state & ~pin_mask),
                   [data]   "r" (data),
                   [length] "r" (length)
    );
}

void ws2812b_write(const ws2812b_t *dev, const color_t *data, uint8_t length)
{
    ws2812b_write_raw(MASK(dev->pin_offset), (const uint8_t *)data, length * sizeof(color_t));
}
