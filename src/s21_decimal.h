#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INT_DECIMAL 3
#define INT_BIG_DECIMAL 6
#define SO_BIG_NUMBER 79228162514264337593543950335
#define SO_SMALL_NUMBER 1e-28

typedef struct {
  unsigned int mantisa : 23;
  unsigned int exp : 8;
  unsigned int sign : 1;

} float_field;

typedef union {
  float_field fl_field;
  float fl;
  int i;
} Float_to_int;

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  union {
    unsigned int bits[6];
  };
  unsigned int mantice;

} s21_big_decimal;

static const s21_big_decimal bdec_ten = {.mantice = 0,
                                         .bits[5] = 0,
                                         .bits[4] = 0,
                                         .bits[3] = 0,
                                         .bits[2] = 0,
                                         .bits[1] = 0,
                                         .bits[0] = 10};

static const s21_big_decimal bdec_one = {.mantice = 0,
                                         .bits[5] = 0,
                                         .bits[4] = 0,
                                         .bits[3] = 0,
                                         .bits[2] = 0,
                                         .bits[1] = 0,
                                         .bits[0] = 1};

static const s21_big_decimal bdec_null = {.mantice = 0,
                                          .bits[5] = 0,
                                          .bits[4] = 0,
                                          .bits[3] = 0,
                                          .bits[2] = 0,
                                          .bits[1] = 0,
                                          .bits[0] = 0};

// arithmetic
/*return
0 - OK
1 - число слишком велико или равно бесконечности
2 - число слишком мало или равно отрицательной бесконечности
3 - деление на 0
*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// arithmetic

// compare
/*return
0 - FALSE
1 - TRUE
*/

/// @brief value_1 < value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_less(s21_decimal, s21_decimal);

/// @brief value_1 <= value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_less_or_equal(s21_decimal, s21_decimal);

/// @brief value_1 > value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_greater(s21_decimal, s21_decimal);

/// @brief value_1 >= value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_greater_or_equal(s21_decimal, s21_decimal);

/// @brief value_1 = value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_equal(s21_decimal, s21_decimal);

/// @brief value_1 != value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_not_equal(s21_decimal, s21_decimal);

/// @brief value_1 < value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_big_less(s21_big_decimal value_1, s21_big_decimal value_2);

/// @brief value_1 = value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_big_equal(s21_big_decimal value_1, s21_big_decimal value_2);

/// @brief value_1 > value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_big_greater(s21_big_decimal value_1, s21_big_decimal value_2);

/// @brief value_1 >= value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_big_greater_or_equal(s21_big_decimal value_1,
                                s21_big_decimal value_2);

/// @brief value_1 != value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_not_big_equal(s21_big_decimal value_1, s21_big_decimal value_2);

/// @brief value_1 <= value_2
/// @param value_1
/// @param value_2
/// @return 0 - false, 1 - true
int s21_is_big_less_or_equal(s21_big_decimal value_1, s21_big_decimal value_2);

// compare

// convert
/*return
0 - OK
1 - ошибка конвертации
Уточнение про преобразование числа типа float:

Если числа слишком малы (0 < |x| < 1e-28), вернуть ошибку и значение, равное 0
Если числа слишком велики (|x| > 79,228,162,514,264,337,593,543,950,335) или
равны бесконечности, вернуть ошибку При обработке числа с типом float
преобразовывать все содержащиеся в нём значимые десятичные цифры. Если таких
цифр больше 7, то значение числа округляется к ближайшему, у которого не больше
7 значимых цифр.

Уточнение про преобразование из числа типа decimal в тип int:

Если в числе типа decimal есть дробная часть, то её следует отбросить (например,
0.9 преобразуется 0)
*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// convert

// other
/*return
0 - OK
1 - ошибка вычисления
*/
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

/// @brief changes sign to the opposite
/// @param value - in
/// @param result - out
/// @return 0 - ok.
int s21_negate(s21_decimal value, s21_decimal *result);
// other

// support
void print_bit(s21_decimal);
void print_big_bit(s21_big_decimal);
void set_bit(unsigned int *, unsigned char);
void reset_bit(unsigned int *, unsigned char);
void set_exp(unsigned int *, unsigned char);
void set_sign(unsigned int *, char);
char get_exp(unsigned int);
char get_sign(unsigned int);
char check_bit(unsigned int, unsigned char);
s21_big_decimal decimal_to_big(s21_decimal);
s21_decimal set_rand_decimal();
unsigned char gen_rand_exp();
unsigned char gen_rand_sign();
void shift_bigdec_to_high(s21_big_decimal *);
unsigned char shift_bigdec_to_low(s21_big_decimal *);
s21_decimal set_decimal(unsigned int low, unsigned int mid, unsigned int high,
                        unsigned char exp, unsigned char sign);
s21_decimal set_decimal(unsigned int low, unsigned int mid, unsigned int high,
                        unsigned char exp, unsigned char sign);
unsigned int singl_high_shift(unsigned int);
unsigned int singl_low_shift(unsigned int);
unsigned char is_empty_bdec(s21_big_decimal);
int is_empty_dec(s21_decimal);
unsigned char get_big_fract_part(s21_big_decimal);
unsigned char round_big_dec(s21_big_decimal *, int, int);
unsigned char is_big_converted_to_dec(s21_big_decimal);
void fill_dec_from_big(s21_big_decimal, s21_decimal *);

/// @brief !!!Динамическая память не забудьте free()!!! функция формирует строку
/// цисла децимал в виде: знак експонента старший int средний int младший int
/// @param  число децимал
/// @return строка в формате: [sign] [exp] [high int] [mid int] [low int]
char *print_dec(s21_decimal);
void print_big_dec(s21_big_decimal);
unsigned char check_high_ints_big(s21_big_decimal bdec);

// simple arithmetic
#define DEC1_ZERO                                                       \
  (big_value_1.bits[0] || big_value_1.bits[1] || big_value_1.bits[2] || \
   big_value_1.bits[3] || big_value_1.bits[4] || big_value_1.bits[5])

#define DEC2_ZERO                                                       \
  (big_value_2.bits[0] || big_value_2.bits[1] || big_value_2.bits[2] || \
   big_value_2.bits[3] || big_value_2.bits[4] || big_value_2.bits[5])

s21_big_decimal simple_add(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2);
void full_add(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
              s21_big_decimal *big_rezult);
s21_big_decimal simple_sub(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2);
void full_sub(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
              s21_big_decimal *big_rezult);
s21_big_decimal simple_mul(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2);
s21_big_decimal simple_div(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2);
s21_big_decimal full_div(s21_big_decimal big_value_1,
                         s21_big_decimal big_value_2);
unsigned char sign_def(s21_big_decimal big_value_1,
                       s21_big_decimal big_value_2);
s21_big_decimal simple_mod(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2);
s21_big_decimal negative(s21_big_decimal big_value_1);
s21_big_decimal exclusive_or(s21_big_decimal value_1, s21_big_decimal value_2);
s21_big_decimal bit_and(s21_big_decimal value_1, s21_big_decimal value_2);
// simple arithmetic

/// @brief приводит число с меньшей экспонентой из двух чисел биг децимал к
/// числу с большей експонентой, путем умножения на 10 и увеличения экспоненты
/// @param big_value_1 первое число биг децимал
/// @param big_value_2 второе число биг децимал
void normalize_big_dec(s21_big_decimal *big_value_1,
                       s21_big_decimal *big_value_2);
void normalize_for_mod(s21_big_decimal big_value_1,
                       s21_big_decimal *big_value_2);
void cast_by_exp(s21_big_decimal *, unsigned char);

/// @brief переводит биг децимал в децимал
/// @param bdec биг децимал
/// @param dec_rez результат перевода в децимал
/// @return 0 если число переполнено, 1 если число перевелось корректно
int big_to_dec(s21_big_decimal *, s21_decimal *);

/// @brief функция приводит делимое до порядка делителя
/// @param big_value_1 делимое
/// @param temp_divider делитель приведенный до порядка делимого
/// @return степень десяти для приведения делителя к порядку делимого
unsigned char mul_to_exp(s21_big_decimal, s21_big_decimal *);
unsigned char get_mul_to_exp(s21_big_decimal, s21_big_decimal);
unsigned char sum_to_divided(s21_big_decimal *, s21_big_decimal *);

/// @brief приводит число децимал к нужной экспоненте
/// @param dec исходный децимал который необходимо привести
/// @param reduce_num экспонента к которой приводится число
/// @return децимал приведенный к нужной экспоненте
s21_decimal reduce_exp_dec(s21_decimal dec, unsigned char reduce_num);
s21_big_decimal reduce_exp_big_dec(s21_big_decimal dec1);

// comparison
int s21_is_big_to_equals(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_is_big_less(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_is_big_equal(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_is_big_greater(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_is_big_greater_or_equal(s21_big_decimal value_1,
                                s21_big_decimal value_2);
int s21_is_not_big_equal(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_is_big_less_or_equal(s21_big_decimal value_1, s21_big_decimal value_2);

// comparison

// other

s21_decimal simple_floor(s21_decimal dec);

// other

// support

#endif