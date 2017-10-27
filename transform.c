#include "cdefs.h"

void warpAffine(unsigned char* input, int width, int height, unsigned char* output,
                float matrix[2][3]) {
  float x0, y0;
  float M11 = matrix[0][0];
  float M12 = matrix[0][1];
  float M13 = matrix[0][2];
  float M21 = matrix[1][0];
  float M22 = matrix[1][1];
  float M23 = matrix[1][2];

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {

      x0 = M11 * x + M12 * y + M13;
      y0 = M21 * x + M22 * y + M23;

      if (x0 < 0)
        x0 = 0;
      if (x0 < 0)
        x0 = 0;

      if (x0 >= height)
        x0 = height - 1;
      if (x0 >= width)
        x0 = width - 1;

      output[y * width + x] = input[(int)(y0)*width + (int)(x0)];
    }
  }
}

void warpPerspective(unsigned char* input, int width, int height, unsigned char* output,
                float matrix[3][3]) {
  float M11 = matrix[0][0];
  float M12 = matrix[0][1];
  float M13 = matrix[0][2];
  float M21 = matrix[1][0];
  float M22 = matrix[1][1];
  float M23 = matrix[1][2];
  float M31 = matrix[2][0];
  float M32 = matrix[2][1];
  float M33 = matrix[2][2];

  float x0, y0, z0;

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      x0 = M11 * x + M12 * y + M13;
      y0 = M21 * x + M22 * y + M23;
      z0 = M31 * x + M32 * y + M33;

      int newy = (int)(y0 / z0);
      int newx = (int)(x0 / z0);

      if (newy < 0)
        newy = 0;
      if (newx < 0)
        newx = 0;

      if (newy >= height)
        newy = height - 1;
      if (newx >= width)
        newx = width - 1;

      output[y * width + x] = input[newy * width + newx];
    }
  }
}
