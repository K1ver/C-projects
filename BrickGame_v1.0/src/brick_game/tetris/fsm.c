#include "fsm.h"


/**
 * Rotates the given figure based on its type and current rotation state.
 *
 * This function checks the type of the figure and its current rotation state,
 * and then applies the necessary rotation (90 or 270 degrees) to the figure's
 * matrix. It also updates the figure's rotation state accordingly.
 *
 * @param figure   A pointer to the figure to be rotated.
 * @param gameInfo A pointer to the game information, which is used to check
 *                 if the rotation is possible.
 *
 * @return None
 */
void rotateFigure(Figure_t *figure, GameInfo_t *gameInfo) {
  switch (figure->type) {
    case I:
      if (figure->rotationState == first) {
        if (isCanRotate270Degrees(*figure, *gameInfo)) {
          rotateFigureOn270Degrees(figure->figureMatrix, figure->size);
          figure->rotationState = third;
        }
      } else {
        if (isCanRotate90Degrees(*figure, *gameInfo)) {
          rotateFigureOn90Degrees(figure->figureMatrix, figure->size);
        }
      }
      break;
    case O:
      break;
    case T:
      if (isCanRotate90Degrees(*figure, *gameInfo)) {
        rotateFigureOn90Degrees(figure->figureMatrix, figure->size);
      }
      break;
    case L:
      if (isCanRotate90Degrees(*figure, *gameInfo)) {
        rotateFigureOn90Degrees(figure->figureMatrix, figure->size);
      }
      break;
    case J:
      if (isCanRotate90Degrees(*figure, *gameInfo)) {
        rotateFigureOn90Degrees(figure->figureMatrix, figure->size);
      }
      break;
    case Z:
      if (figure->rotationState == first) {
        if (isCanRotate270Degrees(*figure, *gameInfo)) {
          rotateFigureOn270Degrees(figure->figureMatrix, figure->size);
          figure->rotationState = third;
        }
      } else {
        if (isCanRotate90Degrees(*figure, *gameInfo)) {
          rotateFigureOn90Degrees(figure->figureMatrix, figure->size);
        }
      }
      break;
    case S:
      if (figure->rotationState == first) {
        if (isCanRotate270Degrees(*figure, *gameInfo)) {
          rotateFigureOn270Degrees(figure->figureMatrix, figure->size);
          figure->rotationState = third;
        }
      } else {
        if (isCanRotate90Degrees(*figure, *gameInfo)) {
          rotateFigureOn90Degrees(figure->figureMatrix, figure->size);
        }
      }
      break;
    default:
      break;
  }
  if (figure->rotationState == fourth) {
    figure->rotationState = first;
  } else {
    figure->rotationState++;
  }
}

GameInfo_t *getGameInfo(GameInfo_t *gameInfo) {
  static GameInfo_t *Info = NULL;
  if (Info == NULL) {
    Info = malloc(sizeof(GameInfo_t));
    initGameInfo(Info);
    return Info;
  }
  if (gameInfo != NULL) {
    Info = gameInfo;
  }
  return Info;
}

TetrisState_t *getTetrisState(TetrisState_t *state) {
  static TetrisState_t *State = NULL;
  if (State == NULL) {
    State = malloc(sizeof(TetrisState_t));
    *State = START;
    return State;
  }
  if (state != NULL) {
    State = state;
  }
  return State;
}

Figure_t *getFigure(Figure_t *figure) {
  static Figure_t *Figure = NULL;
  if (Figure == NULL) {
    Figure = malloc(sizeof(Figure_t));
    return Figure;
  }
  if (figure != NULL) {
    Figure = figure;
  }
  return Figure;
}

Figure_t *getNextFigure(Figure_t *figure) {
  static Figure_t *Figure = NULL;
  if (Figure == NULL) {
    Figure = malloc(sizeof(Figure_t));
    initFigure(Figure);
    return Figure;
  }
  if (figure != NULL) {
    Figure = figure;
  }
  return Figure;
}

void spawn_state(GameInfo_t *gameInfo, Figure_t *currentFigure,
                 Figure_t *nextFigure, TetrisState_t *state) {
  if (!spawnBlock(gameInfo, currentFigure, nextFigure)) {
    *state = GAMEOVER;
  } else {
    *state = MOVING;
  }
}

void pause_state(UserAction_t action, GameInfo_t *gameInfo,
                 TetrisState_t *state) {
  switch (action) {
    case Action:
      gameInfo->pause = 0;
      *state = MOVING;
      break;
    case Terminate:
      *state = EXIT;
      break;
    default:
      break;
  }
}

/**
 * Handles the moving state of the Tetris game, updating the game state and figures accordingly.
 *
 * @param action The user action to handle (e.g. move left, right, down, etc.)
 * @param gameInfo A pointer to the game information structure
 * @param currentFigure A pointer to the current figure being manipulated
 * @param state A pointer to the current game state
 */
void moving_state(UserAction_t action, GameInfo_t *gameInfo,
                  Figure_t *currentFigure, TetrisState_t *state) {
  switch (action) {
    case Left:
      if (isCollision(*currentFigure, *gameInfo, Left)) {
        moveFigureLeft(currentFigure, gameInfo);
      }
      break;
    case Right:
      if (isCollision(*currentFigure, *gameInfo, Right)) {
        moveFigureRight(currentFigure, gameInfo);
      }
      break;
    case Down:
      while (isCollision(*currentFigure, *gameInfo, Down)) {
        moveFigureDown(currentFigure, gameInfo);
      }
      updateField(currentFigure, gameInfo);
      checkLinesField(gameInfo);
      *state = SPAWN;
      break;
    case Action:
      rotateFigure(currentFigure, gameInfo);
      break;
    default:
      break;
  }
}

/**
 * Handles a user action in the Tetris game, updating the game state and figures accordingly.
 *
 * @param action The user action to handle (e.g. move left, right, down, etc.)
 * @param state A pointer to the current game state
 * @param gameInfo A pointer to the game information structure
 * @param currentFigure A pointer to the current figure being manipulated
 * @param nextFigure A pointer to the next figure to be spawned
 */
void sigact(UserAction_t action, TetrisState_t *state, GameInfo_t *gameInfo,
            Figure_t *currentFigure, Figure_t *nextFigure) {
  if (*state != START && *state != GAMEOVER && action != Down &&
      *state != SPAWN && *state != PAUSE) {
    if (isCollision(*currentFigure, *gameInfo, Down)) {
      moveFigureDown(currentFigure, gameInfo);
      updateField(currentFigure, gameInfo);
    } else {
      *state = SPAWN;
      updateField(currentFigure, gameInfo);
      checkLinesField(gameInfo);
    }
  }
  if (action == Pause) {
    *state = PAUSE;
    gameInfo->pause = 1;
  }
  switch (*state) {
    case START:
      if (action == Action)
        *state = SPAWN;
      else if (action == Terminate)
        *state = EXIT;
      break;
    case SPAWN:
      spawn_state(gameInfo, currentFigure, nextFigure, state);
      break;
    case MOVING:
      moving_state(action, gameInfo, currentFigure, state);
      break;
    case SHIFTING:
      if (*state != SPAWN) {
        *state = MOVING;
      }
      break;
    case PAUSE:
      pause_state(action, gameInfo, state);
      break;
    case GAMEOVER:
      if (action == Terminate) *state = EXIT;
      if (action == Action) {
        clearInfo(gameInfo);
        *state = SPAWN;
      }
      break;
    default:
      break;
  }
  if (*state != SPAWN) {
    updateField(currentFigure, gameInfo);
  }
}

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *gameInfo = getGameInfo(NULL);
  Figure_t *currentFigure = getFigure(NULL);
  TetrisState_t *state = getTetrisState(NULL);
  Figure_t *nextFigure = getNextFigure(NULL);

  if (hold) {
    sigact(action, state, gameInfo, currentFigure, nextFigure);
  }
  getGameInfo(gameInfo);
  getTetrisState(state);
  getFigure(currentFigure);
  getNextFigure(nextFigure);
  if (*state == GAMEOVER) {
    writeHighScore(gameInfo->high_score);
    printGameOverTetris(0);
  } else if (gameInfo->level == 10) {
    writeHighScore(gameInfo->high_score);
    printGameOverTetris(1);
  } else {
    printField(gameInfo, nextFigure);
  }
  refresh();
  speedUp(gameInfo);
  erase();
}

void moveFigureLeft(Figure_t *figure, GameInfo_t *gameInfo) {
  backPosClearField(gameInfo->field, figure);
  figure->x--;
}

void moveFigureRight(Figure_t *figure, GameInfo_t *gameInfo) {
  backPosClearField(gameInfo->field, figure);
  figure->x++;
}

void moveFigureDown(Figure_t *figure, GameInfo_t *gameInfo) {
  backPosClearField(gameInfo->field, figure);
  figure->y++;
}
void updateUserAction(UserAction_t *action) {
  char c = getch();
  switch (c) {
    case 'a':
      *action = Left;
      break;
    case 'd':
      *action = Right;
      break;
    case 's':
      *action = Down;
      break;
    case 'r':
      *action = Action;
      break;
    case 'q':
      *action = Terminate;
      break;
    case 'p':
      *action = Pause;
      break;
    default:
      *action = Start;
      break;
  }
}