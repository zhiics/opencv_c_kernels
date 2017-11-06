/*
 * Utility functions and data types.
 */

#ifndef UTIL_H
#define UTIL_H

#include <malloc.h>

#include <time.h>

#ifdef __APPLE__
#define HAVE_MACH_TIMER
#include <mach/clock.h>
#include <mach/mach.h>
#include <sys/time.h>
#endif

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

#define MAKE_ASSERT_EQ(T)\
  int assert_eq_##T(T* arr1, T* arr2, size_t len){\
    int i;\
    int ret=0;\
    for(i = 0; i < len; i = i+1) { \
      if (arr1[i] != arr2[i]) {\
        printf("Mismatch at index %d. Got %d, expected %d\n", i, (int)arr1[i], (int)arr2[i]); \
        ret=-1;\
      }\
    }\
    return ret;\
  }

// Generate Assertion Functinos
MAKE_ASSERT_EQ(uchar)
MAKE_ASSERT_EQ(schar)
MAKE_ASSERT_EQ(short)
MAKE_ASSERT_EQ(int32)

// Specialize floating point
int assert_eq_float(float* arr1, float* arr2, size_t len){
  int i;
  int ret=0;
  for(i = 0; i < len; i = i+1) {
    if ((arr1[i]-arr2[i]) > EPSILON || (arr2[i]-arr1[i]) > EPSILON) {
      printf("Mismatch at index %d. Got %f, expected %f\n", i, arr1[i], arr2[i]);
      ret=-1;
    }
  }
  return ret;
}



struct TestImage {
  uchar * data;
  int width;
  int height;
  int elemSize;
};

void allocateImage(int width, int height, int elemSize, struct TestImage* ts) {
	mallopt(M_MMAP_MAX, 0);
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

	mallopt(M_MMAP_MAX, 0);
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

#define MAKE_RANDOM_DATA(T) \
  void get_random_array_##T(struct TestImage* ts, int width, int height, int32 max) {\
		mallopt(M_MMAP_MAX, 0);\
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

#endif
