#include <stdio.h>
#include "cdefs.h"
#include "arithm_core_c.c"

// Generate Assertion Functinos
MAKE_ASSERT_EQ(uchar)
MAKE_ASSERT_EQ(schar)
MAKE_ASSERT_EQ(short)
MAKE_ASSERT_EQ(int32)

#define MAKE_TEST_ADDSUB(T, F) \
  int test_##F##_##T(T* src1, T *src2, \
                    T *dst, T *expected, size_t step, int width, int height) { \
                    F##_##T(src1, step, src2, step, dst, step, width, height); \
                    int ret = assert_eq_##T(dst, expected, width*height);\
                    if (ret ==0 )  printf("Testing %s for type %s was succesfull.\n", #F, #T); \
                    else   printf("Testing %s for type %s failed.\n", #F, #T); \
                    return ret;\
                }

#define MAKE_TEST_MULDIV(T, F) \
  int test_##F##_##T(T* src1, T *src2, \
                    T *dst, T *expected, size_t step, int width, int height, float scale) { \
                    F##_##T(src1, step, src2, step, dst, step, width, height, scale); \
                    int ret = assert_eq_##T(dst, expected, width*height);\
                    if (ret ==0 )  printf("Testing %s for type %s was succesfull.\n", #F, #T); \
                    else   printf("Testing %s for type %s failed.\n", #F, #T); \
                    return ret;\
                }

#define MAKE_TEST_RECIP(T) \
  int test_recip_##T(T* src1, \
                    T *dst, T *expected, size_t step, int width, int height, float scale) { \
                    recip_##T(src1, step, dst, step, width, height, scale); \
                    int ret = assert_eq_##T(dst, expected, width*height);\
                    if (ret ==0 )  printf("Testing recip for type %s was succesfull.\n", #T); \
                    else   printf("Testing recip for type %s failed.\n", #T); \
                    return ret;\
                }
#define MAKE_TEST_ADD_WEIGHTED(T) \
  int test_addWeighted_##T(T* src1, T *src2, \
                    T *dst, T *expected, size_t step, int width, int height, void *scalars) { \
                    addWeighted_##T(src1, step, src2, step, dst, step, width, height, scalars); \
                    int ret = assert_eq_##T(dst, expected, width*height);\
                    if (ret == 0 )  printf("Testing addWeighted for type %s was succesfull.\n", #T); \
                    else   printf("Testing addWeighted for type %s failed.\n", #T); \
                    return ret;\
                }

// Generate Test Functinos
MAKE_TEST_ADDSUB(uchar, add)
MAKE_TEST_ADDSUB(uchar, sub)
MAKE_TEST_MULDIV(uchar, mul)
MAKE_TEST_MULDIV(uchar, div)
MAKE_TEST_RECIP(uchar)
MAKE_TEST_ADD_WEIGHTED(uchar)

MAKE_TEST_ADDSUB(schar, add)
MAKE_TEST_ADDSUB(schar, sub)
MAKE_TEST_MULDIV(schar, mul)
MAKE_TEST_MULDIV(schar, div)
MAKE_TEST_RECIP(schar)
MAKE_TEST_ADD_WEIGHTED(schar)

MAKE_TEST_ADDSUB(short, add)
MAKE_TEST_ADDSUB(short, sub)
MAKE_TEST_MULDIV(short, mul)
MAKE_TEST_MULDIV(short, div)
MAKE_TEST_RECIP(short)
MAKE_TEST_ADD_WEIGHTED(short)

MAKE_TEST_ADDSUB(int32, add)
MAKE_TEST_ADDSUB(int32, sub)
MAKE_TEST_MULDIV(int32, mul)
MAKE_TEST_MULDIV(int32, div)
MAKE_TEST_RECIP(int32)
MAKE_TEST_ADD_WEIGHTED(int32)

MAKE_TEST_ADDSUB(float, add)
MAKE_TEST_ADDSUB(float, sub)
MAKE_TEST_MULDIV(float, mul)
MAKE_TEST_MULDIV(float, div)


MAKE_TEST_RECIP(float)
MAKE_TEST_ADD_WEIGHTED(float)


int main() {

  size_t width, height, step;

  // Uchar tests
  uchar uchar_arr1[10] = {1, 0, 3, 4, 250, 60, 70, 8, 100, 90};
  uchar uchar_arr2[10] = {1, 2, 3, 40, 5, 6, 107, 80, 200, 190};
  uchar uchar_arr_dst[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  uchar uchar_add_arr_expected[10] = {2, 2, 6, 44, 255, 66, 177, 88, 255, 255};
  test_add_uchar(uchar_arr1, uchar_arr2, uchar_arr_dst, uchar_add_arr_expected, 1, 10, 1);

  uchar uchar_sub_arr_expected[10] = {0, 0, 0, 0, 245, 54, 0, 0, 0, 0};
  test_sub_uchar(uchar_arr1, uchar_arr2, uchar_arr_dst, uchar_sub_arr_expected, 1, 10, 1);

  uchar uchar_mul_arr_expected[10] = {1, 0, 9, 160, 255, 255, 255, 255, 255, 255};
  test_mul_uchar(uchar_arr1, uchar_arr2, uchar_arr_dst, uchar_mul_arr_expected, 1, 10, 1, 1.0);

  uchar uchar_mul_arr_expected_2[10] = {3, 0, 23, 255, 255, 255, 255, 255, 255, 255};
  test_mul_uchar(uchar_arr1, uchar_arr2, uchar_arr_dst, uchar_mul_arr_expected_2, 1, 10, 1, 2.5);

  uchar uchar_div_arr_expected[10] = {1, 0, 1, 0, 50, 10, 1, 0, 1, 0};
  test_div_uchar(uchar_arr1, uchar_arr2, uchar_arr_dst, uchar_div_arr_expected, 1, 10, 1, 1.0);

  uchar uchar_recip_arr_expected[10] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
  test_recip_uchar(uchar_arr2, uchar_arr_dst, uchar_recip_arr_expected, 1, 10, 1, 1.0);


  // Short tests
  short short_arr1[10] = {-30001, 0, 3, 4, 2500, 600, 700, 800, 100, 20000};
  short short_arr2[10] = {10000, 2, 3, 40, 5, 6, 107, 80, 200, 20000};
  short short_arr_dst[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  short short_add_arr_expected[10] = {-20001, 2, 6, 44, 2505, 606, 807, 880, 300, 32767};
  test_add_short(short_arr1, short_arr2, short_arr_dst, short_add_arr_expected, 1, 10, 1);

  short short_sub_arr_expected[10] = {-32768, -2, 0, -36, 2495, 594, 593, 720, -100, 0};
  test_sub_short(short_arr1, short_arr2, short_arr_dst, short_sub_arr_expected, 1, 10, 1);

  short short_mul_arr_expected[10] = {-32768, 0, 9, 160, 12500, 3600, 32767, 32767, 20000, 32767};
  test_mul_short(short_arr1, short_arr2, short_arr_dst, short_mul_arr_expected, 1, 10, 1, 1.0);

  short short_div_arr_expected[10] = {-3, 0, 1, 0, 500, 100, 7, 10, 1, 1};
  test_div_short(short_arr1, short_arr2, short_arr_dst, short_div_arr_expected, 1, 10, 1, 1.0);

  short short_recip_arr_expected[10] = {0, 3, 2, 0, 1, 1, 0, 0, 0, 0};
  test_recip_short(short_arr2, short_arr_dst, short_recip_arr_expected, 1, 10, 1, 5.0);


  // Int32 tests
  int32 int32_arr1[10] = {-30001, 2<<30, 3, 4, 2500, 600, 700, 800, 100, 2<<31};
  int32 int32_arr2[10] = {10000, 2<<10, 3, 40, -5, 6, -107, 80, 200, -100};
  int32 int32_arr_dst[10];

  int32 int32_add_arr_expected[10];
  for(int i=0; i < 10; ++i)
   int32_add_arr_expected[i] = int32_arr1[i] + int32_arr2[i];
  test_add_int32(int32_arr1, int32_arr2, int32_arr_dst, int32_add_arr_expected, 1, 10, 1);

  int32 int32_sub_arr_expected[10];
  for(int i=0; i < 10; ++i)
   int32_sub_arr_expected[i] = int32_arr1[i] - int32_arr2[i];
  test_sub_int32(int32_arr1, int32_arr2, int32_arr_dst, int32_sub_arr_expected, 1, 10, 1);

  int32 int32_mul_arr_expected[10];
  for(int i=0; i < 10; ++i)
   int32_mul_arr_expected[i] = saturate_cast_int_float(int32_arr1[i] * int32_arr2[i] * 1.0);
  test_mul_int32(int32_arr1, int32_arr2, int32_arr_dst, int32_mul_arr_expected, 1, 10, 1, 1.0);

  int32 int32_div_arr_expected[10];
  for(int i=0; i < 10; ++i)
   int32_div_arr_expected[i] = saturate_cast_int_float(1.0* int32_arr1[i] / int32_arr2[i]);
  test_div_int32(int32_arr1, int32_arr2, int32_arr_dst, int32_div_arr_expected, 1, 10, 1, 1.0);

  int32 int32_recip_arr_expected[10];
  for(int i=0; i < 10; ++i)
   int32_recip_arr_expected[i] = saturate_cast_int_float(5*(1.0/int32_arr2[i]));
  test_recip_int32(int32_arr2, int32_arr_dst, int32_recip_arr_expected, 1, 10, 1, 5.0);


  // Float tests
  width = 5;
  height = 2;
  step = width; // * sizeof(float);
  float float_arr1[10] = {-30.001, 0, 3, 4, -1002500, 600, 11000.0700, 800, 10.00000200, 20000};
  float float_arr2[10] = {100.00, 2, 3, 40, -0.00005, 6, 1.007, 80, 0.00200, 50000000.001};
  float float_arr_dst[10];
  float float_arr_expected[10];


  for(int i=0; i < 10; ++i)
   float_arr_expected[i] = float_arr1[i] + float_arr2[i];
  test_add_float(float_arr1, float_arr2, float_arr_dst, float_arr_expected, step, width, height);

  for(int i=0; i < 10; ++i)
   float_arr_expected[i] = float_arr1[i] - float_arr2[i];
  test_sub_float(float_arr1, float_arr2, float_arr_dst, float_arr_expected, step, width, height);

  for(int i=0; i < 10; ++i)
   float_arr_expected[i] = float_arr1[i] * float_arr2[i];
  test_mul_float(float_arr1, float_arr2, float_arr_dst, float_arr_expected, step, width, height, 1.0);

  float scale = 3.5;
  for(int i=0; i < 10; ++i) {
    float_arr_expected[i] = (scale * float_arr1[i] / float_arr2[i]);
  }
  test_div_float(float_arr1, float_arr2, float_arr_dst, float_arr_expected, step, width, height, scale);

  for(int i=0; i < 10; ++i)
   float_arr_expected[i] = 5*(1.0/float_arr2[i]);
  test_recip_float(float_arr2, float_arr_dst, float_arr_expected, step, width, height, 5.0);


  return 0;
}
