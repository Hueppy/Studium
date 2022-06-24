#include "pong.h"

char* score_to_string(uint8_t i, char buffer[4]) {
    char *result = buffer;
    buffer[3] = '\0';

    buffer[2] = (uint8_t)'0' + (i % 10U);
    if (i >= 10U) {
        buffer[1] = (uint8_t)'0' + ((i / 10U) % 10U);
        if (i >= 100U) {
            buffer[0] = (uint8_t)'0' + (i / 100U);
        } else {
            result = &buffer[1];
        }
    } else {
        result = &buffer[2];
    }

    return result;
}

void vector_add(vector* lhs, vector* rhs) {
    lhs->x += rhs->x;
    lhs->y += rhs->y;
}

void paddle_init(paddle* p, side s) {
    p->side = s;
    p->mutex = xSemaphoreCreateMutex();
    paddle_reset(p);
}

void paddle_reset(paddle* p) {
    if (xSemaphoreTake(p->mutex, portMAX_DELAY) == pdTRUE) {
        p->y = (DISP_H / 2);
        xSemaphoreGive(p->mutex);
    }
}

void paddle_move(paddle* p, direction d) {
    if (xSemaphoreTake(p->mutex, portMAX_DELAY) == pdTRUE) {
        if (d == UP) {
            p->y--;
            if (p->y < (PADDLE_HEIGHT / 2)) {
                p->y = PADDLE_HEIGHT / 2;
            }
        } else {
            p->y++;
            if (p->y >= (DISP_H - (PADDLE_HEIGHT / 2))) {
                p->y = DISP_H - (PADDLE_HEIGHT / 2);
            }
        }
        xSemaphoreGive(p->mutex);
    }
}

void paddle_draw(paddle* p, framebuffer* fb) {
    if (xSemaphoreTake(p->mutex, portMAX_DELAY) == pdTRUE) {
        fb_draw_rectangle(fb,
                          (p->side == LEFT) ? PADDLE_PADDING : ((DISP_W - PADDLE_PADDING) - PADDLE_WIDTH),
                          (p->y - (PADDLE_HEIGHT / 2)),
                          PADDLE_WIDTH,
                          PADDLE_HEIGHT);
        xSemaphoreGive(p->mutex);
  }
}

void ball_init(ball* b, game* g) {
    b->game = g;
    b->mutex = xSemaphoreCreateRecursiveMutex();
    ball_reset(b, LEFT);
}

void ball_reset(ball* b, side s) {
    if (xSemaphoreTakeRecursive(b->mutex, portMAX_DELAY) == pdTRUE) {
        b->position.x = DISP_W / 2;
        b->position.y = DISP_H / 2;
        b->movement.x = (s == LEFT) ? -1 : 1;
        b->movement.y = 0;
        xSemaphoreGive(b->mutex);
    }
}

void ball_update(ball* b) {
    if (xSemaphoreTake(b->mutex, portMAX_DELAY) == pdTRUE) {
        vector_add(&b->position, &b->movement);
        if ((b->position.y < (BALL_HEIGHT / 2)) || (b->position.y >= (DISP_H - (BALL_HEIGHT / 2)))) {
            b->movement.y = -b->movement.y;
            b->position.y += b->movement.y;
        }

        const int8_t paddle_distance = PADDLE_PADDING + PADDLE_WIDTH;
        
        int16_t left_x = b->position.x - (BALL_WIDTH / 2);
        int16_t right_x = b->position.x + (BALL_WIDTH / 2);

        if (left_x < paddle_distance) {
            // left side collision check
            if (left_x < 0) {
                game_score(b->game, RIGHT);
            } else if (left_x > PADDLE_PADDING) {
                int8_t d = b->position.y - b->game->left.y;
                if ((d + (BALL_HEIGHT / 2)) > -(PADDLE_HEIGHT / 2) &&
                    (d - (BALL_HEIGHT / 2)) < (PADDLE_HEIGHT / 2)) {
                    b->movement.x = -b->movement.x;
                    b->movement.y = 4 * d / PADDLE_HEIGHT;
                }
            } else {

            }
        } else if (right_x >= (DISP_W - paddle_distance)) {
            // right side collision check
            if (right_x >= DISP_W) {
                game_score(b->game, LEFT);
            } else if (right_x <= (DISP_W - PADDLE_PADDING)) {
                int8_t d = b->position.y - b->game->right.y;
                if ((d + (BALL_HEIGHT / 2)) > -(PADDLE_HEIGHT / 2) &&
                    (d - (BALL_HEIGHT / 2)) < (PADDLE_HEIGHT / 2)) {
                    b->movement.x = -b->movement.x;
                    b->movement.y = 4.0 * d / PADDLE_HEIGHT;
                }
            } else {

            }
        } else {

        }
        xSemaphoreGive(b->mutex);
    }
}

void ball_draw(ball* b, framebuffer* fb) {
  if (xSemaphoreTake(b->mutex, portMAX_DELAY) == pdTRUE) {
      fb_draw_rectangle(fb,
                        b->position.x - (BALL_WIDTH / 2),
                        b->position.y - (BALL_HEIGHT / 2),
                        BALL_WIDTH,
                        BALL_HEIGHT);
      xSemaphoreGive(b->mutex);
  }
}

void game_init(game* g) {
    paddle_init(&g->left, LEFT);
    paddle_init(&g->right, RIGHT);
    ball_init(&g->ball, g);
    g->mutex = xSemaphoreCreateMutex();
}

void game_reset(game* g) {
    if (xSemaphoreTake(g->mutex, portMAX_DELAY) == pdTRUE) {
        ball_reset(&g->ball, LEFT);
        paddle_reset(&g->left);
        paddle_reset(&g->right);
        g->points_left = 0;
        g->points_right = 0;
        xSemaphoreGive(g->mutex);
    }
}

void game_score(game* g, side s) {
    if (xSemaphoreTake(g->mutex, portMAX_DELAY) == pdTRUE) {
        if (s == LEFT) {
            g->points_left++;
        } else {
            g->points_right++;
        }
        
        ball_reset(&g->ball, (s == LEFT) ? RIGHT : LEFT);
        paddle_reset(&g->left);
        paddle_reset(&g->right);

        xSemaphoreGive(g->mutex);
    }
}

void game_draw(game* g, framebuffer* fb) {
    if (xSemaphoreTake(g->mutex, portMAX_DELAY) == pdTRUE) {
        paddle_draw(&g->left, fb);
        paddle_draw(&g->right, fb);
        ball_draw(&g->ball, fb);

        char score_buffer[4];
        char* score = score_to_string(g->points_left, score_buffer);
        fb_print(fb, score, 1, (DISP_W / 2) - 5, RIGHT_TO_LEFT);
        score = score_to_string(g->points_right, score_buffer);
        fb_print(fb, score, 1, (DISP_W / 2) + 5, LEFT_TO_RIGHT);

        xSemaphoreGive(g->mutex);
    }
}
