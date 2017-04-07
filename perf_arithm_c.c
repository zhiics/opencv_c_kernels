#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include "cdefs.h"
#include <stdlib.h>


#include <time.h>

#ifdef __APPLE__
#define HAVE_MACH_TIMER
#include <mach/clock.h>
#include <mach/mach.h>
#include <sys/time.h>
#endif

#include "arithm_core_c.c"
#include "morph.c"
#include "integral.c"


struct TestImage {
  uchar * data;
  int width;
  int height;
  int elemSize;
};

struct timespec ts;

void getTime(struct timespec* ts) {
  #ifdef __APPLE__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
  #else
  clock_gettime(CLOCK_REALTIME, ts);
  #endif
}


#define MAKE_PERF_ADDSUB(T, F) \
  void perf_##F##_##T(T* src1, T *src2, \
                    T *dst, size_t step, int width, int height) { \
                    struct timespec t1, t2;\
                    getTime(&t1);\
                    F##_##T(src1, step, src2, step, dst, step, width, height); \
                    getTime(&t2);\
                    printf("Test %s for type %s took %lu nanoseconds.\n", #F, #T, t2.tv_nsec - t1.tv_nsec); \
                    return;\
                }

#define MAKE_PERF_MULDIV(T, F) \
  void perf_##F##_##T(T* src1, T *src2, \
                    T *dst, size_t step, int width, int height, float scale) { \
                    struct timespec t1, t2;\
                    getTime(&t1);\
                    F##_##T(src1, step, src2, step, dst, step, width, height, scale); \
                    getTime(&t2);\
                    printf("Test %s for type %s took %lu nanoseconds.\n", #F, #T, t2.tv_nsec - t1.tv_nsec); \
                    return;\
                }

#define MAKE_PERF_RECIP(T) \
  void perf_recip_##T(T* src1, \
                    T *dst, size_t step, int width, int height, float scale) { \
                    struct timespec t1, t2;\
                    getTime(&t1);\
                    recip_##T(src1, step, dst, step, width, height, scale); \
                    getTime(&t2);\
                    printf("Testing recip for type %s took %lu nanoseconds.\n", #T, t2.tv_nsec - t1.tv_nsec); \
                    return;\
                }
#define MAKE_PERF_ADD_WEIGHTED(T) \
  void perf_addWeighted_##T(T* src1, T *src2, \
                    T *dst, size_t step, int width, int height, void *scalars) { \
                    struct timespec t1, t2;\
                    getTime(&t1);\
                    addWeighted_##T(src1, step, src2, step, dst, step, width, height, scalars); \
                    getTime(&t2);\
                    printf("Testing addWeighted for type %s took %lu nanoseconds.\n", #T, t2.tv_nsec - t1.tv_nsec); \
                    return;\
                }

#define MAKE_PERF_INTEGRAL(T1, T2, T3) \
  void perf_integral_##T1##_##T2##_##T3(T1* src1,size_t _srcstep, T2* sum, size_t _sumstep, \
                  T3* sqsum, size_t s_sqsumstep, T2* tilted, size_t s_tiltedstep,\
                  int width, int height, int cn) { \
                    struct timespec t1, t2;\
                    getTime(&t1);\
                    integral_##T1##_##T2##_##T3(src1,_srcstep, sum, _sumstep, \
                                    sqsum, s_sqsumstep,  tilted, s_tiltedstep,\
                                     width,  height,  cn); \
                    getTime(&t2);\
                    printf("Testing Integral for type %s,%s,%s took %lu nanoseconds.\n", #T1, #T2, #T3, t2.tv_nsec - t1.tv_nsec); \
                    return;\
                }

#define MAKE_PERF_MORPH(T) \
  void perf_morphrowfilter_min_##T(T* src, T* dst, int width, int cn, int ksize) { \
                    struct timespec t1, t2;\
                    getTime(&t1);\
                    morphrowfilter_min_##T(src, dst, width, cn, ksize); \
                    getTime(&t2);\
                    printf("Testing morph.min for type %s took %lu nanoseconds.\n", #T, t2.tv_nsec - t1.tv_nsec); \
                    return;\
                }\
void perf_morphrowfilter_max_##T(T* src,T* dst, int width, int cn, int ksize) { \
                    struct timespec t1, t2;\
                    getTime(&t1);\
                    morphrowfilter_max_##T(src, dst, width, cn, ksize); \
                    getTime(&t2);\
                    printf("Testing morph.max for type %s took %lu nanoseconds.\n", #T, t2.tv_nsec - t1.tv_nsec); \
                    return;\
                }

// Generate Test Functinos
MAKE_PERF_ADDSUB(uchar, add)
MAKE_PERF_ADDSUB(uchar, sub)
MAKE_PERF_MULDIV(uchar, mul)
MAKE_PERF_MULDIV(uchar, div)
MAKE_PERF_RECIP(uchar)
MAKE_PERF_ADD_WEIGHTED(uchar)

MAKE_PERF_ADDSUB(schar, add)
MAKE_PERF_ADDSUB(schar, sub)
MAKE_PERF_MULDIV(schar, mul)
MAKE_PERF_MULDIV(schar, div)
MAKE_PERF_RECIP(schar)
MAKE_PERF_ADD_WEIGHTED(schar)

MAKE_PERF_ADDSUB(short, add)
MAKE_PERF_ADDSUB(short, sub)
MAKE_PERF_MULDIV(short, mul)
MAKE_PERF_MULDIV(short, div)
MAKE_PERF_RECIP(short)
MAKE_PERF_ADD_WEIGHTED(short)

MAKE_PERF_ADDSUB(int32, add)
MAKE_PERF_ADDSUB(int32, sub)
MAKE_PERF_MULDIV(int32, mul)
MAKE_PERF_MULDIV(int32, div)
MAKE_PERF_RECIP(int32)
MAKE_PERF_ADD_WEIGHTED(int32)

MAKE_PERF_ADDSUB(float, add)
MAKE_PERF_ADDSUB(float, sub)
MAKE_PERF_MULDIV(float, mul)
MAKE_PERF_MULDIV(float, div)
MAKE_PERF_RECIP(float)
MAKE_PERF_ADD_WEIGHTED(float)


MAKE_PERF_INTEGRAL(uchar, int32, float)
MAKE_PERF_INTEGRAL(uchar, int32, double)


MAKE_PERF_MORPH(uchar)

#define MAKE_RANDOM_DATA(T) \
  void get_random_array_##T(struct TestImage* ts, int width, int height, int32 max) {\
    T* data = (T*)malloc(sizeof(T)*width*height);\
    for (int y = 0; y<height*width; y++)\
        data[y] = (T)(rand() % max);\
    ts->data = data;\
    ts->width = width;\
    ts->height = height;\
    ts->elemSize = sizeof(T);\
    return;\
  }

MAKE_RANDOM_DATA(uchar)
MAKE_RANDOM_DATA(short)
MAKE_RANDOM_DATA(int32)
MAKE_RANDOM_DATA(float)

void allocateImage(int width, int height, int elemSize, struct TestImage* ts) {
  ts->width = width;
  ts->height = height;
  ts->elemSize = elemSize;
  ts->data = (uchar*) malloc(width*height*elemSize);
}

void deallocateImage(struct TestImage * ts) {
  free(ts->data);
}

void loadPGMImage(char * path, struct TestImage* ts) {
  //pgm file contains width, height value itself.
  int width, height;

  FILE* in = fopen(path, "rb");
  // Declare pointer of char* as amount of width*height.
  uchar* bytes;
	//Read width and height
	fscanf(in, "%*[^\n]\n%d %d\n%*[^\n]\n", &width, &height);

	bytes = (uchar*)malloc(width*height);

	//Fill bytes with pixel values
	for (int y = 0; y<height; y++)
		for (int x = 0; x<width; x++)
			fscanf(in, "%c", &bytes[(y*width) + x]);

  ts->data = bytes;
  ts->width = width;
  ts->height = height;
  ts->elemSize = 1;
  return;
}


void savePGMImage(char * path, struct TestImage* ts) {
  //pgm file contains width, height value itself.
  int width, height;

  FILE* out = fopen(path, "wb");
  // Declare pointer of char* as amount of width*height.
  uchar* bytes;
  //Read width and heightl
  fprintf(out, "P5\n%d %d\n255\n", ts->width, ts->height);
  //Fill bytes with pixel values
  for (int y = 0; y<ts->height; y++)
    for (int x = 0; x<ts->width; x++)
      fprintf(out, "%c", ts->data[(y*ts->width) + x]);

  return;
}

int main() {

  size_t step = 1;
  int ksize = 5;
  // Uchar (UHD) tests
  struct TestImage input_img1, input_img2, dst_img;
  struct TestImage sum_img, sqsum_img, tilted_img;
  loadPGMImage("./raw/256x256/clock.pgm", &input_img1);
  loadPGMImage("./raw/256x256/clock.pgm", &input_img2);
  allocateImage(input_img1.width, input_img1.height, 1, &dst_img);
  step = 1 * dst_img.width;

  perf_morphrowfilter_min_uchar(input_img1.data, dst_img.data, dst_img.width*dst_img.height, 1, ksize);
  perf_morphrowfilter_max_uchar(input_img1.data, dst_img.data, dst_img.width*dst_img.height, 1, ksize);

  perf_add_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.height * dst_img.width, 1);
  //savePGMImage("./raw/scarf_out.pgm", &dst_img);
  perf_sub_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1);
  perf_mul_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 1.0);
  perf_mul_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 2.0);
  perf_div_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 2.5);
  perf_recip_uchar(input_img1.data, dst_img.data, step, dst_img.width*dst_img.height,1, 2.0);
  deallocateImage(&dst_img);


  allocateImage(input_img1.width+1, input_img1.height+1, 4, &sum_img);
  allocateImage(input_img1.width+1, input_img1.height+1, 4, &tilted_img);
  allocateImage(input_img1.width+1, input_img1.height+1, 4, &sqsum_img);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, 0, 0, 0,0 , input_img1.width, input_img1.height, 1);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, sqsum_img.data, sqsum_img.width*4, 0,0 , input_img1.width, input_img1.height, 1);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, sqsum_img.data, sqsum_img.width*4, tilted_img.data, tilted_img.width , input_img1.width, input_img1.height, 1);
  deallocateImage(&sum_img);
  deallocateImage(&tilted_img);
  deallocateImage(&sqsum_img);  



  loadPGMImage("./raw/512x512/mandrill.pgm", &input_img1);
  loadPGMImage("./raw/512x512/mandrill.pgm", &input_img2);
  loadPGMImage("./raw/512x512/mandrill.pgm", &dst_img);
  step = 1 * dst_img.width;
  perf_morphrowfilter_min_uchar(input_img1.data, dst_img.data, dst_img.width*dst_img.height, 1, ksize);
  perf_morphrowfilter_max_uchar(input_img1.data, dst_img.data, dst_img.width*dst_img.height, 1, ksize);
  perf_add_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.height * dst_img.width, 1);
  perf_sub_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1);
  perf_mul_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 1.0);
  perf_mul_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 2.0);
  perf_div_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 2.5);
  perf_recip_uchar(input_img1.data, dst_img.data, step, dst_img.width*dst_img.height,1, 2.0);
  deallocateImage(&dst_img);


  allocateImage(input_img1.width+1, input_img1.height+1, 4, &sum_img);
  allocateImage(input_img1.width+1, input_img1.height+1, 4, &tilted_img);
  allocateImage(input_img1.width+1, input_img1.height+1, 4, &sqsum_img);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, 0, 0, 0,0 , input_img1.width, input_img1.height, 1);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, sqsum_img.data, sqsum_img.width*4, 0,0 , input_img1.width, input_img1.height, 1);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, sqsum_img.data, sqsum_img.width*4, tilted_img.data, tilted_img.width , input_img1.width, input_img1.height, 1);
  deallocateImage(&sum_img);
  deallocateImage(&tilted_img);
  deallocateImage(&sqsum_img);  






  loadPGMImage("./raw/1024x1024/pirate.pgm", &input_img1);
  loadPGMImage("./raw/1024x1024/pirate.pgm", &input_img2);
  loadPGMImage("./raw/1024x1024/pirate.pgm", &dst_img);
  step = 1 * dst_img.width;
  perf_morphrowfilter_min_uchar(input_img1.data, dst_img.data, dst_img.width*dst_img.height, 1, ksize);
  perf_morphrowfilter_max_uchar(input_img1.data, dst_img.data, dst_img.width*dst_img.height, 1, ksize);
 
  perf_add_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.height * dst_img.width, 1);
  perf_sub_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1);
  perf_mul_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 1.0);
  perf_mul_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 2.0);
  perf_div_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 2.5);
  perf_recip_uchar(input_img1.data, dst_img.data, step, dst_img.width*dst_img.height,1, 2.0);
  deallocateImage(&dst_img);


  allocateImage(input_img1.width+1, input_img1.height+1, 4, &sum_img);
  allocateImage(input_img1.width+1, input_img1.height+1, 4, &tilted_img);
  allocateImage(input_img1.width+1, input_img1.height+1, 4, &sqsum_img);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, 0, 0, 0,0 , input_img1.width, input_img1.height, 1);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, sqsum_img.data, sqsum_img.width*4, 0,0 , input_img1.width, input_img1.height, 1);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, sqsum_img.data, sqsum_img.width*4, tilted_img.data, tilted_img.width , input_img1.width, input_img1.height, 1);
  deallocateImage(&sum_img);
  deallocateImage(&tilted_img);
  deallocateImage(&sqsum_img);  



  loadPGMImage("./raw/uhd/scarf.pgm", &input_img1);
  loadPGMImage("./raw/uhd/scarf.pgm", &input_img2);
  loadPGMImage("./raw/uhd/scarf.pgm", &dst_img);
  step = 1 * dst_img.width;
  perf_morphrowfilter_min_uchar(input_img1.data, dst_img.data, dst_img.width*dst_img.height, 1, ksize);
  perf_morphrowfilter_max_uchar(input_img1.data, dst_img.data, dst_img.width*dst_img.height, 1, ksize);
  perf_add_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.height * dst_img.width, 1);
  perf_sub_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1);
  perf_mul_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 1.0);
  perf_mul_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 2.0);
  perf_div_uchar(input_img1.data, input_img2.data, dst_img.data, step, dst_img.width*dst_img.height, 1, 2.5);
  perf_recip_uchar(input_img1.data, dst_img.data, step, dst_img.width*dst_img.height,1, 2.0);
  deallocateImage(&dst_img);


  allocateImage(input_img1.width+1, input_img1.height+1, 4, &sum_img);
  allocateImage(input_img1.width+1, input_img1.height+1, 4, &tilted_img);
  allocateImage(input_img1.width+1, input_img1.height+1, 4, &sqsum_img);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, 0, 0, 0,0 , input_img1.width, input_img1.height, 1);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, sqsum_img.data, sqsum_img.width*4, 0,0 , input_img1.width, input_img1.height, 1);
  perf_integral_uchar_int32_float(input_img1.data, input_img1.width*1, sum_img.data, sum_img.width*4, sqsum_img.data, sqsum_img.width*4, tilted_img.data, tilted_img.width , input_img1.width, input_img1.height, 1);
  deallocateImage(&sum_img);
  deallocateImage(&tilted_img);
  deallocateImage(&sqsum_img);  




  //
  // // short tests
  // struct TestImage short_img1, short_img2, short_dst_img;
  // get_random_array_short(&short_img1, 1000, 2000, (2<<15)-1);
  // get_random_array_short(&short_img2, 1000, 2000, (2<<15)-1);
  // get_random_array_short(&short_dst_img, 1000, 2000, (2<<15)-1);
  // perf_add_short(short_img1.data, short_img2.data, short_dst_img.data, step, short_dst_img.width, short_dst_img.height);
  // perf_sub_short(short_img1.data, short_img2.data, short_dst_img.data, step, short_dst_img.width, short_dst_img.height);
  // perf_mul_short(short_img1.data, short_img2.data, short_dst_img.data, step, short_dst_img.width, short_dst_img.height, 1.0);
  // perf_mul_short(short_img1.data, short_img2.data, short_dst_img.data, step, short_dst_img.width, short_dst_img.height, 2.0);
  // perf_div_short(short_img1.data, short_img2.data, short_dst_img.data, step, short_dst_img.width, short_dst_img.height, 2.5);
  // perf_recip_short(short_img1.data, short_dst_img.data, step, short_dst_img.width, short_dst_img.height, 2.0);
  //
  // // Int32 tests
  // struct TestImage int32_img1, int32_img2, int32_dst_img;
  // get_random_array_int32(&int32_img1, 1000, 2000, (2<<31)-1);
  // get_random_array_int32(&int32_img2, 1000, 2000, (2<<31)-1);
  // get_random_array_int32(&int32_dst_img, 1000, 2000, (2<<31)-1);
  // perf_add_int32(int32_img1.data, int32_img2.data, int32_dst_img.data, step, int32_dst_img.width, int32_dst_img.height);
  // perf_sub_int32(int32_img1.data, int32_img2.data, int32_dst_img.data, step, int32_dst_img.width, int32_dst_img.height);
  // perf_mul_int32(int32_img1.data, int32_img2.data, int32_dst_img.data, step, int32_dst_img.width, int32_dst_img.height, 1.0);
  // perf_mul_int32(int32_img1.data, int32_img2.data, int32_dst_img.data, step, int32_dst_img.width, int32_dst_img.height, 2.0);
  // perf_div_int32(int32_img1.data, int32_img2.data, int32_dst_img.data, step, int32_dst_img.width, int32_dst_img.height, 2.5);
  // perf_recip_int32(int32_img1.data, int32_dst_img.data, step, int32_dst_img.width, int32_dst_img.height, 2.0);
  //
  // // Float tests
  // struct TestImage float_img1, float_img2, float_dst_img;
  // get_random_array_float(&float_img1, 1000, 2000, (2<<31)-1);
  // get_random_array_float(&float_img2, 1000, 2000, (2<<31)-1);
  // get_random_array_float(&float_dst_img, 1000, 2000, (2<<31)-1);
  // perf_add_float(float_img1.data, float_img2.data, float_dst_img.data, step, float_dst_img.width, float_dst_img.height);
  // perf_sub_float(float_img1.data, float_img2.data, float_dst_img.data, step, float_dst_img.width, float_dst_img.height);
  // perf_mul_float(float_img1.data, float_img2.data, float_dst_img.data, step, float_dst_img.width, float_dst_img.height, 1.0);
  // perf_mul_float(float_img1.data, float_img2.data, float_dst_img.data, step, float_dst_img.width, float_dst_img.height, 2.0);
  // perf_div_float(float_img1.data, float_img2.data, float_dst_img.data, step, float_dst_img.width, float_dst_img.height, 2.5);
  // perf_recip_float(float_img1.data, float_dst_img.data, step, float_dst_img.width, float_dst_img.height, 2.0);

  return 0;
}
