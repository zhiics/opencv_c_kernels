#include "cdefs.h"
#include "morph.h"
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

void morphrowfilter_min_uchar(uchar *src, uchar *dst, int width, int cn,
                              int ksize) {
  int i, j, k, _ksize = ksize * cn;
  uchar *S = src;
  uchar *D = dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      uchar *s = S + i;
      uchar m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = min(m, s[0]);
      D[i + cn] = min(m, s[j]);
    }

    for (; i < width; i += cn) {
      uchar *s = S + i;
      uchar m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_min_ushort(uchar *src, uchar *dst, int width, int cn,
                               int ksize) {
  int i, j, k, _ksize = ksize * cn;
  ushort *S = (ushort *)src;
  ushort *D = (ushort *)dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      ushort *s = S + i;
      ushort m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = min(m, s[0]);
      D[i + cn] = min(m, s[j]);
    }

    for (; i < width; i += cn) {
      const ushort *s = S + i;
      ushort m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_min_short(uchar *src, uchar *dst, int width, int cn,
                              int ksize) {
  int i, j, k, _ksize = ksize * cn;
  short *S = (short *)src;
  short *D = (short *)dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      short *s = S + i;
      short m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = min(m, s[j]); D[i] = min(m, s[0]); D[i + cn] = min(m, s[j]);
    }

    for (; i < width; i += cn) {
      short *s = S + i;
      short m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_min_float(uchar *src, uchar *dst, int width, int cn,
                              int ksize) {
  int i, j, k, _ksize = ksize * cn;
  float *S = (float *)src;
  float *D = (float *)dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      float *s = S + i;
      float m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = min(m, s[0]);
      D[i + cn] = min(m, s[j]);
    }

    for (; i < width; i += cn) {
      float *s = S + i;
      float m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_min_double(uchar *src, uchar *dst, int width, int cn,
                               int ksize) {
  int i, j, k, _ksize = ksize * cn;
  double *S = (double *)src;
  double *D = (double *)dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      double *s = S + i;
      double m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = min(m, s[0]);
      D[i + cn] = min(m, s[j]);
    }

    for (; i < width; i += cn) {
      double *s = S + i;
      double m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = min(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_max_uchar(uchar *src, uchar *dst, int width, int cn,
                              int ksize) {
  int i, j, k, _ksize = ksize * cn;
  uchar *S = src;
  uchar *D = dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      uchar *s = S + i;
      uchar m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = max(m, s[0]);
      D[i + cn] = max(m, s[j]);
    }

    for (; i < width; i += cn) {
      uchar *s = S + i;
      uchar m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_max_ushort(uchar *src, uchar *dst, int width, int cn,
                               int ksize) {
  int i, j, k, _ksize = ksize * cn;
  ushort *S = (ushort *)src;
  ushort *D = (ushort *)dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      ushort *s = S + i;
      ushort m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = max(m, s[0]);
      D[i + cn] = max(m, s[j]);
    }

    for (; i < width; i += cn) {
      const ushort *s = S + i;
      ushort m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_max_short(uchar *src, uchar *dst, int width, int cn,
                              int ksize) {
  int i, j, k, _ksize = ksize * cn;
  short *S = (short *)src;
  short *D = (short *)dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      short *s = S + i;
      short m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = max(m, s[0]);
      D[i + cn] = max(m, s[j]);
    }

    for (; i < width; i += cn) {
      short *s = S + i;
      short m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_max_float(uchar *src, uchar *dst, int width, int cn,
                              int ksize) {
  int i, j, k, _ksize = ksize * cn;
  float *S = (float *)src;
  float *D = (float *)dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      float *s = S + i;
      float m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = max(m, s[0]);
      D[i + cn] = max(m, s[j]);
    }

    for (; i < width; i += cn) {
      float *s = S + i;
      float m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = m;
    }
  }
}

void morphrowfilter_max_double(uchar *src, uchar *dst, int width, int cn,
                               int ksize) {
  int i, j, k, _ksize = ksize * cn;
  double *S = (double *)src;
  double *D = (double *)dst;

  if (_ksize == cn) {
    for (i = 0; i < width * cn; i++)
      D[i] = S[i];
    return;
  }

  int i0 = 0;
  width *= cn;

  for (k = 0; k < cn; k++, S++, D++) {
    for (i = i0; i <= width - cn * 2; i += cn * 2) {
      double *s = S + i;
      double m = s[cn];
      for (j = cn * 2; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = max(m, s[0]);
      D[i + cn] = max(m, s[j]);
    }

    for (; i < width; i += cn) {
      double *s = S + i;
      double m = s[0];
      for (j = cn; j < _ksize; j += cn)
        m = max(m, s[j]);
      D[i] = m;
    }
  }
}

void morphcolumnfilter_min_uchar(uchar **_src, uchar *dst, int dststep,
                                 int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  uchar **src = (uchar **)_src;
  uchar *D = (uchar *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      uchar *sptr = src[1] + i;
      uchar s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = min(s0, sptr[0]);
      D[i + 1] = min(s1, sptr[1]);
      D[i + 2] = min(s2, sptr[2]);
      D[i + 3] = min(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = min(s0, sptr[0]);
      D[i + dststep + 1] = min(s1, sptr[1]);
      D[i + dststep + 2] = min(s2, sptr[2]);
      D[i + dststep + 3] = min(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      uchar s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = min(s0, src[k][i]);

      D[i] = min(s0, src[0][i]);
      D[i + dststep] = min(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      uchar *sptr = src[0] + i;
      uchar s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      uchar s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = min(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_min_ushort(uchar **_src, uchar *dst, int dststep,
                                  int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  ushort **src = (ushort **)_src;
  ushort *D = (ushort *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      ushort *sptr = src[1] + i;
      ushort s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = min(s0, sptr[0]);
      D[i + 1] = min(s1, sptr[1]);
      D[i + 2] = min(s2, sptr[2]);
      D[i + 3] = min(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = min(s0, sptr[0]);
      D[i + dststep + 1] = min(s1, sptr[1]);
      D[i + dststep + 2] = min(s2, sptr[2]);
      D[i + dststep + 3] = min(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      ushort s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = min(s0, src[k][i]);

      D[i] = min(s0, src[0][i]);
      D[i + dststep] = min(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      ushort *sptr = src[0] + i;
      ushort s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      ushort s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = min(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_min_short(uchar **_src, uchar *dst, int dststep,
                                 int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  short **src = (short **)_src;
  short *D = (short *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      short *sptr = src[1] + i;
      short s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = min(s0, sptr[0]);
      D[i + 1] = min(s1, sptr[1]);
      D[i + 2] = min(s2, sptr[2]);
      D[i + 3] = min(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = min(s0, sptr[0]);
      D[i + dststep + 1] = min(s1, sptr[1]);
      D[i + dststep + 2] = min(s2, sptr[2]);
      D[i + dststep + 3] = min(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      short s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = min(s0, src[k][i]);

      D[i] = min(s0, src[0][i]);
      D[i + dststep] = min(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      short *sptr = src[0] + i;
      short s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      short s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = min(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_min_float(uchar **_src, uchar *dst, int dststep,
                                 int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  float **src = (float **)_src;
  float *D = (float *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      float *sptr = src[1] + i;
      float s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = min(s0, sptr[0]);
      D[i + 1] = min(s1, sptr[1]);
      D[i + 2] = min(s2, sptr[2]);
      D[i + 3] = min(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = min(s0, sptr[0]);
      D[i + dststep + 1] = min(s1, sptr[1]);
      D[i + dststep + 2] = min(s2, sptr[2]);
      D[i + dststep + 3] = min(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      float s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = min(s0, src[k][i]);

      D[i] = min(s0, src[0][i]);
      D[i + dststep] = min(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      float *sptr = src[0] + i;
      float s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      float s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = min(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_min_double(uchar **_src, uchar *dst, int dststep,
                                  int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  double **src = (double **)_src;
  double *D = (double *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      double *sptr = src[1] + i;
      double s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = min(s0, sptr[0]);
      D[i + 1] = min(s1, sptr[1]);
      D[i + 2] = min(s2, sptr[2]);
      D[i + 3] = min(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = min(s0, sptr[0]);
      D[i + dststep + 1] = min(s1, sptr[1]);
      D[i + dststep + 2] = min(s2, sptr[2]);
      D[i + dststep + 3] = min(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      double s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = min(s0, src[k][i]);

      D[i] = min(s0, src[0][i]);
      D[i + dststep] = min(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      double *sptr = src[0] + i;
      double s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      double s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = min(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_max_uchar(uchar **_src, uchar *dst, int dststep,
                                 int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  uchar **src = (uchar **)_src;
  uchar *D = (uchar *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      uchar *sptr = src[1] + i;
      uchar s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = max(s0, sptr[0]);
      D[i + 1] = max(s1, sptr[1]);
      D[i + 2] = max(s2, sptr[2]);
      D[i + 3] = max(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = max(s0, sptr[0]);
      D[i + dststep + 1] = max(s1, sptr[1]);
      D[i + dststep + 2] = max(s2, sptr[2]);
      D[i + dststep + 3] = max(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      uchar s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = max(s0, src[k][i]);

      D[i] = max(s0, src[0][i]);
      D[i + dststep] = max(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      uchar *sptr = src[0] + i;
      uchar s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      uchar s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = max(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_max_ushort(uchar **_src, uchar *dst, int dststep,
                                  int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  ushort **src = (ushort **)_src;
  ushort *D = (ushort *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      ushort *sptr = src[1] + i;
      ushort s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = max(s0, sptr[0]);
      D[i + 1] = max(s1, sptr[1]);
      D[i + 2] = max(s2, sptr[2]);
      D[i + 3] = max(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = max(s0, sptr[0]);
      D[i + dststep + 1] = max(s1, sptr[1]);
      D[i + dststep + 2] = max(s2, sptr[2]);
      D[i + dststep + 3] = max(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      ushort s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = max(s0, src[k][i]);

      D[i] = max(s0, src[0][i]);
      D[i + dststep] = max(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      ushort *sptr = src[0] + i;
      ushort s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      ushort s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = max(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_max_short(uchar **_src, uchar *dst, int dststep,
                                 int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  short **src = (short **)_src;
  short *D = (short *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      short *sptr = src[1] + i;
      short s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = max(s0, sptr[0]);
      D[i + 1] = max(s1, sptr[1]);
      D[i + 2] = max(s2, sptr[2]);
      D[i + 3] = max(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = max(s0, sptr[0]);
      D[i + dststep + 1] = max(s1, sptr[1]);
      D[i + dststep + 2] = max(s2, sptr[2]);
      D[i + dststep + 3] = max(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      short s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = max(s0, src[k][i]);

      D[i] = max(s0, src[0][i]);
      D[i + dststep] = max(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      short *sptr = src[0] + i;
      short s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      short s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = max(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_max_float(uchar **_src, uchar *dst, int dststep,
                                 int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  float **src = (float **)_src;
  float *D = (float *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      float *sptr = src[1] + i;
      float s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = max(s0, sptr[0]);
      D[i + 1] = max(s1, sptr[1]);
      D[i + 2] = max(s2, sptr[2]);
      D[i + 3] = max(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = max(s0, sptr[0]);
      D[i + dststep + 1] = max(s1, sptr[1]);
      D[i + dststep + 2] = max(s2, sptr[2]);
      D[i + dststep + 3] = max(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      float s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = max(s0, src[k][i]);

      D[i] = max(s0, src[0][i]);
      D[i + dststep] = max(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      float *sptr = src[0] + i;
      float s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      float s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = max(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphcolumnfilter_max_double(uchar **_src, uchar *dst, int dststep,
                                  int count, int width, int ksize) {
  int i, k, _ksize = ksize;
  double **src = (double **)_src;
  double *D = (double *)dst;

  int i0 = 0;
  dststep /= sizeof(D[0]);

  for (; _ksize > 1 && count > 1; count -= 2, D += dststep * 2, src += 2) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      double *sptr = src[1] + i;
      double s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 2; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      sptr = src[0] + i;
      D[i] = max(s0, sptr[0]);
      D[i + 1] = max(s1, sptr[1]);
      D[i + 2] = max(s2, sptr[2]);
      D[i + 3] = max(s3, sptr[3]);

      sptr = src[k] + i;
      D[i + dststep] = max(s0, sptr[0]);
      D[i + dststep + 1] = max(s1, sptr[1]);
      D[i + dststep + 2] = max(s2, sptr[2]);
      D[i + dststep + 3] = max(s3, sptr[3]);
    }
#endif
    for (; i < width; i++) {
      double s0 = src[1][i];

      for (k = 2; k < _ksize; k++)
        s0 = max(s0, src[k][i]);

      D[i] = max(s0, src[0][i]);
      D[i + dststep] = max(s0, src[k][i]);
    }
  }

  for (; count > 0; count--, D += dststep, src++) {
    i = i0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      double *sptr = src[0] + i;
      double s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < _ksize; k++) {
        sptr = src[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      double s0 = src[0][i];
      for (k = 1; k < _ksize; k++)
        s0 = max(s0, src[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_min_uchar(uchar **src, uchar *dst, int dststep, int count,
                           int width, int cn, Point *coords, int size,
                           uchar **ptrs) {
  Point *pt = coords;
  uchar **kp = (uchar **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    uchar *D = (uchar *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (uchar *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      uchar *sptr = kp[0] + i;
      uchar s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      uchar s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = min(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_min_ushort(const uchar **src, uchar *dst, int dststep,
                            int count, int width, int cn, Point *coords,
                            int size, uchar **ptrs) {
  Point *pt = coords;
  ushort **kp = (ushort **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    ushort *D = (ushort *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (ushort *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      ushort *sptr = kp[0] + i;
      ushort s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      ushort s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = min(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_min_short(const uchar **src, uchar *dst, int dststep,
                            int count, int width, int cn, Point *coords,
                            int size, uchar **ptrs) {
  Point *pt = coords;
  short **kp = (short **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    short *D = (short *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (short *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      short *sptr = kp[0] + i;
      short s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      short s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = min(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_min_float(const uchar **src, uchar *dst, int dststep,
                            int count, int width, int cn, Point *coords,
                            int size, uchar **ptrs) {
  Point *pt = coords;
  float **kp = (float **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    float *D = (float *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (float *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      float *sptr = kp[0] + i;
      float s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      float s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = min(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_min_double(const uchar **src, uchar *dst, int dststep,
                            int count, int width, int cn, Point *coords,
                            int size, uchar **ptrs) {
  Point *pt = coords;
  double **kp = (double **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    double *D = (double *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (double *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      double *sptr = kp[0] + i;
      double s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = min(s0, sptr[0]);
        s1 = min(s1, sptr[1]);
        s2 = min(s2, sptr[2]);
        s3 = min(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      double s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = min(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_max_uchar(uchar **src, uchar *dst, int dststep, int count,
                           int width, int cn, Point *coords, int size,
                           uchar **ptrs) {
  Point *pt = coords;
  uchar **kp = (uchar **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    uchar *D = (uchar *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (uchar *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      uchar *sptr = kp[0] + i;
      uchar s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      uchar s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = max(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_max_ushort(const uchar **src, uchar *dst, int dststep,
                            int count, int width, int cn, Point *coords,
                            int size, uchar **ptrs) {
  Point *pt = coords;
  ushort **kp = (ushort **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    ushort *D = (ushort *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (ushort *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      ushort *sptr = kp[0] + i;
      ushort s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      ushort s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = max(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_max_short(const uchar **src, uchar *dst, int dststep,
                            int count, int width, int cn, Point *coords,
                            int size, uchar **ptrs) {
  Point *pt = coords;
  short **kp = (short **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    short *D = (short *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (short *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      short *sptr = kp[0] + i;
      short s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      short s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = max(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_max_float(const uchar **src, uchar *dst, int dststep,
                            int count, int width, int cn, Point *coords,
                            int size, uchar **ptrs) {
  Point *pt = coords;
  float **kp = (float **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    float *D = (float *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (float *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      float *sptr = kp[0] + i;
      float s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      float s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = max(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

void morphfilter_max_double(const uchar **src, uchar *dst, int dststep,
                            int count, int width, int cn, Point *coords,
                            int size, uchar **ptrs) {
  Point *pt = coords;
  double **kp = (double **)ptrs;
  int i, k, nz = size;

  width *= cn;
  for (; count > 0; count--, dst += dststep, src++) {
    double *D = (double *)dst;

    for (k = 0; k < nz; k++)
      kp[k] = (double *)src[pt[k].y] + pt[k].x * cn;

    i = 0;
#if CV_ENABLE_UNROLLED
    for (; i <= width - 4; i += 4) {
      double *sptr = kp[0] + i;
      double s0 = sptr[0], s1 = sptr[1], s2 = sptr[2], s3 = sptr[3];

      for (k = 1; k < nz; k++) {
        sptr = kp[k] + i;
        s0 = max(s0, sptr[0]);
        s1 = max(s1, sptr[1]);
        s2 = max(s2, sptr[2]);
        s3 = max(s3, sptr[3]);
      }

      D[i] = s0;
      D[i + 1] = s1;
      D[i + 2] = s2;
      D[i + 3] = s3;
    }
#endif
    for (; i < width; i++) {
      double s0 = kp[0][i];
      for (k = 1; k < nz; k++)
        s0 = max(s0, kp[k][i]);
      D[i] = s0;
    }
  }
}

int main() {}
