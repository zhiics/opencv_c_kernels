#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include "cdefs.h"
#include <stdlib.h>
#include "util.h"

#include "transform.c"


#define SMALL 1
#define MEDIUM 1
#define LARGE 1
#define HUGE 1

void perf_warpAffine(unsigned char *input, unsigned char *output, float matrix[2][3], int width, int height) {
  struct timespec t1, t2;

  getTime(&t1);
  warpAffine(input, width, height, output, matrix);
  getTime(&t2);

  unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;
  printf("Test warpAffine for type char took %lu nanoseconds.\n", duration); \
  return;
}

void perf_warpPerspective(unsigned char *input, unsigned char *output, float matrix[3][3], int width, int height) {
  struct timespec t1, t2;

  getTime(&t1);
  warpPerspective(input, width, height, output, matrix);
  getTime(&t2);

  unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;
  printf("Test warpPerspective for type char took %lu nanoseconds.\n", duration); \
  return;
}

int main() {

  size_t step = 1;

  // Uchar (UHD) tests
  struct TestImage input_img1, input_img2, dst_img;
  float matrix3x3[3][3] = {0.26, 0.22, -16.03,
                           0011, 0.27, -18.6,
                            -0.0016, -0.00017, 1};

  float matrix2x3[2][3] = {2, 0.3926, 0,
                           0, 2, 0};

#ifdef SMALL
  loadPGMImage("./raw/256x256/clock.pgm", &input_img1);
  allocateImage(input_img1.width, input_img1.height, 1, &dst_img);

  perf_warpAffine(input_img1.data, dst_img.data, matrix2x3, input_img1.width, input_img1.height);
  perf_warpPerspective(input_img1.data, dst_img.data, matrix3x3, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&dst_img);
#endif


#ifdef MEDIUM
  loadPGMImage("./raw/512x512/mandrill.pgm", &input_img1);
  loadPGMImage("./raw/512x512/mandrill.pgm", &dst_img);

  perf_warpAffine(input_img1.data, dst_img.data, matrix2x3, input_img1.width, input_img1.height);
  perf_warpPerspective(input_img1.data, dst_img.data, matrix3x3, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&dst_img);
#endif


#ifdef LARGE
  loadPGMImage("./raw/1024x1024/pirate.pgm", &input_img1);
  loadPGMImage("./raw/1024x1024/pirate.pgm", &dst_img);

  perf_warpAffine(input_img1.data, dst_img.data, matrix2x3, input_img1.width, input_img1.height);
  perf_warpPerspective(input_img1.data, dst_img.data, matrix3x3, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&dst_img);
#endif

#ifdef HUGE
  loadPGMImage("./raw/uhd/scarf.pgm", &input_img1);
  loadPGMImage("./raw/uhd/scarf.pgm", &dst_img);

  perf_warpAffine(input_img1.data, dst_img.data, matrix2x3, input_img1.width, input_img1.height);
  perf_warpPerspective(input_img1.data, dst_img.data, matrix3x3, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&dst_img);
#endif
  return 0;
}
