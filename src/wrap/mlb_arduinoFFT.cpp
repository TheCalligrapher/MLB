#include "mlb_arduinoFFT.h"
#include "impl/mlb_wrapper.h"

#include <new>
#include <arduinoFFT.h>

//char a[sizeof(arduinoFFT)];
//char (*b)[sizeof(MlbarduinoFFT)] = &a;
mlb_static_assert(sizeof(MlbarduinoFFT) == sizeof(arduinoFFT));

void afft_construct(MlbarduinoFFT *p, double *vReal, double *vImag, 
                    uint16_t samples, double samplingFrequency)
{
  assert(p != nullptr);
  new (p) arduinoFFT(vReal, vImag, samples, samplingFrequency);
}

void afft_destruct(MlbarduinoFFT *p)
{
  assert(p != nullptr);
  arduinoFFT *d = reinterpret_cast<arduinoFFT *>(p);
  d->~arduinoFFT();
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbarduinoFFT
#define MLB_CPP_WRAPPER_CPP_CLASS arduinoFFT

  MLB_CPP_WRAPPER_DEF(void, afft_complex_to_magnitude, ComplexToMagnitude)
  MLB_CPP_WRAPPER_DEF(void, afft_compute, Compute, uint8_t, dir)
  MLB_CPP_WRAPPER_DEF(void, afft_dc_removal, DCRemoval)
  MLB_CPP_WRAPPER_DEF(double, afft_major_peak_f, MajorPeak)
  MLB_CPP_WRAPPER_DEF(void, afft_major_peak, MajorPeak, double *, f, double *, v)
  MLB_CPP_WRAPPER_DEF(void, afft_windowing, Windowing, uint8_t, windowType, uint8_t, dir)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

