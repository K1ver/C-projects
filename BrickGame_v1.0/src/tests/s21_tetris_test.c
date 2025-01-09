#include "../brick_game/tetris/fsm.h"
#include "check.h"

START_TEST(test_tetris_1) {
  UserAction_t action;
  updateUserAction(&action);
  action = Action;
  userInput(action, 1);
  userInput(action, 1);
  action = Left;
  userInput(action, 1);
  action = Right;
  userInput(action, 1);
  action = Action;
  userInput(action, 1);
  action = Down;
  userInput(action, 1);
  userInput(action, 1);
  action = Start;
  userInput(action, 1);
  userInput(action, 1);
  action = Action;
  userInput(action, 1);
  userInput(action, 1);
  userInput(action, 1);
  action = Pause;
  userInput(action, 1);
  action = Action;
  userInput(action, 1);
  GameInfo_t *gameInfo = getGameInfo(NULL);
  clearInfo(gameInfo);
}

START_TEST(test_tetris_2) {
  Figure_t *figure = getFigure(NULL);
  Figure_t *figure1 = getFigure(NULL);
  Figure_t *figure2 = getFigure(NULL);
  Figure_t *figure3 = getFigure(NULL);
  Figure_t *figure4 = getFigure(NULL);
  Figure_t *figure5 = getFigure(NULL);
  Figure_t *figure6 = getFigure(NULL);
  Figure_t *figure7 = getFigure(NULL);
  Figure_t *figure8 = getFigure(NULL);
  initFigure(figure);
  initFigure(figure1);
  initFigure(figure2);
  initFigure(figure3);
  initFigure(figure4);
  initFigure(figure5);
  initFigure(figure6);
  initFigure(figure7);
  initFigure(figure8);
}

START_TEST(test_tetris_3) {
  GameInfo_t *gameInfo = getGameInfo(NULL);
  initGameInfo(gameInfo);
  clearInfo(gameInfo);
  speedUp(gameInfo);
  gameInfo->field[18][1] = 1;
  gameInfo->field[18][2] = 1;
  gameInfo->field[18][3] = 1;
  gameInfo->field[18][4] = 1;
  gameInfo->field[18][5] = 1;
  gameInfo->field[18][6] = 1;
  gameInfo->field[18][7] = 1;
  gameInfo->field[18][8] = 1;
  gameInfo->field[18][9] = 1;
  checkLinesField(gameInfo);
}

START_TEST(test_tetris_4) {
  GameInfo_t *gameInfo = getGameInfo(NULL);
  initGameInfo(gameInfo);
  clearInfo(gameInfo);
  speedUp(gameInfo);
  gameInfo->field[18][1] = 1;
  gameInfo->field[18][2] = 1;
  gameInfo->field[18][3] = 1;
  gameInfo->field[18][4] = 1;
  gameInfo->field[18][5] = 1;
  gameInfo->field[18][6] = 1;
  gameInfo->field[18][7] = 1;
  gameInfo->field[18][8] = 1;
  gameInfo->field[18][9] = 1;
  gameInfo->field[17][1] = 1;
  gameInfo->field[17][2] = 1;
  gameInfo->field[17][3] = 1;
  gameInfo->field[17][4] = 1;
  gameInfo->field[17][5] = 1;
  gameInfo->field[17][6] = 1;
  gameInfo->field[17][7] = 1;
  gameInfo->field[17][8] = 1;
  gameInfo->field[17][9] = 1;
  checkLinesField(gameInfo);
}

START_TEST(test_tetris_5) {
  GameInfo_t *gameInfo = getGameInfo(NULL);
  initGameInfo(gameInfo);
  clearInfo(gameInfo);
  speedUp(gameInfo);
  gameInfo->field[18][1] = 1;
  gameInfo->field[18][2] = 1;
  gameInfo->field[18][3] = 1;
  gameInfo->field[18][4] = 1;
  gameInfo->field[18][5] = 1;
  gameInfo->field[18][6] = 1;
  gameInfo->field[18][7] = 1;
  gameInfo->field[18][8] = 1;
  gameInfo->field[18][9] = 1;
  gameInfo->field[17][1] = 1;
  gameInfo->field[17][2] = 1;
  gameInfo->field[17][3] = 1;
  gameInfo->field[17][4] = 1;
  gameInfo->field[17][5] = 1;
  gameInfo->field[17][6] = 1;
  gameInfo->field[17][7] = 1;
  gameInfo->field[17][8] = 1;
  gameInfo->field[17][9] = 1;
  gameInfo->field[16][1] = 1;
  gameInfo->field[16][2] = 1;
  gameInfo->field[16][3] = 1;
  gameInfo->field[16][4] = 1;
  gameInfo->field[16][5] = 1;
  gameInfo->field[16][6] = 1;
  gameInfo->field[16][7] = 1;
  gameInfo->field[16][8] = 1;
  gameInfo->field[16][9] = 1;
  checkLinesField(gameInfo);
}

START_TEST(test_tetris_6) {
  GameInfo_t *gameInfo = getGameInfo(NULL);
  initGameInfo(gameInfo);
  clearInfo(gameInfo);
  speedUp(gameInfo);
  gameInfo->field[18][1] = 1;
  gameInfo->field[18][2] = 1;
  gameInfo->field[18][3] = 1;
  gameInfo->field[18][4] = 1;
  gameInfo->field[18][5] = 1;
  gameInfo->field[18][6] = 1;
  gameInfo->field[18][7] = 1;
  gameInfo->field[18][8] = 1;
  gameInfo->field[18][9] = 1;
  gameInfo->field[17][1] = 1;
  gameInfo->field[17][2] = 1;
  gameInfo->field[17][3] = 1;
  gameInfo->field[17][4] = 1;
  gameInfo->field[17][5] = 1;
  gameInfo->field[17][6] = 1;
  gameInfo->field[17][7] = 1;
  gameInfo->field[17][8] = 1;
  gameInfo->field[17][9] = 1;
  gameInfo->field[16][1] = 1;
  gameInfo->field[16][2] = 1;
  gameInfo->field[16][3] = 1;
  gameInfo->field[16][4] = 1;
  gameInfo->field[16][5] = 1;
  gameInfo->field[16][6] = 1;
  gameInfo->field[16][7] = 1;
  gameInfo->field[16][8] = 1;
  gameInfo->field[16][9] = 1;
  gameInfo->field[15][1] = 1;
  gameInfo->field[15][2] = 1;
  gameInfo->field[15][3] = 1;
  gameInfo->field[15][4] = 1;
  gameInfo->field[15][5] = 1;
  gameInfo->field[15][6] = 1;
  gameInfo->field[15][7] = 1;
  gameInfo->field[15][8] = 1;
  gameInfo->field[15][9] = 1;
  checkLinesField(gameInfo);
}

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_tetris_1);
  tcase_add_test(tc1_1, test_tetris_2);
  tcase_add_test(tc1_1, test_tetris_3);
  tcase_add_test(tc1_1, test_tetris_4);
  tcase_add_test(tc1_1, test_tetris_5);
  tcase_add_test(tc1_1, test_tetris_6);
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}