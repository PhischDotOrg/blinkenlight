/*-
 * $Copyright$
-*/

#ifndef _DSP_SINE_CPP_9af73fc6_72bd_4d44_858a_31eccbc9d645
#define _DSP_SINE_CPP_9af73fc6_72bd_4d44_858a_31eccbc9d645

#include <dsp/Sine.hpp>

#include <dsp/SinCos.hpp>

#include <math.h>
#include <stdio.h>

#include <stdint.h>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T, const int t_sampleRate>
SineT<T, t_sampleRate>::SineT(void) {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T, const int t_sampleRate>
SineT<T, t_sampleRate>::~SineT() {

}

#if defined(USE_FLOAT)
/*******************************************************************************
 *
 ******************************************************************************/
template<typename T, const int t_sampleRate>
T
SineT<T, t_sampleRate>::get_sample(const unsigned p_freqInHz, const int p_sample) {
    static const int16_t maxAmplitude = (1 << ((sizeof(T) * 8) - 1)) - 1;

    const double pi = 4 * atan(1);
    const double phase = 2 * pi * p_freqInHz * p_sample;

    double sample = maxAmplitude * ::sin(phase / t_sampleRate);

    return round(sample);
}
#elif defined(USE_LIBM)
template<typename T, const int t_sampleRate>
T
SineT<T, t_sampleRate>::get_sample(const unsigned p_freqInHz, const int p_sample) {
    typedef SinCosT<int16_t, true> SinCos_t;

    const int16_t phase = ((256 * p_freqInHz * p_sample)) / t_sampleRate;
    return SinCos_t::sin(phase);
}
#else
template<typename T, const int t_sampleRate>
T
SineT<T, t_sampleRate>::get_sample(const unsigned p_freqInHz, const int p_sample) {
    typedef int8_t SinCosValue_t;
    typedef SinCosT<SinCosValue_t, false> SinCos_t;

    const int8_t phase = ((256 * p_freqInHz * p_sample)) / t_sampleRate;

    /*
     * Max. Amplitude of Sine implementation when instantiated w/ int8_t is
     * 2^8 - 1. Because we need to return signed 16-Bit samples, we need to
     * multiply the sine value with (2^16 - 1)/(2^8 - 1) which is roughly the
     * same as 2^16/2^8 => 2^8 => 128.
     */
    return 128 * SinCos_t::sin(phase);
}
#endif /* ifdef (USE_FLOAT) */

} /* namespace dsp */

#endif /* _DSP_SINE_CPP_9af73fc6_72bd_4d44_858a_31eccbc9d645 */
