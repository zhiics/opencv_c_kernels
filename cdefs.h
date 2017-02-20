/*
 * define the basic types that will be used to the core algorithms.
 */

#ifndef CDEFS_H
#define CDEFS_H

#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#define CV_Error(fmt)                                                          \
  ({                                                                           \
    printf("Error %s:%d: %s\n", __FILE__, __LINE__, fmt);                      \
    exit(1);                                                                   \
  })

#define EPSILON 0.000001
#define false 0
#define true 1

typedef unsigned char uchar;
typedef signed char schar;
typedef unsigned short ushort;
typedef uint32_t uint32;
typedef int32_t int32;
typedef int64_t int64;
typedef uint64_t uint64;
typedef uchar bool;

#ifndef UCHAR_MAX
#define UCHAR_MAX 255
#endif

#ifndef SCHAR_MAX
#define SCHAR_MAX 127
#endif

#ifndef SCHAR_MIN
#define SCHAR_MIN -128
#endif

#ifndef USHRT_MAX
#define USHRT_MAX 65535
#endif

#ifndef SHRT_MAX
#define SHRT_MAX 32767
#endif

#ifndef SHRT_MIN
#define SHRT_MIN -32768
#endif

#define saturate_cast_uchar(v) (v)
#define saturate_cast_schar(v) (v)
#define saturate_cast_ushort(v) (v)
#define saturate_cast_short(v) (v)
#define saturate_cast_unsigned(v) (v)
#define saturate_cast_int(v) (v)
#define saturate_cast_uint64(v) (v)
#define saturate_cast_int64(v) (v)
#define saturate_cast_float(v) (v)
#define saturate_cast_double(v) (v)

#define cvRound_float(v) ({ (int)((v) + ((v) >= 0 ? 0.5f : -0.5f)); })

#define cvRound_double(v) ({ (int)((v) + ((v) >= 0 ? 0.5 : -0.5)); })

#define saturate_cast_uchar_schar(v) ({ (uchar) max((int)(v), 0); })

#define saturate_cast_uchar_ushort(v)                                          \
  ({ (uchar)((unsigned)(v) < (unsigned)UCHAR_MAX ? (v) : UCHAR_MAX); })
//({ (uchar) min((unsigned)(v), (unsigned)UCHAR_MAX); })

#define saturate_cast_uchar_int(v)                                             \
  ({ (uchar)((unsigned)(v) <= UCHAR_MAX ? (v) : (v) > 0 ? UCHAR_MAX : 0); })

#define saturate_cast_uchar_short(v) ({ saturate_cast_uchar_int(v); })

#define saturate_cast_uchar_unsigned(v)                                        \
  ({ (uchar) min((v), (unsigned)UCHAR_MAX); })

#define saturate_cast_uchar_float(v)                                           \
  ({                                                                           \
    int iv = cvRound_float(v);                                                 \
    saturate_cast_uchar_int(iv);                                               \
  })

#define saturate_cast_uchar_double(v)                                          \
  ({                                                                           \
    int iv = cvRound_double(v);                                                \
    saturate_cast_uchar_int(iv);                                               \
  })

#define saturate_cast_uchar_int64(v)                                           \
  ({                                                                           \
    (uchar)((uint64)(v) <= (uint64)UCHAR_MAX ? (v) : (v) > 0 ? UCHAR_MAX : 0); \
  })

#define saturate_cast_uchar_uint64(v) ({ (uchar) min((v), (uint64)UCHAR_MAX); })

#define saturate_cast_schar_uchar(v) ({ (schar) min((int)(v), SCHAR_MAX); })

#define saturate_cast_schar_ushort(v)                                          \
  ({ (schar) min((unsigned)(v), (unsigned)SCHAR_MAX); })

#define saturate_cast_schar_int(v)                                             \
  ({                                                                           \
    (schar)((unsigned)((v)-SCHAR_MIN) <= (unsigned)UCHAR_MAX                   \
                ? (v)                                                          \
                : (v) > 0 ? SCHAR_MAX : SCHAR_MIN);                            \
  })

#define saturate_cast_schar_short(v)                                           \
  ({                                                                           \
    int iv = (int)(v);                                                         \
    saturate_cast_schar_int(iv);                                               \
  })

#define saturate_cast_schar_unsigned(v)                                        \
  ({ (schar) min((v), (unsigned)SCHAR_MAX); })

#define saturate_cast_schar_float(v)                                           \
  ({                                                                           \
    int iv = cvRound_float(v);                                                 \
    saturate_cast_schar_int(iv);                                               \
  })

#define saturate_cast_schar_double(v)                                          \
  ({                                                                           \
    int iv = cvRound_double(v);                                                \
    saturate_cast_schar_int(iv);                                               \
  })

#define saturate_cast_schar_int64(v)                                           \
  ({                                                                           \
    (schar)((uint64)((int64)(v)-SCHAR_MIN) <= (uint64)UCHAR_MAX                \
                ? (v)                                                          \
                : (v) > 0 ? SCHAR_MAX : SCHAR_MIN);                            \
  })

#define saturate_cast_schar_uint64(v) ({ (schar) min((v), (uint64)SCHAR_MAX); })

#define saturate_cast_ushort_schar(v) ({ (ushort) max((int)(v), 0); })

#define saturate_cast_ushort_short(v) ({ (ushort) max((int)(v), 0); })

#define saturate_cast_ushort_int(v)                                            \
  ({                                                                           \
    (ushort)((unsigned)(v) <= (unsigned)USHRT_MAX ? (v)                        \
                                                  : (v) > 0 ? USHRT_MAX : 0);  \
  })

#define saturate_cast_ushort_unsigned(v)                                       \
  ({ (ushort) min((v), (unsigned)USHRT_MAX); })

#define saturate_cast_ushort_float(v)                                          \
  ({                                                                           \
    int iv = cvRound_float(v);                                                 \
    saturate_cast_ushort_int(iv);                                              \
  })

#define saturate_cast_ushort_double(v)                                         \
  ({                                                                           \
    int iv = cvRound_double(v);                                                \
    saturate_cast_ushort_int(iv);                                              \
  })

#define saturate_cast_ushort_int64(v)                                          \
  ({                                                                           \
    (ushort)((uint64)(v) <= (uint64)USHRT_MAX ? (v)                            \
                                              : (v) > 0 ? USHRT_MAX : 0);      \
  })

#define saturate_cast_ushort_uint64(v)                                         \
  ({ (ushort) min((v), (uint64)USHRT_MAX); })

#define saturate_cast_short_schar(v) ({ (short)min((int)(v), SHRT_MAX); })

#define saturate_cast_short_int(v)                                             \
  ({                                                                           \
    (short)((unsigned)((v)-SHRT_MIN) <= (unsigned)USHRT_MAX                    \
                ? (v)                                                          \
                : (v) > 0 ? SHRT_MAX : SHRT_MIN);                              \
  })

#define saturate_cast_short_unsigned(v)                                        \
  ({ (short)min((v), (unsigned)SHRT_MAX); })

#define saturate_cast_short_float(v)                                           \
  ({                                                                           \
    int iv = cvRound_float(v);                                                 \
    saturate_cast_short_int(iv);                                               \
  })

#define saturate_cast_short_double(v)                                          \
  ({                                                                           \
    int iv = cvRound_double(v);                                                \
    saturate_cast_short_int(iv);                                               \
  })

#define saturate_cast_short_int64(v)                                           \
  ({                                                                           \
    (short)((uint64)((int64)(v)-SHRT_MIN) <= (uint64)USHRT_MAX                 \
                ? (v)                                                          \
                : (v) > 0 ? SHRT_MAX : SHRT_MIN);                              \
  })

#define saturate_cast_short_uint64(v)                                          \
  ({ return (short)min((v), (uint64)SHRT_MAX); })

#define saturate_cast_int_float(v) ({ cvRound_float(v); })

#define saturate_cast_int_double(v) ({ cvRound_double(v); })

#define saturate_cast_unsigned_float(v) ({ cvRound_float(v); })

#define saturate_cast_unsigned_double(v) ({ cvRound_double(v); })

#define swap(x, y, T)                                                          \
  do {                                                                         \
    T swap = x;                                                                \
    x = y;                                                                     \
    y = swap;                                                                  \
  } while (0);

enum CmpTypes {
  CMP_EQ = 0, //!< src1 is equal to src2.
  CMP_GT = 1, //!< src1 is greater than src2.
  CMP_GE = 2, //!< src1 is greater than or equal to src2.
  CMP_LT = 3, //!< src1 is less than src2.
  CMP_LE = 4, //!< src1 is less than or equal to src2.
  CMP_NE = 5  //!< src1 is unequal to src2.
};

enum ThresholdTypes {
  THRESH_BINARY = 0,     //!< \f[\texttt{dst} (x,y) =  \fork{\texttt{maxval}}{if
                         //!\(\texttt{src}(x,y) >
                         //!\texttt{thresh}\)}{0}{otherwise}\f]
  THRESH_BINARY_INV = 1, //!< \f[\texttt{dst} (x,y) =  \fork{0}{if
                         //!\(\texttt{src}(x,y) >
                         //!\texttt{thresh}\)}{\texttt{maxval}}{otherwise}\f]
  THRESH_TRUNC = 2,  //!< \f[\texttt{dst} (x,y) =  \fork{\texttt{threshold}}{if
                     //!\(\texttt{src}(x,y) >
                     //!\texttt{thresh}\)}{\texttt{src}(x,y)}{otherwise}\f]
  THRESH_TOZERO = 3, //!< \f[\texttt{dst} (x,y) =  \fork{\texttt{src}(x,y)}{if
                     //!\(\texttt{src}(x,y) >
                     //!\texttt{thresh}\)}{0}{otherwise}\f]
  THRESH_TOZERO_INV = 4, //!< \f[\texttt{dst} (x,y) =  \fork{0}{if
                         //!\(\texttt{src}(x,y) >
                         //!\texttt{thresh}\)}{\texttt{src}(x,y)}{otherwise}\f]
  THRESH_MASK = 7,
  THRESH_OTSU =
      8, //!< flag, use Otsu algorithm to choose the optimal threshold value
  THRESH_TRIANGLE =
      16 //!< flag, use Triangle algorithm to choose the optimal threshold value
};

#endif
