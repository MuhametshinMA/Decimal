#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal dec1 = decimal_to_big(value_1);
  s21_big_decimal dec2 = decimal_to_big(value_2);
  normalize_big_dec(&dec1, &dec2);
  return s21_is_big_less(dec1, dec2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal dec1 = decimal_to_big(value_1);
  s21_big_decimal dec2 = decimal_to_big(value_2);
  normalize_big_dec(&dec1, &dec2);
  return s21_is_big_less_or_equal(dec1, dec2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal dec1 = decimal_to_big(value_1);
  s21_big_decimal dec2 = decimal_to_big(value_2);
  normalize_big_dec(&dec1, &dec2);
  return s21_is_big_greater(dec1, dec2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal dec1 = decimal_to_big(value_1);
  s21_big_decimal dec2 = decimal_to_big(value_2);
  normalize_big_dec(&dec1, &dec2);
  return s21_is_big_greater_or_equal(dec1, dec2);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal dec1 = decimal_to_big(value_1);
  s21_big_decimal dec2 = decimal_to_big(value_2);
  normalize_big_dec(&dec1, &dec2);
  return s21_is_big_equal(dec1, dec2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal dec1 = decimal_to_big(value_1);
  s21_big_decimal dec2 = decimal_to_big(value_2);
  normalize_big_dec(&dec1, &dec2);
  return s21_is_not_big_equal(dec1, dec2);
}
