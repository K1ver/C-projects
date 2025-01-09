#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal lvalue_1, lvalue_2;
  s21_copy_decimal(value_1, &lvalue_1);
  s21_copy_decimal(value_2, &lvalue_2);
  int error = 0;
  if (s21_is_zero(lvalue_2)) {
    error = 3;
  } else {
    s21_set_zero(result);
    int sign_1 = s21_get_sign(lvalue_1);
    int sign_2 = s21_get_sign(lvalue_2);

    int scale_1 = s21_get_scale(lvalue_1);
    int scale_2 = s21_get_scale(lvalue_2);

    int result_sign = sign_1 ^ sign_2;
    int result_scale = 6;

    s21_set_sign(&lvalue_1, 0);
    s21_set_sign(&lvalue_2, 0);
    if (s21_is_equal(lvalue_1, lvalue_2)) {
      result->bits[0] = 1;
    }
    s21_set_sign(result, result_sign);
    if (scale_1 > 6 || scale_2 > 6) {
      if (scale_1 == scale_2) {
        s21_set_scale(result, scale_1);
      }
    } else {
      s21_set_scale(result, result_scale);
    }
  }
  return error;
}