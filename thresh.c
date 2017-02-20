#include "matrix.h"
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define N 256

void thresh_8u(Mat *_src, Mat *_dst, uchar thresh, uchar maxval, int type) {
  Size roi = _src->size;
  roi.width *= _src->channels;
  size_t src_step = _src->step;
  size_t dst_step = _dst->step;

  if (_src->isContinuous && _dst->isContinuous) {
    roi.width *= roi.height;
    roi.height = 1;
    src_step = dst_step = roi.width;
  }

  int j = 0;
  uchar *src = _src->uchar_ptr;
  uchar *dst = _dst->uchar_ptr;

  int j_scalar = j;
  if (j_scalar < roi.width) {
    int thresh_pivot = thresh + 1;
    uchar tab[256];
    switch (type) {
    case THRESH_BINARY:
      memset(tab, 0, thresh_pivot);
      if (thresh_pivot < 256) {
        memset(tab + thresh_pivot, maxval, 256 - thresh_pivot);
      }
      break;
    case THRESH_BINARY_INV:
      memset(tab, maxval, thresh_pivot);
      if (thresh_pivot < 256) {
        memset(tab + thresh_pivot, 0, 256 - thresh_pivot);
      }
      break;
    case THRESH_TRUNC:
      for (int i = 0; i <= thresh; i++)
        tab[i] = (uchar)i;
      if (thresh_pivot < 256) {
        memset(tab + thresh_pivot, thresh, 256 - thresh_pivot);
      }
      break;
    case THRESH_TOZERO:
      memset(tab, 0, thresh_pivot);
      for (int i = thresh_pivot; i < 256; i++)
        tab[i] = (uchar)i;
      break;
    case THRESH_TOZERO_INV:
      for (int i = 0; i <= thresh; i++)
        tab[i] = (uchar)i;
      if (thresh_pivot < 256) {
        memset(tab + thresh_pivot, 0, 256 - thresh_pivot);
      }
      break;
    }

    src = _src->uchar_ptr;
    dst = _dst->uchar_ptr;
    for (int i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
      j = j_scalar;
#if CV_ENABLE_UNROLLED
      for (; j <= roi.width - 4; j += 4) {
        uchar t0 = tab[src[j]];
        uchar t1 = tab[src[j + 1]];

        dst[j] = t0;
        dst[j + 1] = t1;

        t0 = tab[src[j + 2]];
        t1 = tab[src[j + 3]];

        dst[j + 2] = t0;
        dst[j + 3] = t1;
      }
#endif
      for (; j < roi.width; j++)
        dst[j] = tab[src[j]];
    }
  }
}

void thresh_16s(Mat *_src, Mat *_dst, short thresh, short maxval, int type) {
  int i, j;
  Size roi = _src->size;
  roi.width *= _src->channels;
  short *src = _src->short_ptr;
  short *dst = _dst->short_ptr;
  size_t src_step = _src->step / sizeof(src[0]);
  size_t dst_step = _dst->step / sizeof(dst[0]);

  if (_src->isContinuous && _dst->isContinuous) {
    roi.width *= roi.height;
    roi.height = 1;
    src_step = dst_step = roi.width;
  }

  {
    switch (type) {
    case THRESH_BINARY:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++)
          dst[j] = src[j] > thresh ? maxval : 0;
      }
      break;

    case THRESH_BINARY_INV:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++)
          dst[j] = src[j] <= thresh ? maxval : 0;
      }
      break;

    case THRESH_TRUNC:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++)
          dst[j] = min(src[j], thresh);
      }
      break;

    case THRESH_TOZERO:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++) {
          short v = src[j];
          dst[j] = v > thresh ? v : 0;
        }
      }
      break;

    case THRESH_TOZERO_INV:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++) {
          short v = src[j];
          dst[j] = v <= thresh ? v : 0;
        }
      }
      break;
    default:
      return CV_Error("");
    }
  }
}

void thresh_32f(Mat *_src, Mat *_dst, float thresh, float maxval, int type) {
  int i, j;
  Size roi = _src->size;
  roi.width *= _src->channels;
  float *src = _src->float_ptr;
  float *dst = _dst->float_ptr;
  size_t src_step = _src->step / sizeof(src[0]);
  size_t dst_step = _dst->step / sizeof(dst[0]);

  if (_src->isContinuous && _dst->isContinuous) {
    roi.width *= roi.height;
    roi.height = 1;
  }

  {
    switch (type) {
    case THRESH_BINARY:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++)
          dst[j] = src[j] > thresh ? maxval : 0;
      }
      break;

    case THRESH_BINARY_INV:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++)
          dst[j] = src[j] <= thresh ? maxval : 0;
      }
      break;

    case THRESH_TRUNC:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++)
          dst[j] = min(src[j], thresh);
      }
      break;

    case THRESH_TOZERO:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++) {
          float v = src[j];
          dst[j] = v > thresh ? v : 0;
        }
      }
      break;

    case THRESH_TOZERO_INV:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        for (j = 0; j < roi.width; j++) {
          float v = src[j];
          dst[j] = v <= thresh ? v : 0;
        }
      }
      break;
    default:
      return CV_Error("");
    }
  }
}

void thresh_64f(Mat *_src, Mat *_dst, double thresh, double maxval, int type) {
  int i, j;
  Size roi = _src->size;
  roi.width *= _src->channels;
  double *src = _src->double_ptr;
  double *dst = _dst->double_ptr;
  size_t src_step = _src->step / sizeof(src[0]);
  size_t dst_step = _dst->step / sizeof(dst[0]);

  if (_src->isContinuous && _dst->isContinuous) {
    roi.width *= roi.height;
    roi.height = 1;
  }

  {
    switch (type) {
    case THRESH_BINARY:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        j = 0;
        for (; j < roi.width; j++)
          dst[j] = src[j] > thresh ? maxval : 0;
      }
      break;

    case THRESH_BINARY_INV:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        j = 0;
        for (; j < roi.width; j++)
          dst[j] = src[j] <= thresh ? maxval : 0;
      }
      break;

    case THRESH_TRUNC:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        j = 0;
        for (; j < roi.width; j++)
          dst[j] = min(src[j], thresh);
      }
      break;

    case THRESH_TOZERO:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        j = 0;
        for (; j < roi.width; j++) {
          double v = src[j];
          dst[j] = v > thresh ? v : 0;
        }
      }
      break;

    case THRESH_TOZERO_INV:
      for (i = 0; i < roi.height; i++, src += src_step, dst += dst_step) {
        j = 0;
        for (; j < roi.width; j++) {
          double v = src[j];
          dst[j] = v <= thresh ? v : 0;
        }
      }
      break;
    default:
      return CV_Error("");
    }
  }
}

double getThreshVal_Otsu_8u(Mat *_src) {
  Size size = _src->size;
  int step = _src->step;
  if (_src->isContinuous) {
    size.width *= size.height;
    size.height = 1;
    step = size.width;
  }

  int i, j, h[N] = {0};
  for (i = 0; i < size.height; i++) {
    uchar *src = _src->uchar_ptr + step * i;
    j = 0;
#if CV_ENABLE_UNROLLED
    for (; j <= size.width - 4; j += 4) {
      int v0 = src[j], v1 = src[j + 1];
      h[v0]++;
      h[v1]++;
      v0 = src[j + 2];
      v1 = src[j + 3];
      h[v0]++;
      h[v1]++;
    }
#endif
    for (; j < size.width; j++)
      h[src[j]]++;
  }

  double mu = 0, scale = 1. / (size.width * size.height);
  for (i = 0; i < N; i++)
    mu += i * (double)h[i];

  mu *= scale;
  double mu1 = 0, q1 = 0;
  double max_sigma = 0, max_val = 0;

  for (i = 0; i < N; i++) {
    double p_i, q2, mu2, sigma;

    p_i = h[i] * scale;
    mu1 *= q1;
    q1 += p_i;
    q2 = 1. - q1;

    if (min(q1, q2) < FLT_EPSILON || max(q1, q2) > 1. - FLT_EPSILON)
      continue;

    mu1 = (mu1 + i * p_i) / q1;
    mu2 = (mu - q1 * mu1) / q2;
    sigma = q1 * q2 * (mu1 - mu2) * (mu1 - mu2);
    if (sigma > max_sigma) {
      max_sigma = sigma;
      max_val = i;
    }
  }

  return max_val;
}

double getThreshVal_Triangle_8u(Mat *_src) {
  Size size = _src->size;
  int step = _src->step;
  if (_src->isContinuous) {
    size.width *= size.height;
    size.height = 1;
    step = size.width;
  }

  int i, j, h[N] = {0};
  for (i = 0; i < size.height; i++) {
    uchar *src = _src->uchar_ptr + step * i;
    j = 0;
#if CV_ENABLE_UNROLLED
    for (; j <= size.width - 4; j += 4) {
      int v0 = src[j], v1 = src[j + 1];
      h[v0]++;
      h[v1]++;
      v0 = src[j + 2];
      v1 = src[j + 3];
      h[v0]++;
      h[v1]++;
    }
#endif
    for (; j < size.width; j++)
      h[src[j]]++;
  }

  int left_bound = 0, right_bound = 0, max_ind = 0, max = 0;
  int temp;
  bool isflipped = false;

  for (i = 0; i < N; i++) {
    if (h[i] > 0) {
      left_bound = i;
      break;
    }
  }
  if (left_bound > 0)
    left_bound--;

  for (i = N - 1; i > 0; i--) {
    if (h[i] > 0) {
      right_bound = i;
      break;
    }
  }
  if (right_bound < N - 1)
    right_bound++;

  for (i = 0; i < N; i++) {
    if (h[i] > max) {
      max = h[i];
      max_ind = i;
    }
  }

  if (max_ind - left_bound < right_bound - max_ind) {
    isflipped = true;
    i = 0, j = N - 1;
    while (i < j) {
      temp = h[i];
      h[i] = h[j];
      h[j] = temp;
      i++;
      j--;
    }
    left_bound = N - 1 - right_bound;
    max_ind = N - 1 - max_ind;
  }

  double thresh = left_bound;
  double a, b, dist = 0, tempdist;

  /*
   * We do not need to compute precise distance here. Distance is maximized, so
   * some constants can
   * be omitted. This speeds up a computation a bit.
   */
  a = max;
  b = left_bound - max_ind;
  for (i = left_bound + 1; i <= max_ind; i++) {
    tempdist = a * i + b * h[i];
    if (tempdist > dist) {
      dist = tempdist;
      thresh = i;
    }
  }
  thresh--;

  if (isflipped)
    thresh = N - 1 - thresh;

  return thresh;
}

