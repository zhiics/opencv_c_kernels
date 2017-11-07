#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include "cdefs.h"
#include <stdlib.h>
#include "util.h"

#include "stats.c"
#include "stencil.c"

#define SMALL
#define MEDIUM
#define LARGE
#define HUGE

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
// Generate Test Functinos
MAKE_PERF_STENCIL(box3x3)
MAKE_PERF_STENCIL(erode)
MAKE_PERF_STENCIL(dilate)
MAKE_PERF_STENCIL(gaussian3x3)
MAKE_PERF_STENCIL(gaussian5x5)
MAKE_PERF_STENCIL(median3x3)
MAKE_PERF_STENCIL(censusTransform)

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

void perf_sobel(unsigned char *input, short* output_x, short* output_y, int width, int height) {
  struct timespec t1, t2;

  getTime(&t1);
  sobel(input, width, height, output_x, output_y);
  getTime(&t2);

  unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;
  printf("Test Sobel for type char took %lu nanoseconds.\n", duration); \
  return;
}

void perf_histogram(unsigned char *input, unsigned int *dist, int width, int height) {
  struct timespec t1, t2;
  int offset = 15;
  int range = 256;
  int B = 100;

  getTime(&t1);
  histogram(input, width, height, dist, offset, range, B);
  getTime(&t2);

  unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;
  printf("Test histogram for type char took %lu nanoseconds.\n", duration); \
  return;
}

int perf_nonmaxSuppress3x3(unsigned char* src, unsigned char* mask, unsigned char *dst, int width, int height) {
  struct timespec t1, t2;
  memset(dst, 0, width*height);

  getTime(&t1);
  nonmaxSuppress3x3(src, width, height, mask, dst);
  getTime(&t2);

  unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;
  printf("Test nonmaxSuppress3x3 for type char took %lu nanoseconds.\n", duration); \
  return;
}

int main() {

  size_t step = 1;
  int ksize = 5;

  // Uchar (UHD) tests
  struct TestImage input_img1, input_img2, dst_img, mask_img;
  struct TestImage dst_img_x, dst_img_y;
  float mean, stddev;
  unsigned int dist[256];

#ifdef SMALL
  loadPGMImage("./raw/256x256/clock.pgm", &input_img1);
  loadPGMImage("./raw/256x256/clock.pgm", &mask_img);
  allocateImage(input_img1.width, input_img1.height, 1, &dst_img);
  allocateImage(input_img1.width, input_img1.height, 2, &dst_img_x);
  allocateImage(input_img1.width, input_img1.height, 2, &dst_img_y);


  perf_box3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_erode(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_dilate(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian5x5(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_median3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_censusTransform(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_nonmaxSuppress3x3(input_img1.data, mask_img.data, dst_img.data, input_img1.width, input_img1.height);
  perf_sobel(input_img1.data, dst_img_x.data, dst_img_y.data, input_img1.width, input_img1.height);

  perf_histogram(input_img1.data, dist, input_img1.width, input_img1.height);
  perf_meanStdDev(input_img1.data, &mean, &stddev, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&mask_img);
  deallocateImage(&dst_img);
  deallocateImage(&dst_img_x);
  deallocateImage(&dst_img_y);
#endif


#ifdef MEDIUM
  loadPGMImage("./raw/256x256/clock.pgm", &input_img1);
  loadPGMImage("./raw/256x256/clock.pgm", &mask_img);
  allocateImage(input_img1.width, input_img1.height, 1, &dst_img);
  allocateImage(input_img1.width, input_img1.height, 2, &dst_img_x);
  allocateImage(input_img1.width, input_img1.height, 2, &dst_img_y);

  perf_box3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_erode(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_dilate(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian5x5(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_median3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_censusTransform(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_nonmaxSuppress3x3(input_img1.data, mask_img.data, dst_img.data, input_img1.width, input_img1.height);
  perf_sobel(input_img1.data, dst_img_x.data, dst_img_y.data, input_img1.width, input_img1.height);

  perf_histogram(input_img1.data, dist, input_img1.width, input_img1.height);
  perf_meanStdDev(input_img1.data, &mean, &stddev, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&mask_img);
  deallocateImage(&dst_img);
  deallocateImage(&dst_img_x);
  deallocateImage(&dst_img_y);
#endif


#ifdef LARGE
  loadPGMImage("./raw/256x256/clock.pgm", &input_img1);
  loadPGMImage("./raw/256x256/clock.pgm", &mask_img);
  allocateImage(input_img1.width, input_img1.height, 1, &dst_img);
  allocateImage(input_img1.width, input_img1.height, 2, &dst_img_x);
  allocateImage(input_img1.width, input_img1.height, 2, &dst_img_y);

  perf_box3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_erode(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_dilate(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian5x5(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_median3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_censusTransform(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_nonmaxSuppress3x3(input_img1.data, mask_img.data, dst_img.data, input_img1.width, input_img1.height);
  perf_sobel(input_img1.data, dst_img_x.data, dst_img_y.data, input_img1.width, input_img1.height);

  perf_histogram(input_img1.data, dist, input_img1.width, input_img1.height);
  perf_meanStdDev(input_img1.data, &mean, &stddev, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&mask_img);
  deallocateImage(&dst_img);
  deallocateImage(&dst_img_x);
  deallocateImage(&dst_img_y);
#endif

#ifdef HUGE
  loadPGMImage("./raw/256x256/clock.pgm", &input_img1);
  loadPGMImage("./raw/256x256/clock.pgm", &mask_img);
  allocateImage(input_img1.width, input_img1.height, 1, &dst_img);
  allocateImage(input_img1.width, input_img1.height, 2, &dst_img_x);
  allocateImage(input_img1.width, input_img1.height, 2, &dst_img_y);

  perf_box3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_erode(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_dilate(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_gaussian5x5(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_median3x3(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_censusTransform(input_img1.data, dst_img.data, input_img1.width, input_img1.height);
  perf_nonmaxSuppress3x3(input_img1.data, mask_img.data, dst_img.data, input_img1.width, input_img1.height);
  perf_sobel(input_img1.data, dst_img_x.data, dst_img_y.data, input_img1.width, input_img1.height);

  perf_histogram(input_img1.data, dist, input_img1.width, input_img1.height);
  perf_meanStdDev(input_img1.data, &mean, &stddev, input_img1.width, input_img1.height);

  deallocateImage(&input_img1);
  deallocateImage(&mask_img);
  deallocateImage(&dst_img);
  deallocateImage(&dst_img_x);
  deallocateImage(&dst_img_y);
#endif
  return 0;
}
