#include <stdint.h>

typedef struct {
    uint8_t addr;
} pcf8591_t;

typedef enum {
    A0 = 0,
    A1 = 1,
    A2 = 2,
    A3 = 3
} pcf8591_channel_t;

void pcf8591_init();
uint8_t pcf8591_read(const pcf8591_t *dev, const pcf8591_channel_t channel);
