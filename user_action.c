#include "tetris.h"

void userInput(UserAction_t input, int hold) {
  GameInfo_t *data = NULL;
  static double stop, hault, temp;
  static int fall;
  FILE *f = NULL;
  wchar_t key = input;
  data = updateCurrentState();
  if (data->speed > 0 && key == Pause)
    data->pause ? (data->pause = 0) : (data->pause = 1);
  else if (data->speed > 0 && data->pause == 0) {
    if (key == Left)
      move_left(data);
    else if (key == Right)
      move_right(data);
    else if (key == Down)
      move_down(data, hold, &fall);
    else if (key == Action)
      data->brick.pos = (data->brick.pos > 2 ? 0 : data->brick.pos + 1);
  } else if (data->speed <= 0 && key == Start) {
    data->score = data->pause = 0, data->level = 1, data->speed = 12,
    temp = hault = 0, hold = fall = 0,
    stop = ((double)clock()) + CLOCKS_PER_SEC * data->speed / 10.0;
    (f = fopen("max_score.txt", "r")) == NULL ||
            fscanf(f, "%d", &data->high_score) == -1
        ? data->high_score = 0
        : 0;
    f ? fclose(f), f = NULL : 0;
    for (int y = 0; y < 22; y++)
      for (int x = 0; x < 12; data->field[y][x] = 0, x++)
        ;
    flushinp(), new_brick(&data->brick), new_brick(&data->next);
  }
  if (data->speed > 0 && data->pause == 0) {
    if (((double)clock()) >= stop)
      move_down(data, 0, &fall),
          stop = ((double)clock()) + CLOCKS_PER_SEC * data->speed / 10.0;
    if (data->speed > 0) remove_filled(data);
  }
  if (data->speed > 0 && data->score >= data->high_score){
    (f = fopen("max_score.txt", "w")) ? fprintf(f, "%d", data->score), fclose(f), f = NULL : 0;
    data->high_score=data->score;
  }
  trim_top(data);
  if (key == Terminate) {
    if (data->score >= data->high_score)
      (f = fopen("max_score.txt", "w")) ? fprintf(f, "%d", data->score),
          fclose(f), f = NULL : 0;
    endwin();
    return;
  }
  key = input = getch();
  if (fall) {
    if (temp == 0 || (key == Down && (double)clock() <= temp))
      (hault = hold = 0, input = '\0',
       temp = ((double)clock()) + CLOCKS_PER_SEC / 10.0);
    if ((double)clock() > temp) fall = 0, temp = 0;
  }
  if (fall == 0) {
    if (key == Down)
      hold = ((double)clock() < hault ? 1 : 0),
      hault = ((double)clock()) + 0.05 * CLOCKS_PER_SEC;
    else if (key != ERR)
      hault = 0, hold = 0;
  }
  hold = (data->speed > 0 && data->pause == 0 && fall == 0 && hold ? 1 : 0),
  data = NULL;
  userInput(input, hold);
}
