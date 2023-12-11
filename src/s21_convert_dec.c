#include "s21_decimal.h"
/// @brief Из int в decimal
/// @param src входное значение целого числа
/// @param dst ссылка на структру децимал куда записываем
/// @return 0 - если все ок 1 - если все плохо
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  char res = 0;
  if (dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
    if (src < 0) {
      src *= -1;
      set_sign(&dst->bits[3], 1);
    }
    dst->bits[0] = src;
  } else
    res = 1;
  return res;
}

/// @brief Из float в decimal
/// @param src входное значение числа с плавающей точкой
/// @param dst ссылка на структруу децимал куда записываем
/// @return 0 - если все ок 1 - если все плохо
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  Float_to_int tmp = {0};
  s21_big_decimal big_dec = {0};
  tmp.fl = src;
  char sign = tmp.fl_field.sign, res = 0, flag = 1;
  char fl_char[256] = {0};
  double temp = (double)src, a = 0;
  unsigned exp = 0, len_float = 0, count_null = 0;
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
  if ((0 < fabs(temp) && fabs(temp) < SO_SMALL_NUMBER)) res = 1;
  if (sign) temp *= -1;
  sprintf(fl_char, "%.f", temp);
  fl_char[strlen(fl_char)] = '\0';
  while (exp < 28 && (int)temp / (int)pow(2, 21) == 0) {
    modf(temp, &a);
    if (a == 0 && flag) {
      count_null += 1;
      temp *= 10;
    } else if (exp <= 5 && (count_null + exp) <= 27) {
      flag = 0;
      temp *= 10;
      exp += 1;
    } else
      break;
  }
  exp = exp + count_null;
  temp = round(temp);
  if (exp == 0) {
    len_float = strlen(fl_char);
  }
  if (len_float > 7) {
    temp /= pow(10, len_float - 7);
    temp = round(temp);
    dst->bits[0] = temp;
    big_dec = decimal_to_big(*dst);
    for (size_t i = 0; i < len_float - 7; i++)
      big_dec = simple_mul(big_dec, bdec_ten);
    big_to_dec(&big_dec, dst);
  } else {
    if (exp <= 28)
      for (; fmod(temp, 10) == 0 && exp > 0; exp--, temp /= 10)
        ;
    (!res) ? (dst->bits[0] = temp) : (dst->bits[0] = 0);
  }
  set_exp(&dst->bits[3], exp);
  set_sign(&dst->bits[3], sign);
  return res;
}

/// @brief Из decimal в int
/// @param src входное значение структуры децимала
/// @param dst ссылка на переменную куда все записываем (типа int)
/// @return 0 - если все ок 1 - если все плохо
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  char res = 0;
  if (src.bits) {
    *dst = src.bits[0];
    *dst /= (int)pow(10, get_exp(src.bits[3]));
    if (get_sign(src.bits[3]) == 1) {
      *dst *= -1;
    }
  } else
    res = 1;
  return res;
}

/// @brief Из decimal в float
/// @param src входное значение структуры децимал
/// @param dst ссылка на переменную куда все записываем(типа float)
/// @return 0 - если все ок 1 - если все плохо
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int exp = get_exp(src.bits[3]);
  char result = 0;
  int index = 0;
  for (int i = 0, j = 0; i <= 32 && j < 96; i++, j++) {
    if (index != 2 && i == 32) {
      index += 1;
      i = 0;
    }
    *dst += check_bit(src.bits[index], i) * pow(2, j);
  }
  *dst /= pow(10, exp);
  if (get_sign(src.bits[3]) == 1) {
    *dst *= -1;
  }
  return result;
}
