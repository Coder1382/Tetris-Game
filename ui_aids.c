#include "tetris.h"
void initial_field(WINDOW *field, WINDOW *info, WINDOW *menu, GameInfo_t data) {
  wattron(info, COLOR_PAIR(10)), wattron(menu, COLOR_PAIR(10)),
      mvwprintw(info, 4, 1, "Score %d     ", data.score),
      mvwprintw(info, 5, 1, "Level %d ", data.level),
      mvwprintw(info, 10, 0, "READY TO START"),
      mvwprintw(menu, 4, 1, "Start - Enter"),
      mvwprintw(menu, 5, 1, "Quit - Esc"), wattroff(info, COLOR_PAIR(10)),
      wattroff(menu, COLOR_PAIR(10)), wattron(field, COLOR_PAIR(11)),
      box(field, 0, 0), wattroff(field, COLOR_PAIR(11));
}
void set_colors() {
  start_color();
  init_color(1, 686, 0, 0), init_color(2, 843, 300, 0),
      init_color(3, 843, 620, 0), init_color(4, 686, 0, 400),
      init_color(5, 0, 686, 0), init_color(6, 0, 0, 686),
      init_color(7, 700, 100, 700), init_color(0, 175, 225, 225),
      init_color(10, 1000, 1000, 1000), init_color(11, 170, 170, 170),
      init_pair(1, 11, 1), init_pair(2, 11, 2), init_pair(3, 11, 3),
      init_pair(4, 11, 4), init_pair(5, 11, 5), init_pair(6, 11, 6),
      init_pair(7, 11, 7), init_pair(0, 0, 0), init_pair(10, 10, 0),
      init_pair(11, 11, 11), init_pair(12, 11, 0);
}
void game_over(WINDOW *info, WINDOW *menu, GameInfo_t data, int over) {
  if (over == 0)
    wclear(menu), wattron(info, COLOR_PAIR(10)), wattron(menu, COLOR_PAIR(10)),
        mvwprintw(info, 10, 0, "GAME OVER       "),
        mvwprintw(info, 4, 1, "Score %d     ", data.score),
        mvwprintw(info, 5, 1, "Record %d     ",
                  data.score > data.high_score ? data.score : data.high_score),
        mvwprintw(info, 6, 1, "Level %d ", data.level),
        mvwprintw(menu, 4, 1, "Restart - Enter"),
        mvwprintw(menu, 5, 1, "Quit - Esc");
  wattroff(info, COLOR_PAIR(10)), wattroff(menu, COLOR_PAIR(10));
}
void game_running(WINDOW *info, WINDOW *menu, GameInfo_t data, int run) {
  static int stop;
  // if(run==0) wclear(menu);
  wattron(info, COLOR_PAIR(10)), wattron(menu, COLOR_PAIR(10));
  mvwprintw(info, 4, 1, "Score %d     ", data.score),
      mvwprintw(info, 5, 1, "Record %d     ",
                data.score > data.high_score ? data.score : data.high_score),
      mvwprintw(info, 6, 1, "Level %d ", data.level),
      mvwprintw(info, 7, 1, "Speed %.1fs  ", data.speed / 10.0);
  if (data.pause && stop == 0)
    wclear(menu), stop = 1, mvwprintw(info, 10, 0, "GAME ON PAUSE   "),
                  mvwprintw(menu, 4, 1, "Resume - Space\n"),
                  mvwprintw(menu, 5, 1, "Quit - Esc\n"), stop = 1;
  else if (data.pause == 0 && (stop || run == 0)) {
    stop ? stop = 0 : 0;
    wclear(menu);
    mvwprintw(info, 10, 0, "GAME IN PROGRESS"), mvwprintw(menu, 1, 5, "MENU"),
        mvwprintw(menu, 2, 1, "Left - LeftArrow"),
        mvwprintw(menu, 3, 1, "Right - RightArrow"),
        mvwprintw(menu, 4, 1, "Down - DownArrow"),
        mvwprintw(menu, 5, 1, "Rotate - UpArrow"),
        mvwprintw(menu, 6, 1, "Fall - hold DownArrow"),
        mvwprintw(menu, 7, 1, "Pause - Space"),
        mvwprintw(menu, 8, 1, "Quit - Esc");
  }
  wattroff(info, COLOR_PAIR(10)), wattron(menu, COLOR_PAIR(10));
}