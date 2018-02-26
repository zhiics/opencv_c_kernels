// rewrite
// https://github.com/opencv/opencv_contrib/blob/e53977f64bcaa766b4e053a21213cc45ef5d61b1/modules/xfeatures2d/src/sift.cpp
//
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "cdefs.h"

#define max(a, b) ((a > b) ? a : b)
#define min(a, b)((a < b) ? a : b)
#define at(x, y, n) ((x) * (n) + (y))

// default width of descriptor histogram array
#define SIFT_DESCR_WIDTH 4

// default number of bins per histogram in descriptor array
#define SIFT_DESCR_HIST_BINS 8

// assumed gaussian blur for input image
#define SIFT_INIT_SIGMA 0.5

// width of border in which to ignore keypoints
#define SIFT_IMG_BORDER 5

// maximum steps of keypoint interpolation before failure
#define SIFT_MAX_INTERP_STEPS 5

// default number of bins in histogram for orientation assignment
#define SIFT_ORI_HIST_BINS 36

// determines gaussian sigma for orientation assignment
#define SIFT_ORI_SIG_FCTR 1.5

// determines the radius of the region used in orientation assignment
#define SIFT_ORI_RADIUS (3 * SIFT_ORI_SIG_FCTR)

// orientation magnitude relative to max that results in new feature
#define SIFT_ORI_PEAK_RATIO 0.8

// determines the size of a single descriptor orientation histogram
#define SIFT_DESCR_SCL_FCTR 3

// threshold on magnitude of elements of descriptor vector
#define SIFT_DESCR_MAG_THR 0.2

// factor used to convert floating-point descriptor to unsigned char
#define SIFT_INT_DESCR_FCTR 512

#define DoG_TYPE_SHORT 0
#if DoG_TYPE_SHORT
// intermediate type used for DoG pyramids
typedef short sift_wt;
#define SIFT_FIXPT_SCALE 48
#else
// intermediate type used for DoG pyramids
typedef float sift_wt;
#define SIFT_FIXPT_SCALE 1
#endif

float calcOrientationHist(unsigned char *img, int width, int height, int py,
                          int px, int radius, float sigma, float *hist, int n) {
  int i, j, k, len = (radius * 2 + 1) * (radius * 2 + 1);

  float expf_scale = -1.f / (2.f * sigma * sigma);
  float *buf = (float *)malloc((len * 4 + n + 4) * sizeof(float));
  float *X = buf, *Y = X + len, *Mag = X, *Ori = Y + len, *W = Ori + len;
  float *temphist = W + len + 2;

  for (i = 0; i < n; i++)
    temphist[i] = 0.f;

  for (i = -radius, k = 0; i <= radius; i++) {
    int y = py + i;
    if (y <= 0 || y >= height - 1)
      continue;
    for (j = -radius; j <= radius; j++) {
      int x = px + j;
      if (x <= 0 || x >= width - 1)
        continue;

      // float dx = (float)(img.at<sift_wt>(y, x + 1) - img.at<sift_wt>(y, x -
      // 1));
      float dx = (float)((y * width + (x + 1)) - (y * width + (x - 1)));
      // float dy = (float)(img.at<sift_wt>(y - 1, x) - img.at<sift_wt>(y + 1,
      // x));
      float dy = (float)(((y - 1) * width + x) - ((y + 1) * width + x));

      X[k] = dx;
      Y[k] = dy;
      W[k] = (i * i + j * j) * expf_scale;
      k++;
    }
  }

  len = k;

  // cv::hal::exp32f(W, W, len);
  int t = 0;
  while (t < len)
    W[t] = exp(W[t++]);
  // cv::hal::fastAtan2(Y, X, Ori, len, true);
  t = 0;
  while (t < len) {
    Ori[t] = atan2(Y[t], X[t]);
    t++;
  }

  k = 0;
  for (; k < len; k++) {
    int bin = roundf((n / 360.f) * Ori[k]);
    if (bin >= n)
      bin -= n;
    if (bin < 0)
      bin += n;
    temphist[bin] += W[k] * Mag[k];
  }

  // smooth the histogram
  temphist[-1] = temphist[n - 1];
  temphist[-2] = temphist[n - 2];
  temphist[n] = temphist[0];
  temphist[n + 1] = temphist[1];

  for (i = 0; i < n; i++) {
    hist[i] = (temphist[i - 2] + temphist[i + 2]) * (1.f / 16.f) +
              (temphist[i - 1] + temphist[i + 1]) * (4.f / 16.f) +
              temphist[i] * (6.f / 16.f);
  }

  float maxval = hist[0];
  for (i = 1; i < n; i++)
    maxval = max(maxval, hist[i]);

  return maxval;
}

//bool adjustLocalExtrema(const std::vector<Mat> &dog_pyr, int octv, int &layer,
//                        int &r, int &c, int nOctaveLayers,
//                        float contrastThreshold, float edgeThreshold,
//                        float sigma) {
//  const float img_scale = 1.f / (255 * SIFT_FIXPT_SCALE);
//  const float deriv_scale = img_scale * 0.5f;
//  const float second_deriv_scale = img_scale;
//  const float cross_deriv_scale = img_scale * 0.25f;
//
//  float xi = 0, xr = 0, xc = 0, contr = 0;
//  int i = 0;
//
//  for (; i < SIFT_MAX_INTERP_STEPS; i++) {
//    int idx = octv * (nOctaveLayers + 2) + layer;
//    const Mat &img = dog_pyr[idx];
//    const Mat &prev = dog_pyr[idx - 1];
//    const Mat &next = dog_pyr[idx + 1];
//
//    Vec3f dD(
//        (img.at<sift_wt>(r, c + 1) - img.at<sift_wt>(r, c - 1)) * deriv_scale,
//        (img.at<sift_wt>(r + 1, c) - img.at<sift_wt>(r - 1, c)) * deriv_scale,
//        (next.at<sift_wt>(r, c) - prev.at<sift_wt>(r, c)) * deriv_scale);
//
//    float v2 = (float)img.at<sift_wt>(r, c) * 2;
//    float dxx = (img.at<sift_wt>(r, c + 1) + img.at<sift_wt>(r, c - 1) - v2) *
//                second_deriv_scale;
//    float dyy = (img.at<sift_wt>(r + 1, c) + img.at<sift_wt>(r - 1, c) - v2) *
//                second_deriv_scale;
//    float dss = (next.at<sift_wt>(r, c) + prev.at<sift_wt>(r, c) - v2) *
//                second_deriv_scale;
//    float dxy =
//        (img.at<sift_wt>(r + 1, c + 1) - img.at<sift_wt>(r + 1, c - 1) -
//         img.at<sift_wt>(r - 1, c + 1) + img.at<sift_wt>(r - 1, c - 1)) *
//        cross_deriv_scale;
//    float dxs = (next.at<sift_wt>(r, c + 1) - next.at<sift_wt>(r, c - 1) -
//                 prev.at<sift_wt>(r, c + 1) + prev.at<sift_wt>(r, c - 1)) *
//                cross_deriv_scale;
//    float dys = (next.at<sift_wt>(r + 1, c) - next.at<sift_wt>(r - 1, c) -
//                 prev.at<sift_wt>(r + 1, c) + prev.at<sift_wt>(r - 1, c)) *
//                cross_deriv_scale;
//
//    Matx33f H(dxx, dxy, dxs, dxy, dyy, dys, dxs, dys, dss);
//
//    Vec3f X = H.solve(dD, DECOMP_LU);
//
//    xi = -X[2];
//    xr = -X[1];
//    xc = -X[0];
//
//    if (std::abs(xi) < 0.5f && std::abs(xr) < 0.5f && std::abs(xc) < 0.5f)
//      break;
//
//    if (std::abs(xi) > (float)(INT_MAX / 3) ||
//        std::abs(xr) > (float)(INT_MAX / 3) ||
//        std::abs(xc) > (float)(INT_MAX / 3))
//      return false;
//
//    c += cvRound(xc);
//    r += cvRound(xr);
//    layer += cvRound(xi);
//
//    if (layer < 1 || layer > nOctaveLayers || c < SIFT_IMG_BORDER ||
//        c >= img.cols - SIFT_IMG_BORDER || r < SIFT_IMG_BORDER ||
//        r >= img.rows - SIFT_IMG_BORDER)
//      return false;
//  }
//
//  // ensure convergence of interpolation
//  if (i >= SIFT_MAX_INTERP_STEPS)
//    return false;
//
//  return true;
//}

// class findScaleSpaceExtremaComputer : public ParallelLoopBody
//{
// public:
//    findScaleSpaceExtremaComputer(
//        int _o,
//        int _i,
//        int _threshold,
//        int _idx,
//        int _step,
//        int _cols,
//        int _nOctaveLayers,
//        double _contrastThreshold,
//        double _edgeThreshold,
//        double _sigma,
//        const std::vector<Mat>& _gauss_pyr,
//        const std::vector<Mat>& _dog_pyr,
//        TLSData<std::vector<KeyPoint> > &_tls_kpts_struct)
//
//        : o(_o),
//          i(_i),
//          threshold(_threshold),
//          idx(_idx),
//          step(_step),
//          cols(_cols),
//          nOctaveLayers(_nOctaveLayers),
//          contrastThreshold(_contrastThreshold),
//          edgeThreshold(_edgeThreshold),
//          sigma(_sigma),
//          gauss_pyr(_gauss_pyr),
//          dog_pyr(_dog_pyr),
//          tls_kpts_struct(_tls_kpts_struct) { }
//    void operator()( const cv::Range& range ) const
//    {
//        const int begin = range.start;
//        const int end = range.end;
//
//        static const int n = SIFT_ORI_HIST_BINS;
//        float hist[n];
//
//        const Mat& img = dog_pyr[idx];
//        const Mat& prev = dog_pyr[idx-1];
//        const Mat& next = dog_pyr[idx+1];
//
//        std::vector<KeyPoint> *tls_kpts = tls_kpts_struct.get();
//
//        KeyPoint kpt;
//        for( int r = begin; r < end; r++)
//        {
//            const sift_wt* currptr = img.ptr<sift_wt>(r);
//            const sift_wt* prevptr = prev.ptr<sift_wt>(r);
//            const sift_wt* nextptr = next.ptr<sift_wt>(r);
//
//            for( int c = SIFT_IMG_BORDER; c < cols-SIFT_IMG_BORDER; c++)
//            {
//                sift_wt val = currptr[c];
//
//                // find local extrema with pixel accuracy
//                if( std::abs(val) > threshold &&
//                   ((val > 0 && val >= currptr[c-1] && val >= currptr[c+1] &&
//                     val >= currptr[c-step-1] && val >= currptr[c-step] && val
//                     >= currptr[c-step+1] &&
//                     val >= currptr[c+step-1] && val >= currptr[c+step] && val
//                     >= currptr[c+step+1] &&
//                     val >= nextptr[c] && val >= nextptr[c-1] && val >=
//                     nextptr[c+1] &&
//                     val >= nextptr[c-step-1] && val >= nextptr[c-step] && val
//                     >= nextptr[c-step+1] &&
//                     val >= nextptr[c+step-1] && val >= nextptr[c+step] && val
//                     >= nextptr[c+step+1] &&
//                     val >= prevptr[c] && val >= prevptr[c-1] && val >=
//                     prevptr[c+1] &&
//                     val >= prevptr[c-step-1] && val >= prevptr[c-step] && val
//                     >= prevptr[c-step+1] &&
//                     val >= prevptr[c+step-1] && val >= prevptr[c+step] && val
//                     >= prevptr[c+step+1]) ||
//                    (val < 0 && val <= currptr[c-1] && val <= currptr[c+1] &&
//                     val <= currptr[c-step-1] && val <= currptr[c-step] && val
//                     <= currptr[c-step+1] &&
//                     val <= currptr[c+step-1] && val <= currptr[c+step] && val
//                     <= currptr[c+step+1] &&
//                     val <= nextptr[c] && val <= nextptr[c-1] && val <=
//                     nextptr[c+1] &&
//                     val <= nextptr[c-step-1] && val <= nextptr[c-step] && val
//                     <= nextptr[c-step+1] &&
//                     val <= nextptr[c+step-1] && val <= nextptr[c+step] && val
//                     <= nextptr[c+step+1] &&
//                     val <= prevptr[c] && val <= prevptr[c-1] && val <=
//                     prevptr[c+1] &&
//                     val <= prevptr[c-step-1] && val <= prevptr[c-step] && val
//                     <= prevptr[c-step+1] &&
//                     val <= prevptr[c+step-1] && val <= prevptr[c+step] && val
//                     <= prevptr[c+step+1])))
//                {
//                    int r1 = r, c1 = c, layer = i;
//                    if( !adjustLocalExtrema(dog_pyr, kpt, o, layer, r1, c1,
//                                            nOctaveLayers,
//                                            (float)contrastThreshold,
//                                            (float)edgeThreshold,
//                                            (float)sigma) )
//                        continue;
//                    float scl_octv = kpt.size*0.5f/(1 << o);
//                    float omax =
//                    calcOrientationHist(gauss_pyr[o*(nOctaveLayers+3) +
//                    layer],
//                                                     Point(c1, r1),
//                                                     cvRound(SIFT_ORI_RADIUS *
//                                                     scl_octv),
//                                                     SIFT_ORI_SIG_FCTR *
//                                                     scl_octv,
//                                                     hist, n);
//                    float mag_thr = (float)(omax * SIFT_ORI_PEAK_RATIO);
//                    for( int j = 0; j < n; j++ )
//                    {
//                        int l = j > 0 ? j - 1 : n - 1;
//                        int r2 = j < n-1 ? j + 1 : 0;
//
//                        if( hist[j] > hist[l]  &&  hist[j] > hist[r2]  &&
//                        hist[j] >= mag_thr )
//                        {
//                            float bin = j + 0.5f * (hist[l]-hist[r2]) /
//                            (hist[l] - 2*hist[j] + hist[r2]);
//                            bin = bin < 0 ? n + bin : bin >= n ? bin - n :
//                            bin;
//                            kpt.angle = 360.f - (float)((360.f/n) * bin);
//                            if(std::abs(kpt.angle - 360.f) < FLT_EPSILON)
//                                kpt.angle = 0.f;
//                            {
//                                tls_kpts->push_back(kpt);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
// private:
//    int o, i;
//    int threshold;
//    int idx, step, cols;
//    int nOctaveLayers;
//    double contrastThreshold;
//    double edgeThreshold;
//    double sigma;
//    const std::vector<Mat>& gauss_pyr;
//    const std::vector<Mat>& dog_pyr;
//    TLSData<std::vector<KeyPoint> > &tls_kpts_struct;
//};

static void calcSIFTDescriptor(int rows, int cols, int size, int ptx, int pty,
                               float ori, float scl, int d, int n, float *dst) {
  float cos_t = cosf(ori * (float)(CV_PI / 180));
  float sin_t = sinf(ori * (float)(CV_PI / 180));
  float bins_per_rad = n / 360.f;
  float exp_scale = -1.f / (d * d * 0.5f);
  float hist_width = SIFT_DESCR_SCL_FCTR * scl;
  int radius = (int) (hist_width * 1.4142135623730951f * (d + 1) * 0.5f + 0.5);
  radius = min(radius, (int)sqrt(cols * cols + rows * rows));
  cos_t /= hist_width;
  sin_t /= hist_width;

  int i, j, k, len = (radius * 2 + 1) * (radius * 2 + 1),
               histlen = (d + 2) * (d + 2) * (n + 2);

  float *buf = (float *)malloc((len * 6 + histlen) * sizeof(float));
  float *X = buf, *Y = X + len, *Mag = Y, *Ori = Mag + len, *W = Ori + len;
  float *RBin = W + len, *CBin = RBin + len, *hist = CBin + len;

  for (i = 0; i < d + 2; i++) {
    for (j = 0; j < d + 2; j++)
      for (k = 0; k < n + 2; k++)
        hist[(i * (d + 2) + j) * (n + 2) + k] = 0.;
  }

  for (i = -radius, k = 0; i <= radius; i++)
    for (j = -radius; j <= radius; j++) {
      // Calculate sample's histogram array coords rotated relative to ori.
      // Subtract 0.5 so samples that fall e.g. in the center of row 1 (i.e.
      // r_rot = 1.5) have full weight placed in row 1 after interpolation.
      float c_rot = j * cos_t - i * sin_t;
      float r_rot = j * sin_t + i * cos_t;
      float rbin = r_rot + d / 2 - 0.5f;
      float cbin = c_rot + d / 2 - 0.5f;
      int r = pty + i, c = ptx + j;

      if (rbin > -1 && rbin < d && cbin > -1 && cbin < d && r > 0 &&
          r < rows - 1 && c > 0 && c < cols - 1) {
        float dx = (float)(at(r, c + 1, size) - at(r, c - 1, size));
        float dy = (float)(at(r - 1, c, size) - at(r + 1, c, size));
        X[k] = dx;
        Y[k] = dy;
        RBin[k] = rbin;
        CBin[k] = cbin;
        W[k] = (c_rot * c_rot + r_rot * r_rot) * exp_scale;
        k++;
      }
    }

  len = k;
  int t = 0;
  // cv::hal::exp32f(W, W, len);
  while (t < len) {
    Ori[t] = atan2(Y[t], X[t]);
    t++;
  }
  // cv::hal::fastAtan2(Y, X, Ori, len, true);
  t = 0;
  while (t < len)
    W[t] = exp(W[t++]);

  // cv::hal::fastAtan2(Y, X, Ori, len, true);
  // cv::hal::magnitude32f(X, Y, Mag, len);
  // cv::hal::exp32f(W, W, len);

  k = 0;
  for (; k < len; k++) {
    float rbin = RBin[k], cbin = CBin[k];
    float obin = (Ori[k] - ori) * bins_per_rad;
    float mag = Mag[k] * W[k];

    int r0 = (int) (rbin);
    int c0 = (int) (cbin);
    int o0 = (int) (obin);
    rbin -= r0;
    cbin -= c0;
    obin -= o0;

    if (o0 < 0)
      o0 += n;
    if (o0 >= n)
      o0 -= n;

    // histogram update using tri-linear interpolation
    float v_r1 = mag * rbin, v_r0 = mag - v_r1;
    float v_rc11 = v_r1 * cbin, v_rc10 = v_r1 - v_rc11;
    float v_rc01 = v_r0 * cbin, v_rc00 = v_r0 - v_rc01;
    float v_rco111 = v_rc11 * obin, v_rco110 = v_rc11 - v_rco111;
    float v_rco101 = v_rc10 * obin, v_rco100 = v_rc10 - v_rco101;
    float v_rco011 = v_rc01 * obin, v_rco010 = v_rc01 - v_rco011;
    float v_rco001 = v_rc00 * obin, v_rco000 = v_rc00 - v_rco001;

    int idx = ((r0 + 1) * (d + 2) + c0 + 1) * (n + 2) + o0;
    hist[idx] += v_rco000;
    hist[idx + 1] += v_rco001;
    hist[idx + (n + 2)] += v_rco010;
    hist[idx + (n + 3)] += v_rco011;
    hist[idx + (d + 2) * (n + 2)] += v_rco100;
    hist[idx + (d + 2) * (n + 2) + 1] += v_rco101;
    hist[idx + (d + 3) * (n + 2)] += v_rco110;
    hist[idx + (d + 3) * (n + 2) + 1] += v_rco111;
  }

  // finalize histogram, since the orientation histograms are circular
  for (i = 0; i < d; i++)
    for (j = 0; j < d; j++) {
      int idx = ((i + 1) * (d + 2) + (j + 1)) * (n + 2);
      hist[idx] += hist[idx + n];
      hist[idx + 1] += hist[idx + n + 1];
      for (k = 0; k < n; k++)
        dst[(i * d + j) * n + k] = hist[idx + k];
    }
  // copy histogram to the descriptor,
  // apply hysteresis thresholding
  // and scale the result, so that it can be easily converted
  // to byte array
  float nrm2 = 0;
  len = d * d * n;
  k = 0;
  for (; k < len; k++)
    nrm2 += dst[k] * dst[k];

  float thr = sqrt(nrm2) * SIFT_DESCR_MAG_THR;

  i = 0, nrm2 = 0;
  for (; i < len; i++) {
    float val = min(dst[i], thr);
    dst[i] = val;
    nrm2 += val * val;
  }
  nrm2 = SIFT_INT_DESCR_FCTR / max(sqrt(nrm2), FLT_EPSILON);

#if 0
    k = 0;
    for( ; k < len; k++ )
    {
        dst[k] = saturate_cast<uchar>(dst[k]*nrm2);
    }
#else
  float nrm1 = 0;
  for (k = 0; k < len; k++) {
    dst[k] *= nrm2;
    nrm1 += dst[k];
  }
  nrm1 = 1.f / max(nrm1, FLT_EPSILON);
  for (k = 0; k < len; k++) {
    dst[k] = sqrt(dst[k] * nrm1); // saturate_cast<uchar>(std::sqrt(dst[k]
                                       // * nrm1)*SIFT_INT_DESCR_FCTR);
  }
#endif
}

