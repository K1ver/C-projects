#ifndef TETRIS_FRONTEND_H
#define TETRIS_FRONTEND_H

#include "../../brick_game/tetris/tetris_backend.h"

void printField(GameInfo_t *gameInfo, Figure_t *nextFigure);

void printMenuTetris();
void printGameOverTetris(int result);

#endif