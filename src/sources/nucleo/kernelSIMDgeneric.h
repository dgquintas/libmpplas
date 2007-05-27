/* 
 * $Id$
 *
 */

#ifndef __KERNELSIMDGENERIC_H
#define __KERNELSIMDGENERIC_H

namespace mpplas{

  namespace SIMDCPU{ 

    /* FLOAT */
#ifndef __FLOAT_SIMD

    template<> 
      const short SIMDCPUImpl<float>::ELEMENTS_PER_DIGIT= 4;


    template<>
      inline void SIMDCPUImpl<float>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const float* const a( (const float* const) (&(arg1.f)) );
        const float* const b( (const float* const) (&(arg2.f)) );
        float* const  c( (float* const) (&(out.f)) );


        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] + b[i];
        }
      }


    template<>
      inline void SIMDCPUImpl<float>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const float* const a( (const float* const) (&(arg1.f)) );
        const float* const b( (const float* const) (&(arg2.f)) );
        float*  const c( (float* const)(&(out.f)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] - b[i];
        }

      }



    template<>
      inline void SIMDCPUImpl<float>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const float* const a( (const float* const) (&(arg1.f)) );
        const float* const b( (const float* const) (&(arg2.f)) );
        float* const c( (float* const) (&(out.f)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] * b[i];
        }

      }

    template<>
      inline void SIMDCPUImpl<float>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const float* const a( (const float* const) (&(arg1.f)) );
        const float* const b( (const float* const) (&(arg2.f)) );
        float* const c( (float* const) (&(out.f)) );


        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] / b[i];
        }

      }

    template<>
      inline void SIMDCPUImpl<float>::Sum(float& out,SIMDDigit arg1){
        const float* const in( (const float* const) (&(arg1.f)) );
        out = 0.0f;

        for( int i=0; i < ELEMENTS_PER_DIGIT; i++){
          out += in[i];
        }
      }



    template<>
      inline void SIMDCPUImpl<float>::Pack(SIMDDigit& out, const float* const src){
        float* const c( (float* const) (&(out.f)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = src[i];
        }

      }


    template<>
      inline void SIMDCPUImpl<float>::Unpack(float* const out, const SIMDDigit& src ){
        const float* const c( (const float* const) (&(src.f)) );
        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          out[i] = c[i];
        }
      }
#endif


    /* DOUBLE */
#ifndef __DOUBLE_SIMD

    template<> 
      const short SIMDCPUImpl<double>::ELEMENTS_PER_DIGIT= 2;

    template<>
      inline void SIMDCPUImpl<double>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const double* const a( (const double* const) (&(arg1.d)) );
        const double* const b( (const double* const) (&(arg2.d)) );
        double* const c( (double* const) (&(out.d)) );


        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] + b[i];
        }
      }


    template<>
      inline void SIMDCPUImpl<double>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const double* const a( (const double* const) (&(arg1.d)) );
        const double* const b( (const double* const) (&(arg2.d)) );
        double* const c( (double* const) (&(out.d)) );


        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] - b[i];
        }
      }



    template<>
      inline void SIMDCPUImpl<double>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const double* const a( (const double* const) (&(arg1.d)) );
        const double* const b( (const double* const) (&(arg2.d)) );
        double* const c( (double* const) (&(out.d)) );


        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] * b[i];
        }
      }

    template<>
      inline void SIMDCPUImpl<double>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const double* const a( (const double* const) (&(arg1.d)) );
        const double* const b( (const double* const) (&(arg2.d)) );
        double* const c( (double* const) (&(out.d)) );


        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] / b[i];
        }

      }

    template<>
      inline void SIMDCPUImpl<double>::Sum(double& out,SIMDDigit arg1){
        const double* const in( (const double* const) (&(arg1.d)) );
        out = 0.0;

        for( int i=0; i < ELEMENTS_PER_DIGIT; i++){
          out += in[i];
        }
      }


    template<>
      inline void SIMDCPUImpl<double>::Pack(SIMDDigit& out, const double* const src){
        double* const c( (double* const) (&(out.d)) );


        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = src[i];
        }
      }


    template<>
      inline void SIMDCPUImpl<double>::Unpack(double* const out, const SIMDDigit& src ){
        const double* const c( (const double* const) (&(src.d)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          out[i] = c[i];
        }
      }

#endif






    /* INT 16 */
#ifndef __INT_SIMD

    template<> 
      const short SIMDCPUImpl<int16_t>::ELEMENTS_PER_DIGIT= 8;


    template<>
      inline void SIMDCPUImpl<int16_t>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const int16_t* const a( (const int16_t* const) (&(arg1.i)) );
        const int16_t* const b( (const int16_t* const) (&(arg2.i)) );
        int16_t* c( (int16_t* const) (&(out.i)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] + b[i];
        }
      }


    template<>
      inline void SIMDCPUImpl<int16_t>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const int16_t* const a( (const int16_t* const) (&(arg1.i)) );
        const int16_t* const b( (const int16_t* const) (&(arg2.i)) );
        int16_t* c( (int16_t* const) (&(out.i)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] - b[i];
        }

      }



    template<>
      inline void SIMDCPUImpl<int16_t>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const int16_t* const a( (const int16_t* const) (&(arg1.i)) );
        const int16_t* const b( (const int16_t* const) (&(arg2.i)) );
        int16_t* c( (int16_t* const) (&(out.i)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] * b[i];
        }

      }

    template<>
      inline void SIMDCPUImpl<int16_t>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const int16_t* const a( (const int16_t* const) (&(arg1.i)) );
        const int16_t* const b( (const int16_t* const) (&(arg2.i)) );
        int16_t* c( (int16_t* const) (&(out.i)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = a[i] / b[i];
        }

      }

    template<>
      inline void SIMDCPUImpl<int16_t>::Sum(int16_t& out,SIMDDigit arg1){
        const int16_t* const in( (const int16_t* const) (&(arg1.i)) );
        out = 0;

        for( int i=0; i < ELEMENTS_PER_DIGIT; i++){
          out += in[i];
        }
      }


    template<>
      inline void SIMDCPUImpl<int16_t>::Pack(SIMDDigit& out, const int16_t* const src){
        int16_t* const c( (int16_t* const) (&(out.i)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          c[i] = src[i];
        }

      }


    template<>
      inline void SIMDCPUImpl<int16_t>::Unpack(int16_t* const out, const SIMDDigit& src ){
        const int16_t* const c( (const int16_t* const) (&(src.i)) );

        for(int i=0; i < ELEMENTS_PER_DIGIT; i++){
          out[i] = c[i];
        }

      }
    #endif
  }
}


#endif
