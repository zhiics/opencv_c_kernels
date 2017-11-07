void box3x3(unsigned char *input, int width, int height, unsigned char *output) {
  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      unsigned short accum = 0;

      int count = 0;
      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          accum += input[(y + j) * width + x + i];
        }
      }

      output[y * width + x] = (unsigned char)(accum / 9);
    }
  }
}

void erode(unsigned char *input, int width, int height, unsigned char *output) {
  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      unsigned char min_pixel = 255;
      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          unsigned char data = input[(y + j) * width + x + i];
          min_pixel = data < min_pixel ? data : min_pixel;
        }
      }
      output[y * width + x] = min_pixel;
    }
  }
}

void sobel(unsigned char *input, int width, int height,
           unsigned short *output_x, unsigned short *output_y) {

  short weightX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  short weightY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      short pixel_value_x = 0;
      short pixel_value_y = 0;

      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          unsigned char data = input[(y + j) * width + x + i];

          pixel_value_x += weightX[j + 1][i + 1] * data;
          pixel_value_y += weightY[j + 1][i + 1] * data;
        }
      }

      output_x[y * width + x] = pixel_value_x;
      output_y[y * width + x] = pixel_value_x;
    }
  }
}

void dilate(unsigned char *input, int width, int height, unsigned char *output) {
  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      unsigned char max_pixel = 0;

      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          unsigned char data = input[(y + j) * width + x + i];
          max_pixel = data > max_pixel ? data : max_pixel;
        }
      }
      output[y * width + x] = max_pixel;
    }
  }
}

void gaussian3x3(unsigned char *input, int width, int height, unsigned char *output) {

  short weight[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      short pixel_value = 0;

      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          unsigned char data = input[(y + j) * width + x + i];
          pixel_value += weight[j + 1][i + 1] * data;
        }
      }

      output[y * width + x] = (unsigned char)(pixel_value >> 4);
    }
  }
}

void gaussian5x5(unsigned char *input, int width, int height, unsigned char *output) {
  short weight[5][5] = {{1, 2, 4, 2, 1},
                        {2, 4, 8, 4, 2},
                        {4, 8, 16, 8, 2},
                        {2, 4, 8, 4, 2},
                        {1, 2, 4, 2, 1}};

  for (int y = 2; y < height - 2; y++) {
    for (int x = 2; x < width - 2; x++) {
      short pixel_value = 0;

      for (int j = -2; j <= 2; j++) {
        for (int i = -2; i <= 2; i++) {
          unsigned char data = input[(y + j) * width + x + i];
          pixel_value += weight[j + 2][i + 2] * data;
        }
      }

      output[y * width + x] = (unsigned char)(pixel_value >> 6);
    }
  }
}

void median3x3(unsigned char *input, int width, int height, unsigned char *output) {
  unsigned char data[10] = {0};

  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      unsigned char max_pixel = 255, swap;

      int count = 0;
      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          data[++count] = input[(y + j) * width + x + i];
        }
      }

			if (data[1] > data[6]) { swap = data[1]; data[1] = data[6]; data[6] = swap; }
      if (data[2] > data[7]) { swap = data[2]; data[2] = data[7]; data[7] = swap; }
      if (data[3] > data[8]) { swap = data[3]; data[3] = data[8]; data[8] = swap; }
      if (data[4] > data[9]) { swap = data[4]; data[4] = data[9]; data[9] = swap; }
      if (data[5] > data[8]) { swap = data[5]; data[5] = data[8]; data[8] = swap; }
      if (data[1] > data[4]) { swap = data[1]; data[1] = data[4]; data[4] = swap; }
      if (data[6] > data[9]) { swap = data[6]; data[6] = data[9]; data[9] = swap; }
      if (data[3] > data[6]) { swap = data[3]; data[3] = data[6]; data[6] = swap; }
      if (data[7] > data[9]) { swap = data[7]; data[7] = data[9]; data[9] = swap; }
      if (data[2] > data[4]) { swap = data[2]; data[2] = data[4]; data[4] = swap; }
      if (data[5] > data[7]) { swap = data[5]; data[5] = data[7]; data[7] = swap; }
      if (data[8] > data[9]) { swap = data[8]; data[8] = data[9]; data[9] = swap; }
      if (data[1] > data[2]) { swap = data[1]; data[1] = data[2]; data[2] = swap; }
      if (data[3] > data[5]) { swap = data[3]; data[3] = data[5]; data[5] = swap; }
      if (data[4] > data[6]) { swap = data[4]; data[4] = data[6]; data[6] = swap; }
      if (data[7] > data[8]) { swap = data[7]; data[7] = data[8]; data[8] = swap; }
      if (data[1] > data[3]) { swap = data[1]; data[1] = data[3]; data[3] = swap; }
      if (data[4] > data[7]) { swap = data[4]; data[4] = data[7]; data[7] = swap; }
      if (data[2] > data[5]) { swap = data[2]; data[2] = data[5]; data[5] = swap; }
      if (data[6] > data[8]) { swap = data[6]; data[6] = data[8]; data[8] = swap; }
      if (data[2] > data[3]) { swap = data[2]; data[2] = data[3]; data[3] = swap; }
      if (data[4] > data[5]) { swap = data[4]; data[4] = data[5]; data[5] = swap; }
      if (data[6] > data[7]) { swap = data[6]; data[6] = data[7]; data[7] = swap; }
      if (data[3] > data[4]) { swap = data[3]; data[3] = data[4]; data[4] = swap; }
      if (data[5] > data[6]) { swap = data[5]; data[5] = data[6]; data[6] = swap; }

      output[y * width + x] = data[5];
    }
  }
}

void nonmaxSuppress3x3(unsigned char *input, int width, int height,
                       unsigned char *mask, unsigned char *output) {
  unsigned char buffer[10] = {0};

  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {

      int index = (y)*width + x;
      unsigned char current_val = input[index];

      if (mask[index]) {
        output[index] = input[index];
      } else {
        if (current_val > input[index - 1] && current_val > input[index + 1] &&
            current_val > input[index - width] &&
            current_val > input[index - width - 1] &&
            current_val > input[index - width + 1] &&
            current_val > input[index + width] &&
            current_val > input[index + width + 1] &&
            current_val > input[index + width - 1]) {
          output[index] = input[index];
        } else {
          output[index] = 255;
        }
      }
    }
  }
}

void censusTransform(unsigned char *input, int width, int height,
                     unsigned char *output) {
  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      int index = y * width + x;

      unsigned char center_val = input[index];
      unsigned char current_val = 0;

      if (center_val <= input[index - width - 1])
        current_val |= 1;
      current_val <<= 1;

      if (center_val <= input[index - width])
        current_val |= 1;
      current_val <<= 1;

      if (center_val <= input[index - width + 1])
        current_val |= 1;
      current_val <<= 1;

      if (center_val <= input[index - 1])
        current_val |= 1;
      current_val <<= 1;

      if (center_val <= input[index + 1])
        current_val |= 1;
      current_val <<= 1;

      if (center_val <= input[index + width - 1])
        current_val |= 1;
      current_val <<= 1;

      if (center_val <= input[index + width])
        current_val |= 1;
      current_val <<= 1;

      if (center_val <= input[index + width + 1])
        current_val |= 1;

      output[index] = current_val;
    }
  }
}
