#include <stdio.h>

#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Перевод в БИГ_децимал
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_rezult = decimal_to_big(*result);

  // Приведение к точке
  normalize_big_dec(&big_value_1, &big_value_2);

  // Сложение
  full_add(big_value_1, big_value_2, &big_rezult);

  // Перевод обратно в децимал
  int overflow = big_to_dec(&big_rezult, result);
  int code_error = 0;
  if (overflow) {
    if (get_sign(value_1.bits[3])) {
      code_error = 2;
    } else {
      code_error = 1;
    }
  } else if (is_empty_dec(*result)) {
    code_error = 2;
  }

  return code_error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Перевод в БИГ_децимал
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_rezult = decimal_to_big(*result);
  // Приведение к точке
  normalize_big_dec(&big_value_1, &big_value_2);

  // Вычитание
  full_sub(big_value_1, big_value_2, &big_rezult);

  // Перевод обратно в децимал
  int overflow = big_to_dec(&big_rezult, result);
  int code_error = 0;
  if (overflow) {
    if (get_sign(value_2.bits[3])) {
      code_error = 2;
    } else {
      code_error = 1;
    }
  } else if (is_empty_dec(*result)) {
    code_error = 2;
  }
  return code_error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Перевод в БИГ_децимал
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_rezult = decimal_to_big(*result);
  // Приведение к точке

  // Умножение
  big_rezult = simple_mul(big_value_1, big_value_2);
  set_exp(&big_rezult.mantice,
          get_exp(big_value_2.mantice) + get_exp(big_value_1.mantice));

  // Перевод обратно в децимал
  int overflow = big_to_dec(&big_rezult, result);
  int code_error = 0;
  if (overflow) {
    if (get_sign(value_1.bits[3]) ^ get_sign(value_2.bits[3])) {
      code_error = 2;
    } else {
      code_error = 1;
    }
  } else if (is_empty_dec(*result)) {
    code_error = 2;
  }
  return code_error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Перевод в БИГ_децимал
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_rezult = decimal_to_big(*result);

  // Приведение к точке
  normalize_big_dec(&big_value_1, &big_value_2);
  int code_error = 0;
  // Деление на ноль
  if (is_empty_bdec(big_value_2)) {
    code_error = 3;

  } else {
    // Деление
    big_rezult = full_div(big_value_1, big_value_2);
  }

  // Перевод обратно в децимал
  int overflow = big_to_dec(&big_rezult, result);

  if (overflow && code_error != 3) {
    if (get_sign(value_1.bits[3]) ^ get_sign(value_2.bits[3])) {
      code_error = 2;
    } else {
      code_error = 1;
    }
  } else if (is_empty_dec(*result) && code_error != 3) {
    code_error = 2;
  }
  return code_error;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Перевод в БИГ_децимал
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_rezult = decimal_to_big(*result);
  int code_error = 0;
  // Деление на ноль
  if (is_empty_bdec(big_value_2)) {
    code_error = 3;
  }

  // Приведение к точке
  normalize_big_dec(&big_value_1, &big_value_2);

  // Умножение
  big_rezult = simple_mod(big_value_1, big_value_2);

  // Перевод обратно в децимал
  int overflow = big_to_dec(&big_rezult, result);

  if (overflow && code_error != 3) {
    if (get_sign(value_1.bits[3]) ^ get_sign(value_2.bits[3])) {
      code_error = 2;
    } else {
      code_error = 1;
    }
  } else if (is_empty_dec(*result) && code_error != 3) {
    code_error = 2;
  }
  return code_error;
}
