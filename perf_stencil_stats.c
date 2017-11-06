#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include "cdefs.h"
#include <stdlib.h>
#include "util.h"

#include "stats.c"
#include "stencil.c"


#define SMALL 1
#define MEDIUM 1
#define LARGE 1
#define HUGE 1

#define MAKE_PERF_STENCIL(F) \
  void perf_##F(unsigned char* src, \
                    unsigned char *dst, int width, int height) { \
                    struct timespec t1, t2;\
                    getTime(&t1);\
                    F(src, width, height, dst); \
                    getTime(&t2);\
                    unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;\
                    printf("Test %s for type char took %lu nanoseconds.\n", #F, duration); \
                    return;\
                }

void perf_meanStdDev(unsigned char *input, float* _mean, float* _stddev, int width, int height) {
  struct timespec t1, t2;
  float mean, stddev;

  getTime(&t1);
  meanStdDev(input, width, height, &mean, &stddev);
  getTime(&t2);

  *_mean = mean;
  *_stddev = stddev;
  unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;
  printf("Test meanstddev for type char took %lu nanoseconds.\n", duration); \
  return;
}

// Generate Test Functinos
MAKE_PERF_STENCIL(box3x3)
MAKE_PERF_STENCIL(erode)
MAKE_PERF_STENCIL(dilate)
MAKE_PERF_STENCIL(gaussian3x3)
MAKE_PERF_STENCIL(gaussian5x5)
MAKE_PERF_STENCIL(median3x3)
MAKE_PERF_STENCIL(censusTransform)


int main() {

  size_t step = 1;
  int ksize = 5;

  // Uchar (UHD) tests
  struct TestImage input_img1, input_img2, dst_img;
  float mean, stddev;

#ifdef SMALL
  loadPGMImage("./raw/256x256/clock.pgm", &input_img1);
  allocateImage(input_img1.width, input_img1.height, 1, &dst_img);

  perf_box3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_erode(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_dilate(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian5x5(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_median3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_censusTransform(input_img1.data, dst_img.data, input_img1.width, input_img1.height);

  perf_meanStdDev(input_img1.data, &mean, &stddev, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&dst_img);
#endif


#ifdef MEDIUM
  loadPGMImage("./raw/512x512/mandrill.pgm", &input_img1);
  loadPGMImage("./raw/512x512/mandrill.pgm", &dst_img);

  perf_box3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_erode(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_dilate(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian5x5(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_median3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_censusTransform(input_img1.data, dst_img.data, input_img1.width, input_img1.height);

  perf_meanStdDev(input_img1.data, &mean, &stddev, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&dst_img);
#endif


#ifdef LARGE
  loadPGMImage("./raw/1024x1024/pirate.pgm", &input_img1);
  loadPGMImage("./raw/1024x1024/pirate.pgm", &dst_img);

  perf_box3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_erode(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_dilate(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian5x5(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_median3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_censusTransform(input_img1.data, dst_img.data, input_img1.width, input_img1.height);

  perf_meanStdDev(input_img1.data, &mean, &stddev, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&dst_img);
#endif

#ifdef HUGE
  loadPGMImage("./raw/uhd/scarf.pgm", &input_img1);
  loadPGMImage("./raw/uhd/scarf.pgm", &dst_img);

  perf_box3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_erode(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_dilate(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian5x5(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_median3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_censusTransform(input_img1.data, dst_img.data, input_img1.width, input_img1.height);

  perf_meanStdDev(input_img1.data, &mean, &stddev, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&dst_img);
#endif
  return 0;
}
