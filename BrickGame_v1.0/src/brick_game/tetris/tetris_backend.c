#include "tetris_backend.h"

/**
 * Initializes the game information structure with default values.
 *
 * @param gameInfo A pointer to the GameInfo_t structure to be initialized.
 *
 * This function sets up the game information structure with initial values for
 * the game field, next figure, score, level, speed, and pause state. It also
 * reads the high score from a file and stores it in the gameInfo structure.
 *
 * @return None
 */
void initGameInfo(GameInfo_t* gameInfo) {
  gameInfo->field = initMatrix(COLS_MAP, ROWS_MAP);
  gameInfo->next = initMatrix(4, 4);
  gameInfo->score = 0;
  gameInfo->level = 0;
  gameInfo->speed = 1;
  gameInfo->pause = 0;
  FILE* fp = fopen("../brick_game/tetris/score/high_score.txt", "r");
  fscanf(fp, "%d", &gameInfo->high_score);
  fclose(fp);
}

void writeHighScore(int score) {
  FILE* fp = fopen("../brick_game/tetris/score/high_score.txt", "w");
  fprintf(fp, "%d", score);
  fclose(fp);
}

int** initMatrix(int col, int row) {
  int** matrix = malloc(row * sizeof(int*));
  for (int i = 0; i < row; i++) {
    matrix[i] = malloc(col * sizeof(int));
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

void rotateFigureOn90Degrees(int** figure, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int temp = figure[i][j];
      figure[i][j] = figure[j][i];
      figure[j][i] = temp;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n / 2; j++) {
      int temp = figure[i][j];
      figure[i][j] = figure[i][n - 1 - j];
      figure[i][n - 1 - j] = temp;
    }
  }
}

void rotateFigureOn270Degrees(int** figure, int n) {
  for (int i = 0; i < 3; i++) {
    rotateFigureOn90Degrees(figure, n);
  }
}

void fillEdgesField(int** field) {
  for (int i = 0; i < ROWS_MAP; i++) {
    field[i][0] = 2;
    field[i][COLS_MAP - 1] = 2;
  }

  for (int i = 1; i < COLS_MAP - 1; i++) {
    field[0][i] = 2;
    field[ROWS_MAP - 1][i] = 2;
  }
}

void fillField(int** field, Figure_t* figure) {
  fillEdgesField(field);
  for (int y = figure->y, i = 0; i < figure->size; i++, y++) {
    for (int x = figure->x, j = 0; j < figure->size; j++, x++) {
      if (figure->figureMatrix[i][j] == 1) {
        field[y][x] = 1;
      }
    }
  }
}

/**
 * Resets the game information to its initial state.
 *
 * @param gameInfo A pointer to the GameInfo_t structure to be cleared.
 *
 * @return None
 */

void clearInfo(GameInfo_t* gameInfo) {
  gameInfo->level = 0;
  gameInfo->score = 0;
  gameInfo->speed = 1;
  for (int i = 0; i < ROWS_MAP; i++) {
    for (int j = 0; j < COLS_MAP; j++) {
      gameInfo->field[i][j] = 0;
    }
  }
}

/**
 * Initializes a Figure_t structure with a random type and corresponding figure matrix.
 *
 * The function sets the type of the figure to a random number between 0 and 6, 
 * and then initializes the figure matrix based on the type. The figure's rotation state is set to 'first', 
 * and its position is set to (4, 1).
 *
 * @param figure A pointer to the Figure_t structure to be initialized.
 *
 * @return None
 */
void initFigure(Figure_t* figure) {
  srand(time(NULL));
  figure->type = rand() % 7;
  ;
  figure->rotationState = first;
  figure->x = 4;
  figure->y = 1;
  switch (figure->type) {
    case 0:
      figure->size = 4;
      figure->figureMatrix = initMatrix(figure->size, figure->size);
      int I[4][4] = {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
      for (int i = 0; i < figure->size; i++) {
        for (int j = 0; j < figure->size; j++) {
          figure->figureMatrix[i][j] = I[i][j];
        }
      }
      break;
    case 1:
      figure->size = 2;
      figure->figureMatrix = initMatrix(figure->size, figure->size);
      int O[2][2] = {{1, 1}, {1, 1}};
      for (int i = 0; i < figure->size; i++) {
        for (int j = 0; j < figure->size; j++) {
          figure->figureMatrix[i][j] = O[i][j];
        }
      }
      break;
    case 2:
      figure->size = 3;
      figure->figureMatrix = initMatrix(figure->size, figure->size);
      int T[3][3] = {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}};
      for (int i = 0; i < figure->size; i++) {
        for (int j = 0; j < figure->size; j++) {
          figure->figureMatrix[i][j] = T[i][j];
        }
      }
      break;
    case 3:
      figure->size = 3;
      figure->figureMatrix = initMatrix(figure->size, figure->size);
      int L[3][3] = {{0, 1, 0}, {0, 1, 0}, {0, 1, 1}};
      for (int i = 0; i < figure->size; i++) {
        for (int j = 0; j < figure->size; j++) {
          figure->figureMatrix[i][j] = L[i][j];
        }
      }
      break;
    case 4:
      figure->size = 3;
      figure->figureMatrix = initMatrix(figure->size, figure->size);
      int J[3][3] = {{0, 1, 0}, {0, 1, 0}, {1, 1, 0}};
      for (int i = 0; i < figure->size; i++) {
        for (int j = 0; j < figure->size; j++) {
          figure->figureMatrix[i][j] = J[i][j];
        }
      }
      break;
    case 5:
      figure->size = 3;
      figure->figureMatrix = initMatrix(figure->size, figure->size);
      int Z[3][3] = {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}};
      for (int i = 0; i < figure->size; i++) {
        for (int j = 0; j < figure->size; j++) {
          figure->figureMatrix[i][j] = Z[i][j];
        }
      }
      break;
    case 6:
      figure->size = 3;
      figure->figureMatrix = initMatrix(figure->size, figure->size);
      int S[3][3] = {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}};
      for (int i = 0; i < figure->size; i++) {
        for (int j = 0; j < figure->size; j++) {
          figure->figureMatrix[i][j] = S[i][j];
        }
      }
  }
}

/**
 * Copies the properties of a source Figure_t object to a destination Figure_t object.
 *
 * @param destination Pointer to the destination Figure_t object.
 * @param source Pointer to the source Figure_t object.
 *
 * @return None.
 *
 * @throws None.
 */
void copyFigure(Figure_t* destination, Figure_t* source) {
  destination->type = source->type;
  destination->rotationState = source->rotationState;
  destination->x = source->x;
  destination->y = source->y;
  destination->size = source->size;
  destination->figureMatrix = initMatrix(source->size, source->size);
  for (int i = 0; i < destination->size; i++) {
    for (int j = 0; j < destination->size; j++) {
      destination->figureMatrix[i][j] = source->figureMatrix[i][j];
    }
  }
}

/**
 * Checks if a block can be spawned at the current position in the game field.
 *
 * @param gameInfo Pointer to the game information structure.
 * @param currentFigure Pointer to the current figure structure.
 * @param nextFigure Pointer to the next figure structure.
 *
 * @return 1 if the block can be spawned, 0 otherwise.
 */
int spawnBlock(GameInfo_t* gameInfo, Figure_t* currentFigure,
               Figure_t* nextFigure) {
  copyFigure(currentFigure, nextFigure);
  initFigure(nextFigure);
  int canSpawn = 1;
  for (int y = currentFigure->y, i = 0; i < currentFigure->size; i++, y++) {
    for (int x = currentFigure->x, j = 0; j < currentFigure->size; j++, x++) {
      if (currentFigure->figureMatrix[i][j] == 1 &&
          gameInfo->field[y][x] != 0) {
        canSpawn = 0;
      }
    }
  }
  return canSpawn;
}

void updateField(Figure_t* figure, GameInfo_t* gameInfo) {
  fillField(gameInfo->field, figure);
}

void backPosClearField(int** field, Figure_t* figure) {
  for (int y = figure->y, i = 0; i < figure->size; i++, y++) {
    for (int x = figure->x, j = 0; j < figure->size; j++, x++) {
      if (figure->figureMatrix[i][j] == 1) {
        field[y][x] = 0;
      }
    }
  }
}

/**
 * Checks if a figure can move in a specified direction without colliding with the game field.
 *
 * @param figure The figure to check for collision.
 * @param gameInfo The game information structure containing the game field.
 * @param Move The direction to move the figure (Left, Right, or Down).
 *
 * @return 1 if the figure can move without collision, 0 otherwise.
 */
int isCollision(Figure_t figure, GameInfo_t gameInfo, int Move) {
  backPosClearField(gameInfo.field, &figure);
  switch (Move) {
    case Left:
      figure.x--;
      break;
    case Right:
      figure.x++;
      break;
    case Down:
      figure.y++;
      break;
    default:
      break;
  }
  int isCanMove = 1;
  for (int y = figure.y, i = 0; i < figure.size; i++, y++) {
    for (int x = figure.x, j = 0; j < figure.size; j++, x++) {
      if (figure.figureMatrix[i][j] == 1 && gameInfo.field[y][x] != 0) {
        isCanMove = 0;
      }
    }
  }
  return isCanMove;
}

int isCanRotate270Degrees(Figure_t figure, GameInfo_t gameInfo) {
  backPosClearField(gameInfo.field, &figure);
  rotateFigureOn270Degrees(figure.figureMatrix, figure.size);
  int isCanRotate = 1;
  for (int y = figure.y, i = 0; i < figure.size; i++, y++) {
    for (int x = figure.x, j = 0; j < figure.size; j++, x++) {
      if (figure.figureMatrix[i][j] == 1 && gameInfo.field[y][x] != 0) {
        isCanRotate = 0;
      }
    }
  }
  rotateFigureOn90Degrees(figure.figureMatrix, figure.size);
  return isCanRotate;
}

int isCanRotate90Degrees(Figure_t figure, GameInfo_t gameInfo) {
  backPosClearField(gameInfo.field, &figure);
  rotateFigureOn90Degrees(figure.figureMatrix, figure.size);
  int isCanRotate = 1;
  for (int y = figure.y, i = 0; i < figure.size; i++, y++) {
    for (int x = figure.x, j = 0; j < figure.size; j++, x++) {
      if (figure.figureMatrix[i][j] == 1 && gameInfo.field[y][x] != 0) {
        isCanRotate = 0;
      }
    }
  }
  rotateFigureOn270Degrees(figure.figureMatrix, figure.size);
  return isCanRotate;
}

void checkLinesField(GameInfo_t* gameInfo) {
  int countLines = 0;
  int isFind = 1;
  while (isFind) {
    isFind = 0;
    for (int i = ROWS_MAP - 2; i >= 1; i--) {
      int isFullLine = 1;
      for (int j = 1; j < COLS_MAP - 1; j++) {
        if (gameInfo->field[i][j] == 0) {
          isFullLine = 0;
        }
      }
      if (isFullLine) {
        countLines++;
        isFind = 1;
        for (int k = i; k >= 2; k--) {
          for (int j = 1; j < COLS_MAP - 1; j++) {
            gameInfo->field[k][j] = gameInfo->field[k - 1][j];
          }
        }
      }
    }
  }
  switch (countLines) {
    case 1:
      gameInfo->score += 100;
      break;
    case 2:
      gameInfo->score += 300;
      break;
    case 3:
      gameInfo->score += 700;
      break;
    case 4:
      gameInfo->score += 1500;
      break;
    default:
      break;
  }
  if (countLines > 0) {
    if (gameInfo->score > gameInfo->high_score) {
      gameInfo->high_score = gameInfo->score;
    }
    gameInfo->level = gameInfo->score / 600;
  }
}

void speedUp(GameInfo_t* gameInfo) {
  gameInfo->speed = (gameInfo->level) * 100;
  usleep((200000 - (gameInfo->speed * 150)));
}