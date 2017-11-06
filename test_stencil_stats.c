#include <stdio.h>
#include "cdefs.h"
#include "stencil.c"
#include "stats.c"


// Generate Assertion Functinos
MAKE_ASSERT_EQ(uchar)
MAKE_ASSERT_EQ(short)
MAKE_ASSERT_EQ(int32)

#define MAKE_TEST_STENCIL(F) \
  int test_##F(unsigned char* src, \
                    unsigned char *dst, unsigned char *expected, int width, int height) { \
                    memset(dst, 0, width*height);\
                    F(src, width, height, dst); \
                    int ret = assert_eq_uchar(dst, expected, width*height);\
                    if (ret ==0 )  printf("Testing %s was succesfull.\n", #F); \
                    else   printf("Testing %s failed.\n", #F); \
                    return ret;\
                }


void test_meanStdDev(unsigned char *input, int width, int height, float expected_mean, float expected_stddev) {
  float mean, stddev;
  meanStdDev(input, width, height, &mean, &stddev);
  int ret = ((mean-expected_mean) > EPSILON || (expected_mean-mean) > EPSILON);
  ret |= ((stddev-expected_stddev) > EPSILON || (expected_stddev-stddev) > EPSILON);
  if (ret ==0 )  printf("Testing meanStdDev was succesfull.\n");
  else   printf("Testing meanStdDev failed.\n");
  return ret;
}

// Generate Test Functinos
MAKE_TEST_STENCIL(box3x3)
MAKE_TEST_STENCIL(erode)
MAKE_TEST_STENCIL(dilate)
MAKE_TEST_STENCIL(gaussian3x3)
MAKE_TEST_STENCIL(gaussian5x5)
MAKE_TEST_STENCIL(median3x3)
MAKE_TEST_STENCIL(censusTransform)

int main() {

  size_t width, height, step;

  // Uchar tests
  uchar uchar_image[25] = {1, 2, 3, 4, 5,
                          60, 70, 80, 90, 100,
                          11, 12, 13, 14, 15,
                          160, 170, 180, 190, 200,
                          21, 22, 23, 24, 25};
  uchar uchar_dst_image[25] = {0};

  uchar box3x3_expected[25] = {0, 0, 0, 0, 0,
                          0, 28, 32, 36, 0,
                          0, 84, 91, 98, 0,
                          0, 68, 72, 76, 0,
                          0, 0, 0, 0, 0};
  uchar erode_expected[25] = {0, 0, 0, 0, 0,
                          0, 1, 2, 3, 0,
                          0, 11, 12, 13, 0,
                          0, 11, 12, 13, 0,
                          0, 0, 0, 0, 0};
  uchar dilate_expected[25] = {0, 0, 0, 0, 0,
                          0, 80, 90, 100, 0,
                          0, 180, 190, 200, 0,
                          0, 180, 190, 200, 0,
                          0, 0, 0, 0, 0};
  uchar gaussian3x3_expected[25] = {0, 0, 0, 0, 0,
                          0, 38, 44, 49, 0,
                          0, 66, 71, 77, 0,
                          0, 93, 99, 104, 0,
                          0, 0, 0, 0, 0};
  uchar gaussian5x5_expected[25] = {0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0,
                          0, 0, 92, 0, 0,
                          0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0};
  uchar median3x3_expected[25] = {0, 0, 0, 0, 0,
                          0, 12, 13, 14, 0,
                          0, 70, 80, 90 , 0,
                          0, 22, 23, 24, 0,
                          0, 0, 0, 0, 0};
  uchar censusTransform_expected[25] = {0, 0, 0, 0, 0,
                          0, 8, 8, 8, 0,
                          0, 239, 239, 239, 0,
                          0, 8, 8, 8, 0,
                          0, 0, 0, 0, 0};

  test_box3x3(uchar_image, uchar_dst_image, box3x3_expected, 5, 5);
  test_erode(uchar_image, uchar_dst_image, erode_expected, 5, 5);
  test_dilate(uchar_image, uchar_dst_image, dilate_expected, 5, 5);
  test_gaussian3x3(uchar_image, uchar_dst_image, gaussian3x3_expected, 5, 5);
  test_gaussian5x5(uchar_image, uchar_dst_image, gaussian5x5_expected, 5, 5);
  test_median3x3(uchar_image, uchar_dst_image, median3x3_expected, 5, 5);
  test_censusTransform(uchar_image, uchar_dst_image, censusTransform_expected, 5, 5);

  float expected_mean = 59.8;
  float expected_stddev = 67.75077;
  test_meanStdDev(uchar_image, 5, 5, expected_mean, expected_stddev);

  return 0;
}
