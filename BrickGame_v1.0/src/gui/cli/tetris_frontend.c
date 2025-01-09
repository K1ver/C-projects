#include "tetris_frontend.h"

void printGameOverTetris(int result) {
  MVPRINTW(0, 20, "TETRIS");
  if (result == 1) {
    MVPRINTW(4, 18, "YOU WIN");
  } else {
    MVPRINTW(4, 18, "GAME OVER");
  }
  MVPRINTW(5, 15, "Press R to restart");
  MVPRINTW(6, 15, "Press Q to exit");
}

void printField(GameInfo_t *gameInfo, Figure_t *nextFigure) {
  MVPRINTW(0, 20, "TETRIS");
  MVPRINTW(2, 25, "Score: %d", gameInfo->score);
  MVPRINTW(3, 25, "High score: %d", gameInfo->high_score);
  MVPRINTW(4, 25, "Level: %d", gameInfo->level);
  MVPRINTW(5, 25, "Speed: %d", gameInfo->speed);
  MVPRINTW(6, 25, "Next: ");
  for (int i = 0; i < nextFigure->size; i++) {
    for (int j = 0; j < nextFigure->size; j++) {
      if (nextFigure->figureMatrix[i][j] == 0) {
        MVPRINTW(i + 7, j * 2 + 25, "  ");
      } else if (nextFigure->figureMatrix[i][j] == 1) {
        MVPRINTW(i + 7, j * 2 + 25, "# ");
      }
    }
  }
  for (int i = 0; i < ROWS_MAP; i++) {
    for (int j = 0; j < COLS_MAP; j++) {
      if (gameInfo->field[i][j] == 0) {
        MVPRINTW(i + 2, j * 2, "  ");
      } else if (gameInfo->field[i][j] == 1) {
        MVPRINTW(i + 2, j * 2, "# ");
      } else if (gameInfo->field[i][j] == 2) {
        MVPRINTW(i + 2, j * 2, "@ ");
      }
    }
  }

  if (gameInfo->pause) {
    MVPRINTW(11, 27, "PAUSE");
    MVPRINTW(12, 23, "Press R to continue");
    MVPRINTW(13, 23, "Press Q to exit");
  }
}

void printMenuTetris() {
  MVPRINTW(0, 20, "TETRIS");
  MVPRINTW(4, 15, "Press R to start");
  MVPRINTW(5, 15, "Press Q to exit");
}
