#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

#include "cdefs.h"

void integral_uchar_int_double(uchar* src, size_t _srcstep, int* sum, size_t _sumstep,
                double* sqsum, size_t _sqsumstep, int* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(uchar));
    int sumstep = (int)(_sumstep/sizeof(int));
    int tiltedstep = (int)(_tiltedstep/sizeof(int));
    int sqsumstep = (int)(_sqsumstep/sizeof(double));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                int s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                int s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    uchar it = src[x];
                    s += it;
                    sq += (double)it*it;
                    int t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        int s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                uchar it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                uchar it = src[0];
                int t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    int t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    int t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_uchar_int_float(uchar* src, size_t _srcstep, int* sum, size_t _sumstep,
                float* sqsum, size_t _sqsumstep, int* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(uchar));
    int sumstep = (int)(_sumstep/sizeof(int));
    int tiltedstep = (int)(_tiltedstep/sizeof(int));
    int sqsumstep = (int)(_sqsumstep/sizeof(float));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                int s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                int s = sum[-cn] = 0;
                float sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    uchar it = src[x];
                    s += it;
                    sq += (float)it*it;
                    int t = sum[x - sumstep] + s;
                    float tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        int s;
        float sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                uchar it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (float)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                uchar it = src[0];
                int t0 = s = it;
                float tq0 = sq = (float)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    int t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (float)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    int t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (float)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_uchar_int_int(uchar* src, size_t _srcstep, int* sum, size_t _sumstep,
                int* sqsum, size_t _sqsumstep, int* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(uchar));
    int sumstep = (int)(_sumstep/sizeof(int));
    int tiltedstep = (int)(_tiltedstep/sizeof(int));
    int sqsumstep = (int)(_sqsumstep/sizeof(int));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                int s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                int s = sum[-cn] = 0;
                int sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    uchar it = src[x];
                    s += it;
                    sq += (int)it*it;
                    int t = sum[x - sumstep] + s;
                    int tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        int s;
        int sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                uchar it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (int)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                uchar it = src[0];
                int t0 = s = it;
                int tq0 = sq = (int)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    int t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (int)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    int t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (int)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_uchar_float_double(uchar* src, size_t _srcstep, float* sum, size_t _sumstep,
                double* sqsum, size_t _sqsumstep, float* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(uchar));
    int sumstep = (int)(_sumstep/sizeof(float));
    int tiltedstep = (int)(_tiltedstep/sizeof(float));
    int sqsumstep = (int)(_sqsumstep/sizeof(double));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                float s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                float s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    uchar it = src[x];
                    s += it;
                    sq += (double)it*it;
                    float t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        float s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                uchar it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                uchar it = src[0];
                float t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    float t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    float t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_uchar_float_float(uchar* src, size_t _srcstep, float* sum, size_t _sumstep,
                float* sqsum, size_t _sqsumstep, float* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(uchar));
    int sumstep = (int)(_sumstep/sizeof(float));
    int tiltedstep = (int)(_tiltedstep/sizeof(float));
    int sqsumstep = (int)(_sqsumstep/sizeof(float));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                float s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                float s = sum[-cn] = 0;
                float sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    uchar it = src[x];
                    s += it;
                    sq += (float)it*it;
                    float t = sum[x - sumstep] + s;
                    float tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        float s;
        float sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                uchar it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (float)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                uchar it = src[0];
                float t0 = s = it;
                float tq0 = sq = (float)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    float t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (float)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    float t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (float)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_uchar_double_double(uchar* src, size_t _srcstep, double* sum, size_t _sumstep,
                double* sqsum, size_t _sqsumstep, double* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(uchar));
    int sumstep = (int)(_sumstep/sizeof(double));
    int tiltedstep = (int)(_tiltedstep/sizeof(double));
    int sqsumstep = (int)(_sqsumstep/sizeof(double));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                double s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                double s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    uchar it = src[x];
                    s += it;
                    sq += (double)it*it;
                    double t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        double s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                uchar it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                uchar it = src[0];
                double t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_ushort_double_double(ushort* src, size_t _srcstep, double* sum, size_t _sumstep,
                double* sqsum, size_t _sqsumstep, double* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(ushort));
    int sumstep = (int)(_sumstep/sizeof(double));
    int tiltedstep = (int)(_tiltedstep/sizeof(double));
    int sqsumstep = (int)(_sqsumstep/sizeof(double));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                double s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                double s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    ushort it = src[x];
                    s += it;
                    sq += (double)it*it;
                    double t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        double s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                ushort it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                ushort it = src[0];
                double t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_short_double_double(short* src, size_t _srcstep, double* sum, size_t _sumstep,
                double* sqsum, size_t _sqsumstep, double* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(short));
    int sumstep = (int)(_sumstep/sizeof(double));
    int tiltedstep = (int)(_tiltedstep/sizeof(double));
    int sqsumstep = (int)(_sqsumstep/sizeof(double));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                double s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                double s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    short it = src[x];
                    s += it;
                    sq += (double)it*it;
                    double t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        double s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                short it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                short it = src[0];
                double t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_float_float_double(float* src, size_t _srcstep, float* sum, size_t _sumstep,
                double* sqsum, size_t _sqsumstep, float* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(float));
    int sumstep = (int)(_sumstep/sizeof(float));
    int tiltedstep = (int)(_tiltedstep/sizeof(float));
    int sqsumstep = (int)(_sqsumstep/sizeof(double));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                float s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                float s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    float it = src[x];
                    s += it;
                    sq += (double)it*it;
                    float t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        float s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                float it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                float it = src[0];
                float t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    float t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    float t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_float_float_float(float* src, size_t _srcstep, float* sum, size_t _sumstep,
                float* sqsum, size_t _sqsumstep, float* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(float));
    int sumstep = (int)(_sumstep/sizeof(float));
    int tiltedstep = (int)(_tiltedstep/sizeof(float));
    int sqsumstep = (int)(_sqsumstep/sizeof(float));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                float s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                float s = sum[-cn] = 0;
                float sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    float it = src[x];
                    s += it;
                    sq += (float)it*it;
                    float t = sum[x - sumstep] + s;
                    float tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        float s;
        float sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                float it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (float)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                float it = src[0];
                float t0 = s = it;
                float tq0 = sq = (float)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    float t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (float)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    float t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (float)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_float_double_double(float* src, size_t _srcstep, double* sum, size_t _sumstep,
                double* sqsum, size_t _sqsumstep, double* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(float));
    int sumstep = (int)(_sumstep/sizeof(double));
    int tiltedstep = (int)(_tiltedstep/sizeof(double));
    int sqsumstep = (int)(_sqsumstep/sizeof(double));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                double s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                double s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    float it = src[x];
                    s += it;
                    sq += (double)it*it;
                    double t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        double s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                float it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                float it = src[0];
                double t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void integral_double_double_double(double* src, size_t _srcstep, double* sum, size_t _sumstep,
                double* sqsum, size_t _sqsumstep, double* tilted, size_t _tiltedstep,
                int width, int height, int cn )
{
    int x, y, k;

    int srcstep = (int)(_srcstep/sizeof(double));
    int sumstep = (int)(_sumstep/sizeof(double));
    int tiltedstep = (int)(_tiltedstep/sizeof(double));
    int sqsumstep = (int)(_sqsumstep/sizeof(double));

    width *= cn;

    memset( sum, 0, (width+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (width+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (width+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                double s = sum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < height; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                double s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < width; x += cn )
                {
                    double it = src[x];
                    s += it;
                    sq += (double)it*it;
                    double t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        int* buf = (int) malloc((width+cn) * sizeof(int));
        double s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < width; x += cn )
            {
                double it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( width == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < height; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                double it = src[0];
                double t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < width - cn; x += cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( width > cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}
