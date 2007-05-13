
/* FLOAT */
#ifndef __FLOAT_SIMD
  template<>
      inline void SIMDCPUImpl<float>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const float* const a( (const float* const) (&(arg1.f)) );
        const float* const b( (const float* const) (&(arg2.f)) );
        float* const  c( (float* const) (&(out.f)) );

        c[0] = a[0] + b[0];
        c[1] = a[1] + b[1];
        c[2] = a[2] + b[2];
        c[3] = a[3] + b[3];
      }


    template<>
      inline void SIMDCPUImpl<float>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const float* const a( (const float* const) (&(arg1.f)) );
        const float* const b( (const float* const) (&(arg2.f)) );
        float*  const c( (float* const)(&(out.f)) );

        c[0] = a[0] - b[0];
        c[1] = a[1] - b[1];
        c[2] = a[2] - b[2];
        c[3] = a[3] - b[3];

      }



    template<>
      inline void SIMDCPUImpl<float>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const float* const a( (const float* const) (&(arg1.f)) );
        const float* const b( (const float* const) (&(arg2.f)) );
        float* const c( (float* const) (&(out.f)) );


        c[0] = a[0] * b[0];
        c[1] = a[1] * b[1];
        c[2] = a[2] * b[2];
        c[3] = a[3] * b[3];
      }

    template<>
      inline void SIMDCPUImpl<float>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const float* const a( (const float* const) (&(arg1.f)) );
        const float* const b( (const float* const) (&(arg2.f)) );
        float* const c( (float* const) (&(out.f)) );


        c[0] = a[0] / b[0];
        c[1] = a[1] / b[1];
        c[2] = a[2] / b[2];
        c[3] = a[3] / b[3];

      }



    template<>
      inline void SIMDCPUImpl<float>::Pack(SIMDDigit& out, const float* const src){
        float* const c( (float* const) (&(out.f)) );

        c[0] = src[0];
        c[1] = src[1];
        c[2] = src[2];
        c[3] = src[3];
      }


    template<>
      inline void SIMDCPUImpl<float>::Unpack(float* const out, const SIMDDigit& src ){
        const float* const c( (const float* const) (&(src.f)) );

        out[0] = c[0];
        out[1] = c[1];
        out[2] = c[2];
        out[3] = c[3];
      }
#endif


/* DOUBLE */
#ifndef __DOUBLE_SIMD
  template<>
      inline void SIMDCPUImpl<double>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const double* const a( (const double* const) (&(arg1.d)) );
        const double* const b( (const double* const) (&(arg2.d)) );
        double* const c( (double* const) (&(out.d)) );

        c[0] = a[0] + b[0];
        c[1] = a[1] + b[1];
        c[2] = a[2] + b[2];
        c[3] = a[3] + b[3];
      }


    template<>
      inline void SIMDCPUImpl<double>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const double* const a( (const double* const) (&(arg1.d)) );
        const double* const b( (const double* const) (&(arg2.d)) );
        double* const c( (double* const) (&(out.d)) );

        c[0] = a[0] - b[0];
        c[1] = a[1] - b[1];
        c[2] = a[2] - b[2];
        c[3] = a[3] - b[3];

      }



    template<>
      inline void SIMDCPUImpl<double>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const double* const a( (const double* const) (&(arg1.d)) );
        const double* const b( (const double* const) (&(arg2.d)) );
        double* const c( (double* const) (&(out.d)) );

        c[0] = a[0] * b[0];
        c[1] = a[1] * b[1];
        c[2] = a[2] * b[2];
        c[3] = a[3] * b[3];
      }

    template<>
      inline void SIMDCPUImpl<double>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const double* const a( (const double* const) (&(arg1.d)) );
        const double* const b( (const double* const) (&(arg2.d)) );
        double* const c( (double* const) (&(out.d)) );

        c[0] = a[0] / b[0];
        c[1] = a[1] / b[1];
        c[2] = a[2] / b[2];
        c[3] = a[3] / b[3];

      }



    template<>
      inline void SIMDCPUImpl<double>::Pack(SIMDDigit& out, const double* const src){
        double* const c( (double* const) (&(out.d)) );

        c[0] = src[0];
        c[1] = src[1];
        c[2] = src[2];
        c[3] = src[3];
      }


    template<>
      inline void SIMDCPUImpl<double>::Unpack(double* const out, const SIMDDigit& src ){
        const double* const c( (const double* const) (&(src.d)) );

        out[0] = c[0];
        out[1] = c[1];
        out[2] = c[2];
        out[3] = c[3];
      }

#endif






#ifndef __INT_SIMD
/* INT 16 */
  template<>
      inline void SIMDCPUImpl<int16_t>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const int16_t* const a( (const int16_t* const) (&(arg1.i)) );
        const int16_t* const b( (const int16_t* const) (&(arg2.i)) );
        int16_t* c( (int16_t* const) (&(out.i)) );


        c[0] = a[0] + b[0];
        c[1] = a[1] + b[1];
        c[2] = a[2] + b[2];
        c[3] = a[3] + b[3];
      }


    template<>
      inline void SIMDCPUImpl<int16_t>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const int16_t* const a( (const int16_t* const) (&(arg1.i)) );
        const int16_t* const b( (const int16_t* const) (&(arg2.i)) );
        int16_t* c( (int16_t* const) (&(out.i)) );


        c[0] = a[0] - b[0];
        c[1] = a[1] - b[1];
        c[2] = a[2] - b[2];
        c[3] = a[3] - b[3];

      }



    template<>
      inline void SIMDCPUImpl<int16_t>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const int16_t* const a( (const int16_t* const) (&(arg1.i)) );
        const int16_t* const b( (const int16_t* const) (&(arg2.i)) );
        int16_t* c( (int16_t* const) (&(out.i)) );

        c[0] = a[0] * b[0];
        c[1] = a[1] * b[1];
        c[2] = a[2] * b[2];
        c[3] = a[3] * b[3];
      }

    template<>
      inline void SIMDCPUImpl<int16_t>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        const int16_t* const a( (const int16_t* const) (&(arg1.i)) );
        const int16_t* const b( (const int16_t* const) (&(arg2.i)) );
        int16_t* c( (int16_t* const) (&(out.i)) );

        c[0] = a[0] / b[0];
        c[1] = a[1] / b[1];
        c[2] = a[2] / b[2];
        c[3] = a[3] / b[3];

      }



    template<>
      inline void SIMDCPUImpl<int16_t>::Pack(SIMDDigit& out, const int16_t* const src){
        int16_t* const c( (int16_t* const) (&(out.i)) );

        c[0] = src[0];
        c[1] = src[1];
        c[2] = src[2];
        c[3] = src[3];
      }


    template<>
      inline void SIMDCPUImpl<int16_t>::Unpack(int16_t* const out, const SIMDDigit& src ){
        const int16_t* const c( (const int16_t* const) (&(src.i)) );

        out[0] = c[0];
        out[1] = c[1];
        out[2] = c[2];
        out[3] = c[3];
      }


#endif
