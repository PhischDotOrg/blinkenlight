/*-
 * $Copyright$
-*/

#ifndef _DSP_SINCOS_LIBM_CPP_b9cf9a1f_841c_4085_bc61_434ebf9a8049
#define _DSP_SINCOS_LIBM_CPP_b9cf9a1f_841c_4085_bc61_434ebf9a8049

#include <dsp/SinCosLibM.hpp>

#include <stdint.h>
#include <math.h>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
//template<> const int8_t SinCosT<int8_t, true>::PI = 64;
//template<> const float SinCosT<float, true>::PI = 4 * ::atanf(1);
//template<> const double SinCosT<double, true>::PI = 4 * ::atan(1);

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
SinCosT<T, true>::SinCosT(void) {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
SinCosT<T, true>::~SinCosT() {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
double
SinCosT<T, true>::phase(const T p_phase) {
    double phase = static_cast<double>(p_phase);
    phase *= 4.0 * atan(1);
    phase /= static_cast<double>(SinCosT<T, true>::PI);
    
    return phase;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
T
SinCosT<T, true>::sin(const T p_phase) {
    return SinCosT<T, true>::AMPLITUDE * ::sin(SinCosT<T, true>::phase(p_phase));
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
T
SinCosT<T, true>::cos(const T p_phase) {
    return SinCosT<T, true>::AMPLITUDE * ::cos(SinCosT<T, true>::phase(p_phase));
}

} /* namespace dsp */

#endif /* _DSP_SINCOS_LIBM_CPP_b9cf9a1f_841c_4085_bc61_434ebf9a8049 */
