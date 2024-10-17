#ifndef TETRIS_H
#define TETRIS_H
#include <check.h>
#include <fcntl.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uchar.h>
#include <unistd.h>
#include <wchar.h>
typedef enum {
  Start = 10, Pause = 32, Terminate = 27,
  Left = KEY_LEFT, Right = KEY_RIGHT,
  Down = KEY_DOWN, Action = KEY_UP
} UserAction_t;
typedef struct {
  int set[4][22][12];
  int shape, pos;
} brick_t;
typedef struct {
  int field[22][12], score, high_score, level, pause, speed;
  brick_t brick, next;
} GameInfo_t;
void move_left(GameInfo_t *);
void move_right(GameInfo_t *);
void move_down(GameInfo_t *, int, int *);
void downshift(GameInfo_t *);
void remove_filled(GameInfo_t *);
void trim_top(GameInfo_t *);
void set_colors();
void game_over(WINDOW *, WINDOW *, GameInfo_t, int);
void new_brick(brick_t *);
void initial_field(WINDOW *, WINDOW *, WINDOW *, GameInfo_t);
void game_running(WINDOW *, WINDOW *, GameInfo_t, int);
void userInput(UserAction_t, int);
GameInfo_t *updateCurrentState();
#endif
