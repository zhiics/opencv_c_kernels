#ifndef MATRIX_H
#define MATRIX_H
#include "cdefs.h"

typedef struct Size_t {
  int width;
  int height;
} Size;

typedef struct Mat_t {
  uchar isContinuous;
  int channels;
	int step;
  uchar *uchar_ptr;
  short *short_ptr;
  float *float_ptr;
  double *double_ptr;
  Size size;
} Mat;

#endif
