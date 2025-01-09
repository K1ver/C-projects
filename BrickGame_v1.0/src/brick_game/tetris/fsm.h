#ifndef FSM_H
#define FSM_H

#include "../../gui/cli/tetris_frontend.h"

typedef enum {
  START,
  SPAWN,
  PAUSE,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  EXIT
} TetrisState_t;

void userInput(UserAction_t action, bool hold);
void updateUserAction(UserAction_t *action);

GameInfo_t *getGameInfo(GameInfo_t *gameInfo);
Figure_t *getFigure(Figure_t *figure);
Figure_t *getNextFigure(Figure_t *figure);
TetrisState_t *getTetrisState(TetrisState_t *state);

void sigact(UserAction_t action, TetrisState_t *state, GameInfo_t *gameInfo,
            Figure_t *currentFigure, Figure_t *nextFigure);
void spawn_state(GameInfo_t *gameInfo, Figure_t *currentFigure,
                 Figure_t *nextFigure, TetrisState_t *state);

void moving_state(UserAction_t action, GameInfo_t *gameInfo,
                  Figure_t *currentFigure, TetrisState_t *state);
void pause_state(UserAction_t action, GameInfo_t *gameInfo,
                 TetrisState_t *state);
void rotateFigure(Figure_t *figure, GameInfo_t *gameInfo);
void moveFigureLeft(Figure_t *figure, GameInfo_t *gameInfo);
void moveFigureRight(Figure_t *figure, GameInfo_t *gameInfo);
void moveFigureDown(Figure_t *figure, GameInfo_t *gameInfo);
void printField(GameInfo_t *gameInfo, Figure_t *nextFigure);

#endif
