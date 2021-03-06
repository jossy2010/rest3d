/*
Copyright (c) 2013 Khaled Mammou - Advanced Micro Devices, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#pragma once
#ifndef O3DGC_COMMON_H
#define O3DGC_COMMON_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

namespace o3dgc
{
    typedef float        Real;
    typedef unsigned int Index;
    const double O3DGC_MAX_DOUBLE  = 1.79769e+308;
    const long O3DGC_MIN_LONG      = -2147483647;
    const long O3DGC_MAX_LONG      =  2147483647;
    const long O3DGC_MAX_UCHAR8    = 255;
    const long O3DGC_MAX_TFAN_SIZE = 256;

    const unsigned long O3DGC_SC3DMC_START_CODE               = 0x00001F1;
    const unsigned long O3DGC_SC3DMC_MAX_NUM_FLOAT_ATTRIBUTES = 256;
    const unsigned long O3DGC_SC3DMC_MAX_NUM_INT_ATTRIBUTES   = 256;
    const unsigned long O3DGC_SC3DMC_MAX_DIM_FLOAT_ATTRIBUTES = 8;
    const unsigned long O3DGC_SC3DMC_MAX_DIM_INT_ATTRIBUTES   = 8;

    const unsigned long O3DGC_SC3DMC_MAX_PREDICTION_NEIGHBORS = 8;
    const unsigned long O3DGC_SC3DMC_MAX_PREDICTION_SYMBOLS   = 257;

    enum O3DGCEndianness
    {
        O3DGC_BIG_ENDIAN     = 0,
        O3DGC_LITTLE_ENDIAN  = 1
    };
    enum O3DGCErrorCode
    {
        O3DGC_OK,
        O3DGC_ERROR_BUFFER_FULL,
        O3DGC_ERROR_CREATE_FILE,
        O3DGC_ERROR_OPEN_FILE,
        O3DGC_ERROR_READ_FILE,
        O3DGC_ERROR_CORRUPTED_STREAM,
        O3DGC_ERROR_NON_SUPPORTED_FEATURE
    };
    enum O3DGCSC3DMCBinarization
    {
        O3DGC_SC3DMC_BINARIZATION_FL     = 0,            // Fixed Length (not supported)
        O3DGC_SC3DMC_BINARIZATION_BP     = 1,            // BPC (not supported)
        O3DGC_SC3DMC_BINARIZATION_FC     = 2,            // 4 bits Coding (not supported)
        O3DGC_SC3DMC_BINARIZATION_AC     = 3,            // Arithmetic Coding (not supported)
        O3DGC_SC3DMC_BINARIZATION_AC_EGC = 4,            // Arithmetic Coding & EGCk
        O3DGC_SC3DMC_BINARIZATION_ASCII  = 5             // Arithmetic Coding & EGCk
    };
    enum O3DGCSC3DMCStreamType
    {
        O3DGC_SC3DMC_STREAM_TYPE_UNKOWN = 0,
        O3DGC_SC3DMC_STREAM_TYPE_ASCII  = 1,
        O3DGC_SC3DMC_STREAM_TYPE_BINARY = 2
    };


    enum O3DGCSC3DMCQuantizationMode
    {
        O3DGC_SC3DMC_DIAG_BB             = 0, // supported
        O3DGC_SC3DMC_MAX_ALL_DIMS        = 1, // supported
        O3DGC_SC3DMC_MAX_SEP_DIM         = 2  // supported
    };
    enum O3DGCSC3DMCPredictionMode
    {
        O3DGC_SC3DMC_NO_PREDICTION                   = 0, // supported
        O3DGC_SC3DMC_DIFFERENTIAL_PREDICTION         = 1, // supported
//      O3DGC_SC3DMC_XORPrediction                  = 2, // not supported
//      O3DGC_SC3DMC_AdaptiveDifferentialPrediction = 3, // not supported
//      O3DGC_SC3DMC_CircularDifferentialPrediction = 4, // not supported
        O3DGC_SC3DMC_PARALLELOGRAM_PREDICTION        = 5,  // supported
        O3DGC_SC3DMC_SURF_NORMALS_PREDICTION         = 6   // supported
    };
    enum O3DGCSC3DMCEncodingMode
    {
        O3DGC_SC3DMC_QBCR       = 0,        // not supported
        O3DGC_SC3DMC_SVA        = 1,        // not supported
        O3DGC_SC3DMC_TFAN       = 2,        // supported
    };    
    template<class T> 
    inline const T absolute(const T& a)
    {
        return (a < (T)(0)) ? -a : a;
    }
    template<class T> 
    inline const T min(const T& a, const T& b)
    {
        return (b < a) ? b : a;
    }
    template<class T> 
    inline const T max(const T& a, const T& b)
    {
        return (b > a) ? b : a;
    }
    template<class T> 
    inline void swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
    inline double log2( double n )  
    {  
        return log(n) / log(2.0);  
    }

    inline O3DGCEndianness SystemEndianness()
    {
        unsigned long num = 1;
        return ( *((char *)(&num)) == 1 )? O3DGC_LITTLE_ENDIAN : O3DGC_BIG_ENDIAN ;
    }
    class SC3DMCStats
    {
    public: 
                                    SC3DMCStats(void)
                                    {
                                        m_timeCoord                = 0.0;
                                        m_timeNormal               = 0.0;
                                        m_timeTexCoord             = 0.0;
                                        m_timeColor                = 0.0;
                                        m_timeCoordIndex           = 0.0;
                                        m_timeFloatAttribute       = 0.0;
                                        m_timeIntAttribute         = 0.0;
                                        m_timeReorder              = 0.0;
                                        m_streamSizeCoord          = 0;
                                        m_streamSizeNormal         = 0;
                                        m_streamSizeTexCoord       = 0;
                                        m_streamSizeColor          = 0;
                                        m_streamSizeCoordIndex     = 0;
                                        m_streamSizeFloatAttribute = 0;
                                        m_streamSizeIntAttribute   = 0;
                                    };
                                    ~SC3DMCStats(void){};
        
        double                      m_timeCoord;
        double                      m_timeNormal;
        double                      m_timeTexCoord;
        double                      m_timeColor;
        double                      m_timeCoordIndex;
        double                      m_timeFloatAttribute;
        double                      m_timeIntAttribute;
        double                      m_timeReorder;

        unsigned long               m_streamSizeCoord;
        unsigned long               m_streamSizeNormal;
        unsigned long               m_streamSizeTexCoord;
        unsigned long               m_streamSizeColor;
        unsigned long               m_streamSizeCoordIndex;
        unsigned long               m_streamSizeFloatAttribute;
        unsigned long               m_streamSizeIntAttribute;

    };
    typedef struct 
    {
        long          m_a;
        long          m_b;
        long          m_c;
    } SC3DMCTriplet;

    typedef struct 
    {
        SC3DMCTriplet m_id;
        long          m_pred[O3DGC_SC3DMC_MAX_DIM_FLOAT_ATTRIBUTES];
    } SC3DMCPredictor;

    inline bool operator< (const SC3DMCTriplet& lhs, const SC3DMCTriplet& rhs)
    {
          if (lhs.m_c != rhs.m_c)
          {
              return (lhs.m_c < rhs.m_c);
          }
          else if (lhs.m_b != rhs.m_b)
          {
              return (lhs.m_b < rhs.m_b);
          }
          return (lhs.m_a < rhs.m_a);
    }
    inline bool operator== (const SC3DMCTriplet& lhs, const SC3DMCTriplet& rhs)
    {
          return (lhs.m_c == rhs.m_c && lhs.m_b == rhs.m_b && lhs.m_a == rhs.m_a);
    }


    // fix me: optimize this function (e.g., binary search)
    inline unsigned long Insert(SC3DMCTriplet e, unsigned long & nPred, SC3DMCPredictor * const list)
    {
        unsigned long pos = 0xFFFFFFFF;
        bool foundOrInserted = false;
        for (unsigned long j = 0; j < nPred; ++j)
        {
            if (e == list[j].m_id)
            {
                foundOrInserted = true;
                break;
            }
            else if (e < list[j].m_id)
            {
                if (nPred < O3DGC_SC3DMC_MAX_PREDICTION_NEIGHBORS)
                {
                    ++nPred;
                }
                for (unsigned long h = nPred-1; h > j; --h)
                {
                    list[h] = list[h-1];
                }
                list[j].m_id = e;
                pos = j;
                foundOrInserted = true;
                break;
            }
        }
        if (!foundOrInserted && nPred < O3DGC_SC3DMC_MAX_PREDICTION_NEIGHBORS)
        {
            pos = nPred;
            list[nPred++].m_id = e;
        }
        return pos;
    }
    template <class T> 
    inline void SphereToCube(const T x, const T y, const T z, 
                             T & a, T & b, char & index)
    {
        T ax = absolute(x);
        T ay = absolute(y);
        T az = absolute(z);
        if (az >= ax && az >= ay)
        {
            if (z >= (T)(0))
            {
                index = 0;
                a = x;
                b = y;
            }
            else
            {
                index = 1;
                a = -x;
                b = -y;
            }
        }
        else if (ay >= ax && ay >= az)
        {
            if (y >= (T)(0))
            {
                index = 2;
                a = z;
                b = x;
            }
            else
            {
                index = 3;
                a = -z;
                b = -x;
            }
        }
        else if (ax >= ay && ax >= az)
        {
            if (x >= (T)(0))
            {
                index = 4;
                a = y;
                b = z;
            }
            else
            {
                index = 5;
                a = -y;
                b = -z;
            }
        }
    }
    inline void CubeToSphere(const Real a, const Real b, const char index,
                             Real & x, Real & y, Real & z)
    {
        switch( index )
        {
        case 0:
            x = a;
            y = b;
            z =  (Real) sqrt(max(0.0, 1.0 - x*x-y*y));
            break;
        case 1:
            x = -a;
            y = -b;
            z = -(Real) sqrt(max(0.0, 1.0 - x*x-y*y));
            break;
        case 2:
            z = a;
            x = b;
            y =  (Real) sqrt(max(0.0, 1.0 - x*x-z*z));
            break;
        case 3:
            z = -a;
            x = -b;
            y = -(Real) sqrt(max(0.0, 1.0 - x*x-z*z));
            break;
        case 4:
            y = a;
            z = b;
            x =  (Real) sqrt(max(0.0, 1.0 - y*y-z*z));
            break;
        case 5:
            y = -a;
            z = -b;
            x = -(Real) sqrt(max(0.0, 1.0 - y*y-z*z));
            break;
        }
    }

/*
    inline void SphereToCube(const Real x, const Real y, const Real z, 
                             Real & a, Real & b, long & index)
    {
        Real ax = fabs(x);
        Real ay = fabs(y);
        Real az = fabs(z);
        if (az >= ax && az >= ay)
        {
            if (z >= 0.0) index = 0;
            else          index = 4;
            if (x < 0.0)  index += 1;
            if (y < 0.0)  index += 2;
            a = ax;
            b = ay;
        }
        else if (ay >= ax && ay >= az)
        {
            if (y >= 0.0) index = 8;
            else          index = 12;
            if (x < 0.0)  index += 1;
            if (z < 0.0)  index += 2;
            a = ax;
            b = az;
        }
        else if (ax >= ay && ax >= az)
        {
            if (x >= 0.0) index = 16;
            else          index = 20;
            if (y < 0.0)  index += 1;
            if (z < 0.0)  index += 2;
            a = ay;
            b = az;
        }
    }
    inline void CubeToSphere(const Real a, const Real b, const long index,
                             Real & x, Real & y, Real & z)
    {
        const Real sign[2] = {1.0, -1.0};
        switch( index >> 2 )
        {
        case 0:
            x = a * sign[index&1];
            y = b * sign[index&2];
            z = (Real) sqrt(1.0 - x*x+y*y);
            break;
        case 1:
            x = a * sign[index&1];
            y = b * sign[index&2];
            z = (Real) -sqrt(1.0 - x*x+y*y);
            break;
        case 2:
            x = a * sign[index&1];
            z = b * sign[index&2];
            y = (Real) sqrt(1.0 - x*x+z*z);
            break;
        case 3:
            x = a * sign[index&1];
            z = b * sign[index&2];
            y = (Real) -sqrt(1.0 - x*x+z*z);
            break;
        case 4:
            y = a * sign[index&1];
            z = b * sign[index&2];
            x = (Real) sqrt(1.0 - y*y+z*z);
            break;
        case 5:
            y = a * sign[index&1];
            z = b * sign[index&2];
            x = (Real) -sqrt(1.0 - y*y+z*z);
            break;
        }
    }
    */
    inline unsigned long IntToUInt(long value)
    {
        return (value < 0)?(unsigned long) (-1 - (2 * value)):(unsigned long) (2 * value);
    }
    inline long UIntToInt(unsigned long uiValue)
    {
        return (uiValue & 1)?-((long) ((uiValue+1) >> 1)):((long) (uiValue >> 1));
    }
}
#endif // O3DGC_COMMON_H

