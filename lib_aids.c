#include "tetris.h"

void move_left(GameInfo_t *data) {
  int x = 0, i = 0, j = 0;
  for (x = 0; x < 4; x++) {
    for (i = 1; i < 21; i++) {
      for (j = 10; j > 1; j--)
        if (data->brick.set[x][i][j] && data->field[i][j - 1]) j = 1, i = 21;
      j == 1 && data->brick.set[x][i][1] ? i = 21 : 0;
    }
    if (i == 21)
      for (i = 1; i < 21; i++)
        for (j = 2; j < 11; j++)
          data->brick.set[x][i][j - 1] = data->brick.set[x][i][j],
                                    data->brick.set[x][i][j] = 0;
  }
}
void move_right(GameInfo_t *data) {
  int x = 0, i = 0, j = 0;
  for (x = 0; x < 4; x++) {
    for (i = 1; i < 21; i++) {
      for (j = 1; j < 10; j++)
        if (data->brick.set[x][i][j] && data->field[i][j + 1]) j = 10, i = 21;
      j == 10 && data->brick.set[x][i][10] ? i = 21 : 0;
    }
    if (i == 21)
      for (i = 1; i < 21; i++)
        for (j = 9; j > 0; j--)
          data->brick.set[x][i][j + 1] = data->brick.set[x][i][j],
                                    data->brick.set[x][i][j] = 0;
  }
}
void move_down(GameInfo_t *data, int hold, int *fall) {
  int x = 0, y = 0, i = 0, j = 0, temp = 1;
  for (hold ? temp = 20 : 0; temp; temp--) {
    for (i = 20; i > 0; i--)
      for (j = 1; j < 11; j++)
        if (data->brick.set[data->brick.pos][i][j] &&
            (i == 20 || data->field[i + 1][j])) {
          i = 0, j = 11;
          for (x = 1; x < 11; x++)
            data->brick.set[data->brick.pos][1][x]                    ? x = 11,
                                                     data->speed = -1 : 0;
          if (data->speed > 0) {
            for (y = 1; y < 21; y++)
              for (x = 1; x < 11; x++)
                data->brick.set[data->brick.pos][y][x]
                    ? data->field[y][x] = data->brick.shape
                    : 0;
            flushinp(), data->brick = data->next, new_brick(&data->next),
                        temp = 1, *fall = 1;
          }
        }
    if (i == 0) downshift(data);
  }
}
void downshift(GameInfo_t *data) {
  int x = 0, i = 0, j = 0;
  for (x = 0; x < 4; x++) {
    for (j = 1; j < 11 && data->brick.set[x][20][j] == 0; j++)
      ;
    if (j == 11) {
      for (i = 1; i < 20; i++)
        for (j = 1; j < 11; j++)
          if (data->brick.set[x][i][j] && data->field[i + 1][j]) j = 11, i = 20;
      if (i == 20)
        for (i = 19; i > 0; i--)
          for (j = 1; j < 11; j++)
            data->brick.set[x][i + 1][j] = data->brick.set[x][i][j],
                                   data->brick.set[x][i][j] = 0;
    }
  }
}
void remove_filled(GameInfo_t *data) {
  int x = 0, y = 0, i = 0, j = 0, temp = 0;
  for (y = 20; y > 0; y--) {
    for (x = 1; x < 11 && data->field[y][x]; x++)
      ;
    if (x == 11) {
      for (x = 1, temp++; x < 11; data->field[y][x] = 0, x++)
        ;
      for (i = y - 1, y = 21; i > 0; i--)
        for (j = 1; j < 11; j++)
          data->field[i + 1][j] = data->field[i][j], data->field[i][j] = 0;
    }
  }
  temp = (temp == 1   ? 100
          : temp == 2 ? 300
          : temp == 3 ? 700
          : temp > 3  ? 1500
                      : 0);
  data->level += (temp / 600), data->speed -= (temp / 600);
  if ((data->score % 600 + temp % 600) >= 600) data->level++, data->speed--;
  data->level > 10 ? data->level = 10 : 0,
                     data->speed < 3 ? data->speed = 3 : 0, data->score += temp;
}
void trim_top(GameInfo_t *data) {
  int temp = 1, i = 0, j = 0;
  while (temp) {
    for (i = 20; i > 0; i--)
      for (j = 1; j < 11; j++)
        data->brick.set[data->brick.pos][i][j] && data->field[i][j] ? j = 11,
                                                                      i = 0 : 0;
    if (i == -1)
      for (i = 0; i < 20; i++)
        for (j = 1; j < 11; j++)
          data->brick.set[data->brick.pos][i][j] =
              data->brick.set[data->brick.pos][i + 1][j],
          data->brick.set[data->brick.pos][i + 1][j] = 0;
    else
      temp = 0;
  }
}
void new_brick(brick_t *brick) {
  brick->pos = 0, brick->shape = rand() % 7 + 1;
  for (int v = 0; v < 4; v++)
    for (int i = 0; i < 22; i++)
      for (int j = 0; j < 12; brick->set[v][i][j] = 0, j++)
        ;
  if (brick->shape == 1)
    brick->set[0][1][4] = brick->set[0][1][5] = brick->set[0][1][6] =
        brick->set[0][1][7] = brick->set[1][1][5] = brick->set[1][2][5] =
            brick->set[1][3][5] = brick->set[1][4][5] = brick->set[2][1][4] =
                brick->set[2][1][5] = brick->set[2][1][6] =
                    brick->set[2][1][7] = brick->set[3][1][5] =
                        brick->set[3][2][5] = brick->set[3][3][5] =
                            brick->set[3][4][5] = 1;
  else if (brick->shape == 2)
    brick->set[0][1][5] = brick->set[0][2][5] = brick->set[0][2][6] =
        brick->set[0][2][7] = brick->set[1][1][5] = brick->set[1][1][6] =
            brick->set[1][2][5] = brick->set[1][3][5] = brick->set[2][1][5] =
                brick->set[2][1][6] = brick->set[2][1][7] =
                    brick->set[2][2][7] = brick->set[3][1][6] =
                        brick->set[3][2][6] = brick->set[3][3][5] =
                            brick->set[3][3][6] = 1;
  else if (brick->shape == 3)
    brick->set[0][1][7] = brick->set[0][2][5] = brick->set[0][2][6] =
        brick->set[0][2][7] = brick->set[1][1][5] = brick->set[1][2][5] =
            brick->set[1][3][5] = brick->set[1][3][6] = brick->set[2][1][5] =
                brick->set[2][1][6] = brick->set[2][1][7] =
                    brick->set[2][2][5] = brick->set[3][1][5] =
                        brick->set[3][1][6] = brick->set[3][2][6] =
                            brick->set[3][3][6] = 1;
  else if (brick->shape == 4)
    brick->set[0][1][5] = brick->set[0][1][6] = brick->set[0][2][5] =
        brick->set[0][2][6] = brick->set[1][1][5] = brick->set[1][1][6] =
            brick->set[1][2][5] = brick->set[1][2][6] = brick->set[2][1][5] =
                brick->set[2][1][6] = brick->set[2][2][5] =
                    brick->set[2][2][6] = brick->set[3][1][5] =
                        brick->set[3][1][6] = brick->set[3][2][5] =
                            brick->set[3][2][6] = 1;
  else if (brick->shape == 5)
    brick->set[0][1][6] = brick->set[0][1][7] = brick->set[0][2][5] =
        brick->set[0][2][6] = brick->set[1][1][5] = brick->set[1][2][5] =
            brick->set[1][2][6] = brick->set[1][3][6] = brick->set[2][1][6] =
                brick->set[2][1][7] = brick->set[2][2][5] =
                    brick->set[2][2][6] = brick->set[3][1][5] =
                        brick->set[3][2][5] = brick->set[3][2][6] =
                            brick->set[3][3][6] = 1;
  else if (brick->shape == 6)
    brick->set[0][1][6] = brick->set[0][2][5] = brick->set[0][2][6] =
        brick->set[0][2][7] = brick->set[1][1][6] = brick->set[1][2][6] =
            brick->set[1][2][7] = brick->set[1][3][6] = brick->set[2][1][5] =
                brick->set[2][1][6] = brick->set[2][1][7] =
                    brick->set[2][2][6] = brick->set[3][1][7] =
                        brick->set[3][2][6] = brick->set[3][2][7] =
                            brick->set[3][3][7] = 1;
  else
    brick->set[0][1][5] = brick->set[0][1][6] = brick->set[0][2][6] =
        brick->set[0][2][7] = brick->set[1][1][6] = brick->set[1][2][5] =
            brick->set[1][2][6] = brick->set[1][3][5] = brick->set[2][1][5] =
                brick->set[2][1][6] = brick->set[2][2][6] =
                    brick->set[2][2][7] = brick->set[3][1][6] =
                        brick->set[3][2][5] = brick->set[3][2][6] =
                            brick->set[3][3][5] = 1;
}
