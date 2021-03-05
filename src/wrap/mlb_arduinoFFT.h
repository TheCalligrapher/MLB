#ifndef MLB_ARDUINO_FFT_H_
#define MLB_ARDUINO_FFT_H_

#include "base/mlb_config.h"
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

#define FFT_FORWARD 0x01
#define FFT_REVERSE 0x00

#define FFT_WIN_TYP_RECTANGLE 0x00 /* rectangle (Box car) */
#define FFT_WIN_TYP_HAMMING 0x01 /* hamming */
#define FFT_WIN_TYP_HANN 0x02 /* hann */
#define FFT_WIN_TYP_TRIANGLE 0x03 /* triangle (Bartlett) */
#define FFT_WIN_TYP_NUTTALL 0x04 /* nuttall */
#define FFT_WIN_TYP_BLACKMAN 0x05 /* blackman */
#define FFT_WIN_TYP_BLACKMAN_NUTTALL 0x06 /* blackman nuttall */
#define FFT_WIN_TYP_BLACKMAN_HARRIS 0x07 /* blackman harris*/
#define FFT_WIN_TYP_FLT_TOP 0x08 /* flat top */
#define FFT_WIN_TYP_WELCH 0x09 /* welch */

typedef struct MlbarduinoFFT
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[32];
#else
  char fill[11];
#endif
} MlbarduinoFFT;

/****************************************************************************************/

void afft_construct(MlbarduinoFFT *p, double *vReal, double *vImag, 
                    uint16_t samples, double samplingFrequency);
void afft_destruct(MlbarduinoFFT *p);

void afft_complex_to_magnitude(MlbarduinoFFT *p);
void afft_compute(MlbarduinoFFT *p, uint8_t dir);
void afft_dc_removal(MlbarduinoFFT *p);
double afft_major_peak_f(MlbarduinoFFT *p);
void afft_major_peak(MlbarduinoFFT *p, double *f, double *v);
void afft_windowing(MlbarduinoFFT *p, uint8_t windowType, uint8_t dir);

C_LINKAGE_END

#endif /* MLB_ARDUINO_FFT_H_ */
