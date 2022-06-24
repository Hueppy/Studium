#include "encoding.h"
#include "platform.h"
#include "startup.h"
#include "wrap.h"

#include "FreeRTOS.h"

#include "framebuffer.h"
#include "pong.h"

#define PIN_MASK(offset) (1U << (offset))
#define PLIC_PIN_MASK(offset) (1U << (8U + (offset)))

#define BTN_LEFT_UP PIN_2_OFFSET
#define BTN_LEFT_DOWN PIN_3_OFFSET
#define BTN_RIGHT_UP PIN_5_OFFSET
#define BTN_RIGHT_DOWN PIN_4_OFFSET

#define BTN_MASK (PIN_MASK(BTN_LEFT_UP) | PIN_MASK(BTN_LEFT_DOWN) | PIN_MASK(BTN_RIGHT_UP) | PIN_MASK(BTN_RIGHT_DOWN))

game g;
SemaphoreHandle_t semaphore_left_up;
SemaphoreHandle_t semaphore_left_down;
SemaphoreHandle_t semaphore_right_up;
SemaphoreHandle_t semaphore_right_down;

void handle_m_ext_interrupt() {
	uint32_t nb = PLIC_REG(PLIC_CLAIM_OFFSET);

    uint32_t gpio_interrupts = ~GPIO_REG(GPIO_RISE_IP) & BTN_MASK;

    BaseType_t woken;
    
    if ((gpio_interrupts & PIN_MASK(BTN_LEFT_UP)) > 0U) {
        xSemaphoreGiveFromISR(semaphore_left_up, &woken);
    }
    if ((gpio_interrupts & PIN_MASK(BTN_LEFT_DOWN)) > 0U) {
        xSemaphoreGiveFromISR(semaphore_left_down, &woken);
    }
    if ((gpio_interrupts & PIN_MASK(BTN_RIGHT_UP)) > 0U) {
        xSemaphoreGiveFromISR(semaphore_right_up, &woken);
    }
    if ((gpio_interrupts & PIN_MASK(BTN_RIGHT_DOWN)) > 0U) {
        xSemaphoreGiveFromISR(semaphore_right_down, &woken);
    }

    GPIO_REG(GPIO_RISE_IP) |= gpio_interrupts;

    PLIC_REG(PLIC_CLAIM_OFFSET) = nb;    
    portYIELD_FROM_ISR(woken);
}

void gpio_init() {
	// setup button as input
	GPIO_REG(GPIO_IOF_EN) &= ~BTN_MASK;
	GPIO_REG(GPIO_OUTPUT_EN) &= ~BTN_MASK;
	GPIO_REG(GPIO_OUTPUT_VAL) &= ~BTN_MASK;
	GPIO_REG(GPIO_INPUT_EN) |= BTN_MASK;
	GPIO_REG(GPIO_PULLUP_EN) |= BTN_MASK;
}

void irq_init() {
    PLIC_REG(PLIC_ENABLE_OFFSET) = 0;
    PLIC_REG(PLIC_THRESHOLD_OFFSET) = 0;

    PLIC_REG(PLIC_ENABLE_OFFSET) |=
        PLIC_PIN_MASK(BTN_LEFT_UP) |
        PLIC_PIN_MASK(BTN_LEFT_DOWN) |
        PLIC_PIN_MASK(BTN_RIGHT_UP) |
        PLIC_PIN_MASK(BTN_RIGHT_DOWN);

    PLIC_REG(4 * (8 + BTN_LEFT_UP)) = 7;
    PLIC_REG(4 * (8 + BTN_LEFT_DOWN)) = 7;
    PLIC_REG(4 * (8 + BTN_RIGHT_UP)) = 7;
    PLIC_REG(4 * (8 + BTN_RIGHT_DOWN)) = 7;

    GPIO_REG(GPIO_RISE_IE) |= BTN_MASK;
    GPIO_REG(GPIO_RISE_IP) |= BTN_MASK;
}

void task_draw(void* parameter) {
    void* _ = parameter;

    framebuffer fb;
    fb_init(&fb);

    TickType_t wake_time = xTaskGetTickCount();
    
    while (true) {
        fb_clear(&fb);
        game_draw(&g, &fb);
        fb_paint(&fb);

        vTaskDelayUntil(&wake_time, pdMS_TO_TICKS(30));
    }
}

void task_update_ball(void* parameter) {
    void* _ = parameter;

    TickType_t wake_time = xTaskGetTickCount();
    
    while (true) {
        ball_update(&g.ball);
        vTaskDelayUntil(&wake_time, pdMS_TO_TICKS(30));
    }
}

typedef struct {
    paddle* paddle;
    direction direction;
    SemaphoreHandle_t semaphore;
} move_paddle_parameter;

void task_move_paddle(move_paddle_parameter* parameter) {
    move_paddle_parameter para = *parameter;

    while (true) {
        if (xSemaphoreTake(para.semaphore, portMAX_DELAY) == pdTRUE) {
            paddle_move(para.paddle, para.direction);
        }
    }
}

int main(void) {
    gpio_init();
    irq_init();
    
    oled_init();
    
    game_init(&g);

    semaphore_left_up = xSemaphoreCreateBinary();
    semaphore_left_down = xSemaphoreCreateBinary();
    semaphore_right_up = xSemaphoreCreateBinary();
    semaphore_right_down = xSemaphoreCreateBinary();

    move_paddle_parameter left_up = {
        .paddle = &g.left,
        .direction = UP,
        .semaphore = semaphore_left_up
    };
    move_paddle_parameter left_down = {
        .paddle = &g.left,
        .direction = DOWN,
        .semaphore = semaphore_left_down
    };
    move_paddle_parameter right_up = {
        .paddle = &g.right,
        .direction = UP,
        .semaphore = semaphore_right_up
    };
    move_paddle_parameter right_down = {
        .paddle = &g.right,
        .direction = DOWN,
        .semaphore = semaphore_right_down
    };

    xTaskCreate(task_draw, "draw", 400, NULL, 2, NULL);
    xTaskCreate(task_move_paddle, "lu", 100, &left_up, 2, NULL);
    xTaskCreate(task_move_paddle, "ld", 100, &left_down, 2, NULL);
	xTaskCreate(task_move_paddle, "paddle_move_right_up", 100, &right_up, 2, NULL);
	xTaskCreate(task_move_paddle, "paddle_move_right_down", 200, &right_down, 2, NULL);
    xTaskCreate(task_update_ball, "update_ball", 300, NULL, 2, NULL);
    
    vTaskStartScheduler();

    return 0;
}
