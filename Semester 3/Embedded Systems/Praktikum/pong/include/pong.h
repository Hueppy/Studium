#ifndef PONG_H
#define PONG_H

#include "platform.h"
#include "framebuffer.h"
#include "stdbool.h"

#define PADDLE_WIDTH 4
#define PADDLE_HEIGHT 16
#define PADDLE_PADDING 8

#define BALL_WIDTH 4
#define BALL_HEIGHT 4

typedef struct {
    int16_t x;
    int16_t y;
} vector;

typedef enum {
    LEFT,
    RIGHT
} side;

typedef enum {
    UP,
    DOWN
} direction;

struct game;

typedef struct {
    int8_t y;
    side side;
    SemaphoreHandle_t mutex;
} paddle;

typedef struct {
    vector position;
    vector movement;
    struct game* game;
    SemaphoreHandle_t mutex;
} ball;

typedef struct game {
    paddle left;
    paddle right;
    ball ball;
    uint8_t points_left;
    uint8_t points_right;
    SemaphoreHandle_t mutex;
} game;

void vector_add(vector* lhs, vector* rhs);

void paddle_init(paddle* p, side s);
void paddle_reset(paddle* p);
void paddle_move(paddle* p, direction d);
void paddle_draw(paddle* p, framebuffer* fb);

void ball_init(ball* b, game* g);
void ball_reset(ball* b, side s);
void ball_update(ball *b);
void ball_draw(ball* b, framebuffer* fb);

void game_init(game* g);
void game_reset(game* g);
void game_score(game* g, side s);
void game_draw(game* g, framebuffer* fb);

#endif
