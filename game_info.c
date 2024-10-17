#include "tetris.h"
GameInfo_t *updateCurrentState() {
  static int count, run, over;
  static GameInfo_t data;
  static WINDOW *field, *info, *menu;
  setlocale(LC_ALL, "");
  if (count == 0)
    initscr(), keypad(stdscr, true), cbreak(), noecho(), set_colors(),
        nodelay(stdscr, true),
        count = 1, srand(time(NULL)), field = newwin(22, 12, 0, 25),
        info = newwin(11, 25, 0, 39), menu = newwin(9, 25, 12, 39);
  else
    refresh(), wrefresh(field), wrefresh(info), wrefresh(menu);
  curs_set(0);
  if (data.speed == 0)
    initial_field(field, info, menu, data), run = over = 0;
  else if (data.speed > 0) {
    for (int i = 1; i < 3; i++)
      for (int j = 1; j < 11; j++)
        if (data.next.set[0][i][j])
          wattron(info, COLOR_PAIR(data.next.shape)),
              mvwprintw(info, i, j, "□"),
              wattroff(info, COLOR_PAIR(data.next.shape));
        else
          wattron(info, COLOR_PAIR(0)), mvwprintw(info, i, j, " "),
              wattroff(info, COLOR_PAIR(0));
    game_running(info, menu, data, run), run = 1, over = 0;
  } else if (data.speed < 0) {
    for (int i = 1; i < 3; i++)
      for (int j = 1; j < 11; j++)
        if (data.next.set[0][i][j])
          wattron(info, COLOR_PAIR(0)), mvwprintw(info, i, j, " "),
              wattroff(info, COLOR_PAIR(0));
    game_over(info, menu, data, over), over = 1, run = 0;
  }
  wattron(field, COLOR_PAIR(11)), box(field, 0, 0),
      wattroff(field, COLOR_PAIR(11));
  for (int y = 1; y < 21; y++)
    for (int x = 1; x < 11; x++)
      if (data.field[y][x])
        wattron(field, COLOR_PAIR(data.field[y][x])),
            mvwprintw(field, y, x, "□"),
            wattroff(field, COLOR_PAIR(data.field[y][x]));
      else if (data.brick.set[data.brick.pos][y][x])
        wattron(field, COLOR_PAIR(data.brick.shape)),
            mvwprintw(field, y, x, "□"),
            wattroff(field, COLOR_PAIR(data.brick.shape));
      else
        wattron(field, COLOR_PAIR(0)), mvwprintw(field, y, x, " "),
            wattroff(field, COLOR_PAIR(0));
  return &data;
}