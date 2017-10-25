#include "cdefs.h"
#include <math.h>

void histogram(unsigned char *in, int width, int height, unsigned int *dist,
               int offset, int range, int B) {
  int index;
  int total = width * height;
  for (int i = 0; i < total; ++i) {
    index = (in[i] - offset) * B / range;
    dist[index]++;
  }
}

void eqHistogram(unsigned char *input, int width, int height,
                 unsigned char *output) {
  unsigned int hist[256], cdf[256];

  int index;
  int total = width * height;
  unsigned char minPixel = 255;

  for (int i = 0; i < total; ++i) {
    unsigned char pixel = input[i];
    hist[pixel]++;
    if (pixel < minPixel)
      minPixel = pixel;
  }
  int x;
  int sum = 0;
  // calculate the cumulative distribution (summed histogram)
  for (x = 0; x < 256; x++) {
    sum += hist[x];
    cdf[x] = sum;
  }

  int div_ = (total)-cdf[minPixel];
  if (div_ > 0) {
    /* recompute the histogram to be a LUT for replacing pixel values */
    for (x = 0; x < 256; x++) {
      uint32_t cdfx = cdf[x] - cdf[minPixel];
      float p = (float)cdfx / (float)div_;
      hist[x] = (unsigned char)(p * 255.0f + 0.5f);
    }
  } else {
    for (x = 0; x < 256; x++) {
      hist[x] = x;
    }
  }

  for (int i = 0; i < total; ++i) {
    output[i] = hist[input[i]];
  }
}

// stddev is optional
void mean(unsigned char *input, int width, int height, float* _mean) {
  int total = width * height;

  unsigned int accum = 0;
  for (int i = 0; i < total; i++) {
    accum += input[i];
  }
  *_mean = (accum) / (float)total;
}

void meanStdDev(unsigned char *input, int width, int height, float *_mean,
                float *stddev) {
  int total = width * height;

  float __mean;
  // Pass1 : calculate mean
  mean(input, width, height, &__mean);

  // Pass2 : calculate standard deviation
  unsigned int accum = 0;
  for (int i = 0; i < total; i++) {
    int diff = *_mean - input[i];
    accum += (diff * diff);
  }
  *_mean = __mean;
  *stddev = sqrt(accum / (float)total);
}

