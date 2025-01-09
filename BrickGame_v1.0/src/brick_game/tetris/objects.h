#ifndef OBJECTS_H
#define OBJECTS_H

typedef enum { I, O, T, L, J, Z, S } FigureType_t;

typedef enum { first, second, third, fourth } RotationState_t;

typedef struct {
  FigureType_t type;
  RotationState_t rotationState;
  int size;
  int **figureMatrix;
  int x;
  int y;
} Figure_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif