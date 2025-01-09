#include "tetris.h"

int main(void) {
  game_loop();
  return 0;
}

void game_loop() {
  WIN_INIT(50);
  endwin();
  int row, col;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 2);
  UserAction_t action;
  printMenuTetris();
  refresh();
  while (action != Action) {
    updateUserAction(&action);
  }
  TetrisState_t *state = getTetrisState(NULL);
  while (*state != EXIT) {
    userInput(action, 1);
    updateUserAction(&action);
  }
}
