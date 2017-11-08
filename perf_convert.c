#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include "cdefs.h"
#include <stdlib.h>
#include "util.h"

#include "convert.c"

#define SMALL
#define MEDIUM
#define LARGE
#define HUGE


void perf_color_convert(unsigned char *input, unsigned char *output, int width, int height, int convert_code) {
  struct timespec t1, t2;

  getTime(&t1);
  if (convert_code == 0) // RGB to NV12
    colorConvert(input, width, height, RGB, NV12, output);
  else // NV12 to RGB
    colorConvert(input, width, height, NV12, RGB, output);
  getTime(&t2);

  unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;
  printf("Test colorConvert %s took %lu nanoseconds.\n", (convert_code==0)?"RGB2YUV":"YUV2RGB", duration); \
  return;
}

void perf_channel_convert(unsigned char *input, unsigned char *output, int width, int height, int convert_code, int policy) {
  struct timespec t1, t2;
  int shift = 4;

  getTime(&t1);
  if (convert_code == 0) // U8 to S16
    convertDepth(input, width, height, U8, S16, output, policy, shift);
  else // S16 to U8
    convertDepth(input, width, height, S16, U8, output, policy, shift);
  getTime(&t2);

  unsigned long duration = (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec)*1000000000;
  printf("Test depthConvert %s  with policy took %lu nanoseconds.\n", convert_code==0?"U8toS16":"S16toU8", duration, policy); \
  return;
}

int main() {

  size_t step = 1;
  int ksize = 5;

  // Uchar (UHD) tests
  struct TestImage rgb_img, yuv_image, grayscale_img, short_img;

#ifdef SMALL
  loadPGMImage("./raw/256x256/clock.pgm", &grayscale_img);

  allocateImage(grayscale_img.width, grayscale_img.height, 3, &rgb_img);
  allocateImage(grayscale_img.width, grayscale_img.height, 2, &short_img);
  allocateImage(grayscale_img.width+grayscale_img.width/2, grayscale_img.height, 1, &yuv_image);

  perf_color_convert(rgb_img.data, yuv_image.data, rgb_img.width, rgb_img.height, 0);
  perf_color_convert(yuv_image.data, rgb_img.data, rgb_img.width, rgb_img.height, 1);

  perf_channel_convert(grayscale_img.data, short_img.data, grayscale_img.width, grayscale_img.height, 0, 0);
  perf_channel_convert(short_img.data, grayscale_img.data, grayscale_img.width, grayscale_img.height, 1, WRAP);
  perf_channel_convert(short_img.data, grayscale_img.data, grayscale_img.width, grayscale_img.height, 1, SATURATE);


  deallocateImage(&rgb_img);
  deallocateImage(&yuv_image);
  deallocateImage(&grayscale_img);
  deallocateImage(&short_img);
#endif


#ifdef MEDIUM
  loadPGMImage("./raw/512x512/mandrill.pgm", &grayscale_img);

  allocateImage(grayscale_img.width, grayscale_img.height, 3, &rgb_img);
  allocateImage(grayscale_img.width, grayscale_img.height, 2, &short_img);
  allocateImage(grayscale_img.width+grayscale_img.width/2, grayscale_img.height, 1, &yuv_image);

  perf_color_convert(rgb_img.data, yuv_image.data, rgb_img.width, rgb_img.height, 0);
  perf_color_convert(yuv_image.data, rgb_img.data, rgb_img.width, rgb_img.height, 1);

  perf_channel_convert(grayscale_img.data, short_img.data, grayscale_img.width, grayscale_img.height, 0, 0);
  perf_channel_convert(short_img.data, grayscale_img.data, grayscale_img.width, grayscale_img.height, 1, WRAP);
  perf_channel_convert(short_img.data, grayscale_img.data, grayscale_img.width, grayscale_img.height, 1, SATURATE);


  deallocateImage(&rgb_img);
  deallocateImage(&yuv_image);
  deallocateImage(&grayscale_img);
  deallocateImage(&short_img);
#endif


#ifdef LARGE
  loadPGMImage("./raw/1024x1024/pirate.pgm", &grayscale_img);

  allocateImage(grayscale_img.width, grayscale_img.height, 3, &rgb_img);
  allocateImage(grayscale_img.width, grayscale_img.height, 2, &short_img);
  allocateImage(grayscale_img.width+grayscale_img.width/2, grayscale_img.height, 1, &yuv_image);

  perf_color_convert(rgb_img.data, yuv_image.data, rgb_img.width, rgb_img.height, 0);
  perf_color_convert(yuv_image.data, rgb_img.data, rgb_img.width, rgb_img.height, 1);

  perf_channel_convert(grayscale_img.data, short_img.data, grayscale_img.width, grayscale_img.height, 0, 0);
  perf_channel_convert(short_img.data, grayscale_img.data, grayscale_img.width, grayscale_img.height, 1, WRAP);
  perf_channel_convert(short_img.data, grayscale_img.data, grayscale_img.width, grayscale_img.height, 1, SATURATE);


  deallocateImage(&rgb_img);
  deallocateImage(&yuv_image);
  deallocateImage(&grayscale_img);
deallocateImage(&short_img);
#endif

#ifdef HUGE
  loadPGMImage("./raw/uhd/scarf.pgm", &grayscale_img);

  allocateImage(grayscale_img.width, grayscale_img.height, 3, &rgb_img);
  allocateImage(grayscale_img.width, grayscale_img.height, 2, &short_img);
  allocateImage(grayscale_img.width+grayscale_img.width/2, grayscale_img.height, 1, &yuv_image);

  perf_color_convert(rgb_img.data, yuv_image.data, rgb_img.width, rgb_img.height, 0);
  perf_color_convert(yuv_image.data, rgb_img.data, rgb_img.width, rgb_img.height, 1);

  perf_channel_convert(grayscale_img.data, short_img.data, grayscale_img.width, grayscale_img.height, 0, 0);
  perf_channel_convert(short_img.data, grayscale_img.data, grayscale_img.width, grayscale_img.height, 1, WRAP);
  perf_channel_convert(short_img.data, grayscale_img.data, grayscale_img.width, grayscale_img.height, 1, SATURATE);


  deallocateImage(&rgb_img);
  deallocateImage(&yuv_image);
  deallocateImage(&grayscale_img);
  deallocateImage(&short_img);
#endif
  return 0;
}
