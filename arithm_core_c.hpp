#include <stddef.h>
#include "cdefs.h"
#include <stdio.h>
/*******************************************************************
 *                  different version of add operations            *
 ******************************************************************/

int add_uchar(uchar *src1, size_t step1, uchar *src2, size_t step2,
                  uchar *dst, size_t step, int width, int height) {


  for (; height--; src1 = (uchar *)((const uchar *)src1 + step1),
                   src2 = (uchar *)((const uchar *)src2 + step2),
                   dst = (uchar *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      uchar v0 = saturate_cast_uchar_ushort(src1[x] + src2[x]);
      uchar v1 = saturate_cast_uchar_ushort(src1[x + 1] + src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_uchar_ushort(src1[x + 2] + src2[x + 2]);
      v1 = saturate_cast_uchar_ushort(src1[x + 3] + src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_uchar_ushort(src1[x] + src2[x]);
  }
  return 0;
}

int add_schar(schar *src1, size_t step1, schar *src2, size_t step2,
                  schar *dst, size_t step, int width, int height) {

  for (; height--; src1 = (schar *)((const uchar *)src1 + step1),
                   src2 = (schar *)((const uchar *)src2 + step2),
                   dst = (schar *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      schar v0 = saturate_cast_schar_short(src1[x] + src2[x]);
      schar v1 = saturate_cast_schar_short(src1[x + 1] + src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_schar_short(src1[x + 2] + src2[x + 2]);
      v1 = saturate_cast_schar_short(src1[x + 3] + src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_schar_short(src1[x] + src2[x]);
  }
  return 0;
}

int add_short(short *src1, size_t step1, short *src2, size_t step2,
                  short *dst, size_t step, int width, int height) {

  for (; height--; src1 = (short *)((const uchar *)src1 + step1),
                   src2 = (short *)((const uchar *)src2 + step2),
                   dst = (short *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      short v0 = saturate_cast_short_int(src1[x] + src2[x]);
      short v1 = saturate_cast_short_int(src1[x + 1] + src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_short_int(src1[x + 2] + src2[x + 2]);
      v1 = saturate_cast_short_int(src1[x + 3] + src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_short_int(src1[x] + src2[x]);
  }
  return 0;
}

int add_int32(int *src1, size_t step1, int *src2, size_t step2,
                  int *dst, size_t step, int width, int height) {

  for (; height--; src1 = (int *)((const uchar *)src1 + step1),
                   src2 = (int *)((const uchar *)src2 + step2),
                   dst = (int *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      int v0 = saturate_cast_int(src1[x] + src2[x]);
      int v1 = saturate_cast_int(src1[x + 1] + src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_int(src1[x + 2] + src2[x + 2]);
      v1 = saturate_cast_int(src1[x + 3] + src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_int(src1[x] + src2[x]);
  }
}

float add_float(float *src1, size_t step1, float *src2, size_t step2,
                  float *dst, size_t step, float width, float height) {

  for (; height--; src1 = (float *)((const uchar *)src1 + step1),
                   src2 = (float *)((const uchar *)src2 + step2),
                   dst = (float *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      float v0 = saturate_cast_float(src1[x] + src2[x]);
      float v1 = saturate_cast_float(src1[x + 1] + src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_float(src1[x + 2] + src2[x + 2]);
      v1 = saturate_cast_float(src1[x + 3] + src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_float(src1[x] + src2[x]);
  }
}

/*******************************************************************
 *                  different version of sub operations            *
 ******************************************************************/

uchar sub_uchar(uchar *src1, size_t step1, uchar *src2, size_t step2,
                  uchar *dst, size_t step, int width, int height) {

  for (; height--; src1 = (uchar *)((const uchar *)src1 + step1),
                   src2 = (uchar *)((const uchar *)src2 + step2),
                   dst = (uchar *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      uchar v0 = saturate_cast_uchar_schar(src1[x] - src2[x]);
      uchar v1 = saturate_cast_uchar_ushort(src1[x + 1] - src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_uchar_ushort(src1[x + 2] - src2[x + 2]);
      v1 = saturate_cast_uchar_ushort(src1[x + 3] - src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_uchar_short(src1[x] - src2[x]);
  }
}

schar sub_schar(schar *src1, size_t step1, schar *src2, size_t step2,
                  schar *dst, size_t step, int width, int height) {

  for (; height--; src1 = (schar *)((const uchar *)src1 + step1),
                   src2 = (schar *)((const uchar *)src2 + step2),
                   dst = (schar *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      schar v0 = saturate_cast_schar_short(src1[x] - src2[x]);
      schar v1 = saturate_cast_schar_short(src1[x + 1] - src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_schar_short(src1[x + 2] - src2[x + 2]);
      v1 = saturate_cast_schar_short(src1[x + 3] - src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_schar_short(src1[x] - src2[x]);
  }
}

short sub_short(short *src1, size_t step1, short *src2, size_t step2,
                  short *dst, size_t step, int width, int height) {

  for (; height--; src1 = (short *)((const uchar *)src1 + step1),
                   src2 = (short *)((const uchar *)src2 + step2),
                   dst = (short *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      short v0 = saturate_cast_short_int(src1[x] - src2[x]);
      short v1 = saturate_cast_short_int(src1[x + 1] - src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_short_int(src1[x + 2] - src2[x + 2]);
      v1 = saturate_cast_short_int(src1[x + 3] - src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_short_int(src1[x] - src2[x]);
  }
}

int sub_int32(int *src1, size_t step1, int *src2, size_t step2,
                  int *dst, size_t step, int width, int height) {

  for (; height--; src1 = (int *)((const uchar *)src1 + step1),
                   src2 = (int *)((const uchar *)src2 + step2),
                   dst = (int *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      int v0 = saturate_cast_int(src1[x] - src2[x]);
      int v1 = saturate_cast_int(src1[x + 1] - src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_int(src1[x + 2] - src2[x + 2]);
      v1 = saturate_cast_int(src1[x + 3] - src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_int(src1[x] - src2[x]);
  }
}

float sub_float(float *src1, size_t step1, float *src2, size_t step2,
                  float *dst, size_t step, float width, float height) {

  for (; height--; src1 = (float *)((const uchar *)src1 + step1),
                   src2 = (float *)((const uchar *)src2 + step2),
                   dst = (float *)((uchar *)dst + step)) {
    int x = 0;

#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      float v0 = saturate_cast_float(src1[x] - src2[x]);
      float v1 = saturate_cast_float(src1[x + 1] - src2[x + 1]);
      dst[x] = v0;
      dst[x + 1] = v1;
      v0 = saturate_cast_float(src1[x + 2] - src2[x + 2]);
      v1 = saturate_cast_float(src1[x + 3] - src2[x + 3]);
      dst[x + 2] = v0;
      dst[x + 3] = v1;
    }
#endif

    for (; x < width; x++)
      dst[x] = saturate_cast_float(src1[x] - src2[x]);
  }
}

/*******************************************************************
 *                  different version of cmp operations            *
 ******************************************************************/

void cmp_uchar(uchar *src1, size_t step1, uchar *src2, size_t step2, uchar *dst,
     size_t step, int width, int height, int code) {

    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);

    if( code == CMP_GE || code == CMP_LT )
    {
        swap(*src1, *src2, uchar);
        swap(step1, step2, size_t);
        code = code == CMP_GE ? CMP_LE : CMP_GT;
    }
    if( code == CMP_GT || code == CMP_LE )
    {
        int m = code == CMP_GT ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] > src2[x]) ^ m;
                t1 = -(src1[x+1] > src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] > src2[x+2]) ^ m;
                t1 = -(src1[x+3] > src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] > src2[x]) ^ m);
        }
    }
    else if( code == CMP_EQ || code == CMP_NE )
    {
        int m = code == CMP_EQ ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] == src2[x]) ^ m;
                t1 = -(src1[x+1] == src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] == src2[x+2]) ^ m;
                t1 = -(src1[x+3] == src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] == src2[x]) ^ m);
        }
    }

}

void cmp_schar(schar *src1, size_t step1, schar *src2, size_t step2, uchar *dst,
     size_t step, int width, int height, int code) {

    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);

    if( code == CMP_GE || code == CMP_LT )
    {
        swap(*src1, *src2, schar);
        swap(step1, step2, size_t);
        code = code == CMP_GE ? CMP_LE : CMP_GT;
    }

    if( code == CMP_GT || code == CMP_LE )
    {
        int m = code == CMP_GT ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] > src2[x]) ^ m;
                t1 = -(src1[x+1] > src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] > src2[x+2]) ^ m;
                t1 = -(src1[x+3] > src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] > src2[x]) ^ m);
        }
    }
    else if( code == CMP_EQ || code == CMP_NE )
    {
        int m = code == CMP_EQ ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] == src2[x]) ^ m;
                t1 = -(src1[x+1] == src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] == src2[x+2]) ^ m;
                t1 = -(src1[x+3] == src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] == src2[x]) ^ m);
        }
    }

}

void cmp_short(short *src1, size_t step1, short *src2, size_t step2, uchar *dst,
     size_t step, int width, int height, int code) {

    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);

    if( code == CMP_GE || code == CMP_LT )
    {
        swap(*src1, *src2, short);
        swap(step1, step2, size_t);
        code = code == CMP_GE ? CMP_LE : CMP_GT;
    }

    if( code == CMP_GT || code == CMP_LE )
    {
        int m = code == CMP_GT ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] > src2[x]) ^ m;
                t1 = -(src1[x+1] > src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] > src2[x+2]) ^ m;
                t1 = -(src1[x+3] > src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] > src2[x]) ^ m);
        }
    }
    else if( code == CMP_EQ || code == CMP_NE )
    {
        int m = code == CMP_EQ ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] == src2[x]) ^ m;
                t1 = -(src1[x+1] == src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] == src2[x+2]) ^ m;
                t1 = -(src1[x+3] == src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] == src2[x]) ^ m);
        }
    }

}

void cmp_int32(int *src1, size_t step1, int *src2, size_t step2, uchar *dst,
     size_t step, int width, int height, int code) {

    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);

    if( code == CMP_GE || code == CMP_LT )
    {
        swap(*src1, *src2, int);
        swap(step1, step2, size_t);
        code = code == CMP_GE ? CMP_LE : CMP_GT;
    }

    if( code == CMP_GT || code == CMP_LE )
    {
        int m = code == CMP_GT ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] > src2[x]) ^ m;
                t1 = -(src1[x+1] > src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] > src2[x+2]) ^ m;
                t1 = -(src1[x+3] > src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] > src2[x]) ^ m);
        }
    }
    else if( code == CMP_EQ || code == CMP_NE )
    {
        int m = code == CMP_EQ ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] == src2[x]) ^ m;
                t1 = -(src1[x+1] == src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] == src2[x+2]) ^ m;
                t1 = -(src1[x+3] == src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] == src2[x]) ^ m);
        }
    }

}

void cmp_float(float *src1, size_t step1, float *src2, size_t step2, uchar *dst,
     size_t step, int width, int height, int code) {

    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);

    if( code == CMP_GE || code == CMP_LT )
    {
        swap(*src1, *src2, float);
        swap(step1, step2, size_t);
        code = code == CMP_GE ? CMP_LE : CMP_GT;
    }

    if( code == CMP_GT || code == CMP_LE )
    {
        int m = code == CMP_GT ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] > src2[x]) ^ m;
                t1 = -(src1[x+1] > src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] > src2[x+2]) ^ m;
                t1 = -(src1[x+3] > src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] > src2[x]) ^ m);
        }
    }
    else if( code == CMP_EQ || code == CMP_NE )
    {
        int m = code == CMP_EQ ? 0 : 255;
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int x = 0;
            #if CV_ENABLE_UNROLLED
            for( ; x <= width - 4; x += 4 )
            {
                int t0, t1;
                t0 = -(src1[x] == src2[x]) ^ m;
                t1 = -(src1[x+1] == src2[x+1]) ^ m;
                dst[x] = (uchar)t0; dst[x+1] = (uchar)t1;
                t0 = -(src1[x+2] == src2[x+2]) ^ m;
                t1 = -(src1[x+3] == src2[x+3]) ^ m;
                dst[x+2] = (uchar)t0; dst[x+3] = (uchar)t1;
            }
            #endif
            for( ; x < width; x++ )
                dst[x] = (uchar)(-(src1[x] == src2[x]) ^ m);
        }
    }

}

/*******************************************************************
 *                  different version of mul operations            *
 ******************************************************************/
void mul_uchar(uchar *src1, size_t step1, uchar* src2, size_t step2,
      uchar* dst, size_t step, int width, int height, float scale)
{
    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);
    step /= sizeof(dst[0]);

    if( scale == (float)1. )
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                uchar t0 = saturate_cast_uchar_ushort(src1[i  ] * src2[i  ]);
                uchar t1 = saturate_cast_uchar_ushort(src1[i+1] * src2[i+1]);
                dst[i  ] = t0;
                dst[i+1] = t1;

                t0 = saturate_cast_uchar_ushort(src1[i+2] * src2[i+2]);
                t1 = saturate_cast_uchar_ushort(src1[i+3] * src2[i+3]);
                dst[i+2] = t0;
                dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_uchar_ushort(src1[i] * src2[i]);
        }
    }
    else
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                uchar t0 = saturate_cast_uchar_float(scale*(float)src1[i]*src2[i]);
                uchar t1 = saturate_cast_uchar_float(scale*(float)src1[i+1]*src2[i+1]);
                dst[i] = t0; dst[i+1] = t1;

                t0 = saturate_cast_uchar_float(scale*(float)src1[i+2]*src2[i+2]);
                t1 = saturate_cast_uchar_float(scale*(float)src1[i+3]*src2[i+3]);
                dst[i+2] = t0; dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_uchar_float(scale*(float)src1[i]*src2[i]);
        }
    }
}

void mul_schar(schar *src1, size_t step1, schar* src2, size_t step2,
      schar* dst, size_t step, int width, int height, float scale )
{
    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);
    step /= sizeof(dst[0]);

    if( scale == (float)1. )
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                schar t0 = saturate_cast_schar_short(src1[i  ] * src2[i  ]);
                schar t1 = saturate_cast_schar_short(src1[i+1] * src2[i+1]);
                dst[i  ] = t0;
                dst[i+1] = t1;

                t0 = saturate_cast_schar_short(src1[i+2] * src2[i+2]);
                t1 = saturate_cast_schar_short(src1[i+3] * src2[i+3]);
                dst[i+2] = t0;
                dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_schar_short(src1[i] * src2[i]);
        }
    }
    else
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                schar t0 = saturate_cast_schar_float(scale*(float)src1[i]*src2[i]);
                schar t1 = saturate_cast_schar_float(scale*(float)src1[i+1]*src2[i+1]);
                dst[i] = t0; dst[i+1] = t1;

                t0 = saturate_cast_schar_float(scale*(float)src1[i+2]*src2[i+2]);
                t1 = saturate_cast_schar_float(scale*(float)src1[i+3]*src2[i+3]);
                dst[i+2] = t0; dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_schar_float(scale*(float)src1[i]*src2[i]);
        }
    }
}

void mul_short(short *src1, size_t step1, short* src2, size_t step2,
      short* dst, size_t step, int width, int height, float scale )
{
    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);
    step /= sizeof(dst[0]);

    if( scale == (float)1. )
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                short t0 = saturate_cast_short_int(src1[i  ] * src2[i  ]);
                short t1 = saturate_cast_short_int(src1[i+1] * src2[i+1]);
                dst[i  ] = t0;
                dst[i+1] = t1;

                t0 = saturate_cast_short_int(src1[i+2] * src2[i+2]);
                t1 = saturate_cast_short_int(src1[i+3] * src2[i+3]);
                dst[i+2] = t0;
                dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_short_int(src1[i] * src2[i]);
        }
    }
    else
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                short t0 = saturate_cast_short_float(scale*(float)src1[i]*src2[i]);
                short t1 = saturate_cast_short_float(scale*(float)src1[i+1]*src2[i+1]);
                dst[i] = t0; dst[i+1] = t1;

                t0 = saturate_cast_short_float(scale*(float)src1[i+2]*src2[i+2]);
                t1 = saturate_cast_short_float(scale*(float)src1[i+3]*src2[i+3]);
                dst[i+2] = t0; dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_short_float(scale*(float)src1[i]*src2[i]);
        }
    }
}

void mul_int32(int *src1, size_t step1, int* src2, size_t step2,
      int* dst, size_t step, int width, int height, float scale )
{
    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);
    step /= sizeof(dst[0]);

    if( scale == (float)1. )
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                int t0 = saturate_cast_int(src1[i  ] * src2[i  ]);
                int t1 = saturate_cast_int(src1[i+1] * src2[i+1]);
                dst[i  ] = t0;
                dst[i+1] = t1;

                t0 = saturate_cast_int(src1[i+2] * src2[i+2]);
                t1 = saturate_cast_int(src1[i+3] * src2[i+3]);
                dst[i+2] = t0;
                dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_int(src1[i] * src2[i]);
        }
    }
    else
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                int t0 = saturate_cast_int_float(scale*(float)src1[i]*src2[i]);
                int t1 = saturate_cast_short_float(scale*(float)src1[i+1]*src2[i+1]);
                dst[i] = t0; dst[i+1] = t1;

                t0 = saturate_cast_int_float(scale*(float)src1[i+2]*src2[i+2]);
                t1 = saturate_cast_int_float(scale*(float)src1[i+3]*src2[i+3]);
                dst[i+2] = t0; dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_int_float(scale*(float)src1[i]*src2[i]);
        }
    }
}

void mul_float(float *src1, size_t step1, float* src2, size_t step2,
      float* dst, size_t step, int width, int height, float scale )
{
    step1 /= sizeof(src1[0]);
    step2 /= sizeof(src2[0]);
    step /= sizeof(dst[0]);

    if( scale == (float)1. )
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                float t0 = saturate_cast_float(src1[i  ] * src2[i  ]);
                float t1 = saturate_cast_float(src1[i+1] * src2[i+1]);
                dst[i  ] = t0;
                dst[i+1] = t1;

                t0 = saturate_cast_float(src1[i+2] * src2[i+2]);
                t1 = saturate_cast_float(src1[i+3] * src2[i+3]);
                dst[i+2] = t0;
                dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_float(src1[i] * src2[i]);
        }
    }
    else
    {
        for( ; height--; src1 += step1, src2 += step2, dst += step )
        {
            int i = 0;
            #if CV_ENABLE_UNROLLED
            for(; i <= width - 4; i += 4 )
            {
                float t0 = saturate_cast_float(scale*(float)src1[i]*src2[i]);
                float t1 = saturate_cast_float(scale*(float)src1[i+1]*src2[i+1]);
                dst[i] = t0; dst[i+1] = t1;

                t0 = saturate_cast_float(scale*(float)src1[i+2]*src2[i+2]);
                t1 = saturate_cast_float(scale*(float)src1[i+3]*src2[i+3]);
                dst[i+2] = t0; dst[i+3] = t1;
            }
            #endif
            for( ; i < width; i++ )
                dst[i] = saturate_cast_float(scale*(float)src1[i]*src2[i]);
        }
    }
}

/*******************************************************************
 *                  different version of div operations            *
 ******************************************************************/

void div_uchar(uchar *src1, size_t step1, uchar *src2, size_t step2, uchar *dst,
               size_t step, int width, int height, double scale) {
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      uchar num = src1[i], denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_uchar_float(num * scale_f / denom) : (uchar)0;
    }
  }
}

void div_schar(schar *src1, size_t step1, schar *src2, size_t step2, schar *dst,
               size_t step, int width, int height, double scale) {
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      schar num = src1[i], denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_schar_float(num * scale_f / denom) : (schar)0;
    }
  }
}

void div_short(short *src1, size_t step1, short *src2, size_t step2, short *dst,
               size_t step, int width, int height, double scale) {
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      short num = src1[i], denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_short_float(num * scale_f / denom) : (short)0;
    }
  }
}

void div_int32(int *src1, size_t step1, int *src2, size_t step2, int *dst,
               size_t step, int width, int height, double scale) {
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      int num = src1[i], denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_int_float(num * scale_f / denom) : (int)0;
    }
  }
}

void div_float(float *src1, size_t step1, short *src2, size_t step2, short *dst,
               size_t step, int width, int height, double scale) {
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      float num = src1[i], denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_float(num * scale_f / denom) : (int)0;
    }
  }
}

/*******************************************************************
 *                different version of recip operations            *
 ******************************************************************/
void recip_uchar(uchar *src2, size_t step2, uchar *dst, size_t step, int width,
             int height, double scale) {
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      uchar denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_uchar_float(scale_f / denom) : (uchar)0;
    }
  }
}

void recip_schar(schar *src2, size_t step2, schar *dst, size_t step, int width,
             int height, double scale) {
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      schar denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_schar_float(scale_f / denom) : (schar)0;
    }
  }
}

void recip_short(short *src2, size_t step2, short *dst, size_t step, int width,
             int height, double scale) {
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      short denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_short_float(scale_f / denom) : (short)0;
    }
  }
}

void recip_int32(int *src2, size_t step2, int *dst, size_t step, int width,
             int height, double scale) {
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      int denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_int_float(scale_f / denom) : (int)0;
    }
  }
}

void recip_float(float *src2, size_t step2, float *dst, size_t step, int width,
             int height, double scale) {
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  float scale_f = (float)scale;

  for (; height--; src2 += step2, dst += step) {
    for (int i = 0; i < width; i++) {
      float denom = src2[i];
      dst[i] = denom != 0 ? saturate_cast_float(scale_f / denom) : (float)0;
    }
  }
}
/*******************************************************************
 *         different version of weighted add operations            *
 ******************************************************************/
void addWeighted_uchar(uchar *src1, size_t step1, uchar *src2, size_t step2, uchar *dst,
             size_t step, int width, int height, void *_scalars) {

	double *scalars = (double *)_scalars;
  float alpha = (float)scalars[0], beta = (float)scalars[1], gamma = (float)scalars[2];
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    int x = 0;
#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      uchar t0 = saturate_cast_uchar_float(src1[x] * alpha + src2[x] * beta + gamma);
      uchar t1 = saturate_cast_uchar_float(src1[x + 1] * alpha + src2[x + 1] * beta + gamma);
      dst[x] = t0;
      dst[x + 1] = t1;

      t0 = saturate_cast_uchar_float(src1[x + 2] * alpha + src2[x + 2] * beta + gamma);
      t1 = saturate_cast_uchar_float(src1[x + 3] * alpha + src2[x + 3] * beta + gamma);
      dst[x + 2] = t0;
      dst[x + 3] = t1;
    }
#endif
    for (; x < width; x++)
      dst[x] = saturate_cast_uchar_float(src1[x] * alpha + src2[x] * beta + gamma);
  }
}

void addWeighted_schar(schar *src1, size_t step1, schar *src2, size_t step2, schar *dst,
             size_t step, int width, int height, void *_scalars) {

	double *scalars = (double *)_scalars;
  float alpha = (float)scalars[0], beta = (float)scalars[1], gamma = (float)scalars[2];
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    int x = 0;
#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      schar t0 = saturate_cast_schar_float(src1[x] * alpha + src2[x] * beta + gamma);
      schar t1 = saturate_cast_schar_float(src1[x + 1] * alpha + src2[x + 1] * beta + gamma);
      dst[x] = t0;
      dst[x + 1] = t1;

      t0 = saturate_cast_schar_float(src1[x + 2] * alpha + src2[x + 2] * beta + gamma);
      t1 = saturate_cast_schar_float(src1[x + 3] * alpha + src2[x + 3] * beta + gamma);
      dst[x + 2] = t0;
      dst[x + 3] = t1;
    }
#endif
    for (; x < width; x++)
      dst[x] = saturate_cast_schar_float(src1[x] * alpha + src2[x] * beta + gamma);
  }
}

void addWeighted_short(short *src1, size_t step1, short *src2, size_t step2, short *dst,
             size_t step, int width, int height, void *_scalars) {

	double *scalars = (double *)_scalars;
  float alpha = (float)scalars[0], beta = (float)scalars[1], gamma = (float)scalars[2];
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    int x = 0;
#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      short t0 = saturate_cast_short_float(src1[x] * alpha + src2[x] * beta + gamma);
      short t1 = saturate_cast_short_float(src1[x + 1] * alpha + src2[x + 1] * beta + gamma);
      dst[x] = t0;
      dst[x + 1] = t1;

      t0 = saturate_cast_short_float(src1[x + 2] * alpha + src2[x + 2] * beta + gamma);
      t1 = saturate_cast_short_float(src1[x + 3] * alpha + src2[x + 3] * beta + gamma);
      dst[x + 2] = t0;
      dst[x + 3] = t1;
    }
#endif
    for (; x < width; x++)
      dst[x] = saturate_cast_short_float(src1[x] * alpha + src2[x] * beta + gamma);
  }
}

void addWeighted_int32(int *src1, size_t step1, int *src2, size_t step2, int *dst,
             size_t step, int width, int height, void *_scalars) {

	double *scalars = (double *)_scalars;
  float alpha = (float)scalars[0], beta = (float)scalars[1], gamma = (float)scalars[2];
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    int x = 0;
#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      int t0 = saturate_cast_int_float(src1[x] * alpha + src2[x] * beta + gamma);
      int t1 = saturate_cast_int_float(src1[x + 1] * alpha + src2[x + 1] * beta + gamma);
      dst[x] = t0;
      dst[x + 1] = t1;

      t0 = saturate_cast_int_float(src1[x + 2] * alpha + src2[x + 2] * beta + gamma);
      t1 = saturate_cast_int_float(src1[x + 3] * alpha + src2[x + 3] * beta + gamma);
      dst[x + 2] = t0;
      dst[x + 3] = t1;
    }
#endif
    for (; x < width; x++)
      dst[x] = saturate_cast_int_float(src1[x] * alpha + src2[x] * beta + gamma);
  }
}

void addWeighted_float(float *src1, size_t step1, float *src2, size_t step2, float *dst,
             size_t step, int width, int height, void *_scalars) {

	double *scalars = (double *)_scalars;
  float alpha = (float)scalars[0], beta = (float)scalars[1], gamma = (float)scalars[2];
  step1 /= sizeof(src1[0]);
  step2 /= sizeof(src2[0]);
  step /= sizeof(dst[0]);

  for (; height--; src1 += step1, src2 += step2, dst += step) {
    int x = 0;
#if CV_ENABLE_UNROLLED
    for (; x <= width - 4; x += 4) {
      float t0 = saturate_cast_float_float(src1[x] * alpha + src2[x] * beta + gamma);
      float t1 = saturate_cast_float_float(src1[x + 1] * alpha + src2[x + 1] * beta + gamma);
      dst[x] = t0;
      dst[x + 1] = t1;

      t0 = saturate_cast_float_float(src1[x + 2] * alpha + src2[x + 2] * beta + gamma);
      t1 = saturate_cast_float_float(src1[x + 3] * alpha + src2[x + 3] * beta + gamma);
      dst[x + 2] = t0;
      dst[x + 3] = t1;
    }
#endif
    for (; x < width; x++)
      dst[x] = saturate_cast_float(src1[x] * alpha + src2[x] * beta + gamma);
  }
}
