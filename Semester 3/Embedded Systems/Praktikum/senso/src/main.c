#include <stdbool.h>
#include <stdint.h>

#define REG(P) (*(volatile uint32_t *)(P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_VAL 0x00
#define GPIO_INPUT_EN 0x04
#define GPIO_PUE 0x10
#define GPIO_OUTPUT_EN 0x08
#define GPIO_OUTPUT_VAL 0x0C
#define GPIO_IOF_EN 0x38

#define GREEN_LED (1U << 18)
#define BLUE_LED (1U << 21)
#define YELLOW_LED (1U << 0)
#define RED_LED (1U << 3)
#define ALL_LEDS GREEN_LED | BLUE_LED | YELLOW_LED | RED_LED

#define GREEN_BTN (1U << 19)
#define BLUE_BTN (1U << 20)
#define YELLOW_BTN (1U << 1)
#define RED_BTN (1U << 2)
#define ALL_BTNS GREEN_BTN | BLUE_BTN | YELLOW_BTN | RED_BTN

#define T_SHORT 184210
#define T_LONG T_SHORT * 2
#define T_VERY_LONG T_LONG * 2

enum color
{
    GREEN,
    BLUE,
    YELLOW,
    RED
};

uint8_t level;
uint8_t n;
uint32_t t;

const uint32_t leds[4] = {GREEN_LED, BLUE_LED, YELLOW_LED, RED_LED};

void wait(uint32_t t)
{
    for (volatile uint32_t i = 0; i < t; i++)
    {
    }
}

void blink(uint32_t mask, uint32_t t_on, uint32_t t_off)
{
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= mask;
    wait(t_on);
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~mask;
    wait(t_off);
}

uint32_t input(uint32_t mask)
{
    uint32_t input = ~REG(GPIO_BASE + GPIO_INPUT_VAL) & mask;
    if (input > 0U)
    {
        while ((~REG(GPIO_BASE + GPIO_INPUT_VAL) & mask) > 0U)
        {
        }
    }

    return input;
}

bool pressed(uint32_t mask)
{
    return input(mask) > 0U;
}

void init()
{
    // setup LED as output
    REG(GPIO_BASE + GPIO_IOF_EN) &= ~ALL_LEDS;
    REG(GPIO_BASE + GPIO_INPUT_EN) &= ~ALL_LEDS;
    REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ALL_LEDS;
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~ALL_LEDS;

    // setup BTN as input
    REG(GPIO_BASE + GPIO_IOF_EN) &= ~ALL_BTNS;
    REG(GPIO_BASE + GPIO_PUE) |= ALL_BTNS;
    REG(GPIO_BASE + GPIO_INPUT_EN) |= ALL_BTNS;
    REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~ALL_BTNS;

    blink(ALL_LEDS, T_SHORT, T_SHORT);
}

bool ready()
{
    uint8_t i = 0U;
    bool started = false;
    while ((i < sizeof(leds) / sizeof(leds[0])) && !started)
    {
        blink(leds[i], T_SHORT, T_SHORT);
        started = pressed(GREEN_BTN);
        i++;
    }

    return started;
}

void end()
{
    blink(ALL_LEDS, T_SHORT, T_LONG);
    blink(ALL_LEDS, T_LONG, T_LONG);
    blink(ALL_LEDS, T_SHORT, T_LONG);
    blink(ALL_LEDS, T_LONG, T_LONG);
}

void present(enum color pattern[])
{
    for (uint8_t i = 0; i < n; i++)
    {
        blink(leds[pattern[i]], t, T_SHORT);
    }
    blink(ALL_LEDS, T_SHORT, T_SHORT);
}

bool repeat(enum color pattern[])
{
    const uint32_t btns[] = {GREEN_BTN, BLUE_BTN, YELLOW_BTN, RED_BTN};

    uint8_t i = 0;
    bool correct = true;
    while ((i < n) && correct)
    {
        uint32_t cnt = t;
        uint32_t instate = 0;
        while ((instate == 0U) && (cnt > 0U))
        {
            instate = input(ALL_BTNS);
            cnt--;
        }

        // current input state xor button mask will flip the bit of that specific button
        // so when only the specific button is pressed the result will be 0
        // if any other button was pressed the result will be greater than 0
        correct = (instate ^ btns[pattern[i]]) == 0U;
        if (correct)
        {
            blink(leds[pattern[i]], T_SHORT, T_SHORT);
        }
        i++;
    }
    return correct;
}

void loose()
{
    for (uint8_t i = 0U; i < 5U; i++)
    {
        blink(YELLOW_LED, T_SHORT, T_SHORT);
    }

    uint8_t output = 0U;
    if ((level & (1U << 0)) > 0U)
    {
        output += RED_LED;
    }
    if ((level & (1U << 1)) > 0U)
    {
        output += YELLOW_LED;
    }
    if ((level & (1U << 2)) > 0U)
    {
        output += BLUE_LED;
    }
    if ((level & (1U << 3)) > 0U)
    {
        output += GREEN_LED;
    }

    blink(output, T_VERY_LONG, 0U);
}

void transition()
{
    for (uint8_t i = 0U; i < 3U; i++)
    {
        blink(GREEN_LED | YELLOW_LED, T_SHORT, T_SHORT);
        blink(BLUE_LED | RED_LED, T_SHORT, T_SHORT);
    }

    level++;

    if (level <= 4U)
    {
        n++;
    }
    else if (level <= 8U)
    {
        t *= 0.9;
    }
    else if (level <= 12U)
    {
        n++;
    }
    else
    {
        t *= 0.9;
    }
}

int main(void)
{
    init();

    enum
    {
        READY,
        PRESENT,
        REPEAT,
        LOOSE,
        TRANSITION,
        END
    } state = READY;

    enum color pattern[15] = {BLUE,   RED,  BLUE, GREEN,  RED,  RED, YELLOW, GREEN,
                              YELLOW, BLUE, RED,  YELLOW, BLUE, RED, GREEN};

    while (1)
    {
        switch (state)
        {
        case READY:
            if (ready())
            {
                state = PRESENT;
                level = 1;
                n = 3;
                t = T_LONG;
            }
            break;
        case PRESENT:
            present(pattern);
            state = REPEAT;
            break;
        case REPEAT:
            if (repeat(pattern))
            {
                state = TRANSITION;
            }
            else
            {
                state = LOOSE;
            }
            break;
        case LOOSE:
            loose();
            state = READY;
            break;
        case TRANSITION:
            transition();
            if (level < 16U)
            {
                state = PRESENT;
            }
            else
            {
                state = END;
            }
            break;
        case END:
            end();
            state = READY;
            break;
        default:
            break;
        }
    }
}
