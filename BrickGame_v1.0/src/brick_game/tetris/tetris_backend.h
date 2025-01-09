#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include "defines.h"
#include "objects.h"

void initFigure(Figure_t* figure);
void initGameInfo(GameInfo_t* gameInfo);
int** initMatrix(int col, int row);
void updateField(Figure_t* figure, GameInfo_t* gameInfo);
void fillEdgesField(int** field);
void fillField(int** field, Figure_t* figure);
void freeMatrix(int** matrix, int row);
void freeFigure(Figure_t* figure);
int spawnBlock(GameInfo_t* gameInfo, Figure_t* currentFigure,
               Figure_t* nextFigure);
void backPosClearField(int** field, Figure_t* figure);
int isCollision(Figure_t figure, GameInfo_t gameInfo, int Move);
int isCanRotate90Degrees(Figure_t figure, GameInfo_t gameInfo);
int isCanRotate270Degrees(Figure_t figure, GameInfo_t gameInfo);
void rotateFigureOn90Degrees(int** figure, int n);
void rotateFigureOn270Degrees(int** figure, int n);
void rotateFigure(Figure_t* figure, GameInfo_t* gameInfo);
void checkLinesField(GameInfo_t* gameInfo);
void copyFigure(Figure_t* destination, Figure_t* source);
void writeHighScore(int score);
void clearInfo(GameInfo_t* gameInfo);
void speedUp(GameInfo_t* gameInfo);

#endif