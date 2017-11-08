#include "cdefs.h"

enum ConvertPolicy { WRAP, SATURATE };

#define usat8(a) ((a) > 255 ? 255 : a < 0 ? 0 : a)

#define rgb2yuv_bt709(r, g, b, y, cb, cr)                                      \
  do {                                                                         \
    double f_r = (double)r;                                                    \
    double f_g = (double)g;                                                    \
    double f_b = (double)b;                                                    \
    double f_y = 0 + 0.2126f * f_r + 0.7152f * f_g + 0.0722f * f_b;            \
    double f_u = 0 - 0.1146f * f_r - 0.3854f * f_g + 0.5000f * f_b;            \
    double f_v = 0 + 0.5000f * f_r - 0.4542f * f_g - 0.0458f * f_b;            \
    int i_y = (int)f_y;                                                        \
    int i_u = (int)f_u + 128;                                                  \
    int i_v = (int)f_v + 128;                                                  \
    y = usat8(i_y);                                                            \
    cb = usat8(i_u);                                                           \
    cr = usat8(i_v);                                                           \
  } while (0);

#define yuv2rgb_bt709(y, cb, cr, r, g, b)                                      \
  do {                                                                         \
    double f_y = (double)y;                                                    \
    double f_u = (double)cb - 128;                                             \
    double f_v = (double)cr - 128;                                             \
    double f_r = f_y + 0.0000f * f_u + 1.5748f * f_v;                          \
    double f_g = f_y - 0.1873f * f_u - 0.4681f * f_v;                          \
    double f_b = f_y + 1.8556f * f_u + 0.0000f * f_v;                          \
    int i_r = (int)f_r;                                                        \
    int i_g = (int)f_g;                                                        \
    int i_b = (int)f_b;                                                        \
    r = usat8(i_r);                                                            \
    g = usat8(i_g);                                                            \
    b = usat8(i_b);                                                            \
  } while (0);

void colorConvert(unsigned char *in, int width, int height, int colorFormat_in,
                  int colorFormat_out, unsigned char *out) {
  int total = width * height;

  int x, y;
  unsigned char cb[4];
  unsigned char cr[4];
  if (colorFormat_in == RGB && colorFormat_out == NV12) {
    int qoffset = 0;
    for (y = 0; y < height; y += 2) {
      for (x = 0; x < width; x += 2) {
        int offset = y * width + x;
        // Planar
        // Process 4 RGB Elements into 4 Y,U,V elements
        rgb2yuv_bt709(in[offset], in[offset + total], in[offset + 2 * total],
                      out[offset], cb[0], cr[0]);
        rgb2yuv_bt709(in[offset + 1], in[offset + total + 1],
                      in[offset + 2 * total + 1], out[offset + 1], cb[1],
                      cr[1]);
        rgb2yuv_bt709(in[offset + width], in[offset + total + width],
                      in[offset + 2 * total + width], out[offset + width],
                      cb[2], cr[2]);
        rgb2yuv_bt709(in[offset + width + 1], in[offset + total + width + 1],
                      in[offset + 2 * total + width + 1],
                      out[offset + width + 1], cb[3], cr[3]);

        out[width * height + qoffset] = (cb[0] + cb[1] + cb[2] + cb[3]) / 4;
        out[width * height + qoffset + 1] = (cr[0] + cr[1] + cr[2] + cr[3]) / 4;
        qoffset += 2;
      }
    }
  } else if (colorFormat_in == NV12 && colorFormat_out == RGB) {
    int u_pix = 0;
    int v_pix = 1;

    int qoffset = 0;
    for (y = 0; y < height; y += 2) {
      for (x = 0; x < width; x += 2) {
        int offset = (y * width + x);
          yuv2rgb_bt709(in[offset], in[total + qoffset],
                        in[total + qoffset + 1], out[offset],
                        out[offset + total], out[offset + 2 * total]);
          yuv2rgb_bt709(in[offset + 1], in[total + qoffset],
                        in[total + qoffset + 1], out[offset + 1],
                        out[offset + total + 1], out[offset + 2 * total + 1]);
          yuv2rgb_bt709(in[offset + width], in[total + qoffset],
                        in[total + qoffset + 1], out[offset + width],
                        out[offset + total + width],
                        out[offset + 2 * total + width]);
          yuv2rgb_bt709(in[offset + width + 1], in[total + qoffset],
                        in[total + qoffset + 1], out[offset + width + 1],
                        out[offset + total + width + 1],
                        out[offset + 2 * total + width + 1]);
        qoffset += 2;
      }
    }
  }
}

void convertDepth(unsigned char *in, int width, int height, int depthFormat_in,
  int depthFormat_out, unsigned char *out, int policy, int shift) {
  int total = width * height;

  int x;
  if (depthFormat_in == U8 && depthFormat_out == S16) {
    for (x = 0; x < total; x++)
      ((short *)out)[x] = ((short)(in[x])) << shift;
  } else if (depthFormat_in == S16 && depthFormat_out == U8) {
    if (policy == WRAP) {
      for (x = 0; x < total; x++)
        out[x] = (unsigned char)(((short *)in)[x] >> shift);
    } else if (policy == SATURATE) {
      for (x = 0; x < total; x++) {
        short value = ((short *)in)[x] >> shift;
        value = (value < 0 ? 0 : value);
        value = (value > 255 ? 255 : value);
        out[x] = (unsigned char)value;
      }
    }
  }
}
