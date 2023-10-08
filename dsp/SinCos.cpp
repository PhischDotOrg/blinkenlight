/*-
 * $Copyright$
-*/

#ifndef _DSP_SINCOS_CPP_ad999842_a98a_44fa_8002_18aebe0ef4e9
#define _DSP_SINCOS_CPP_ad999842_a98a_44fa_8002_18aebe0ef4e9

#include <dsp/SinCos.hpp>

#include <stdint.h>
#include <stdio.h>
#include <assert.h>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
T
factorial(unsigned n)
{
    unsigned value = 1;

    for (unsigned idx = n; idx > 1; idx--)
        value *= idx;

    return value;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
static
T
power(T base, unsigned n)
{
    T value = base;

    for (unsigned idx = 1; idx < n; idx++)
        value *= base;

    return value;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
static
T
get_phase_within_base_interval(const T p_phase) {
    T phase = p_phase;

    if (p_phase < (-1 * SinCosT<T, false>::PI)) {
        while (phase < (-1 * SinCosT<T, false>::PI)) {
            phase += 2*SinCosT<T, false>::PI;
        }
    } else if (p_phase > SinCosT<T, false>::PI) {
        while (phase > SinCosT<T, false>::PI) {
            phase -= 2*SinCosT<T, false>::PI;
        }
    }

    assert(phase >= (-1 * SinCosT<T, false>::PI));
    assert(phase <= (SinCosT<T, false>::PI));

    return phase;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
T
SinCosT<T, false>::sin(const T p_phase) {
    T phase = get_phase_within_base_interval(p_phase);
    T s = phase;

    for (unsigned i = 1; i < 6; i++) {
        unsigned n = (2*i) + 1;

        T factor = static_cast<T>(power(phase, n)) / factorial<T>(n);

        if (i % 2) {    // Odd
            s -= factor;
        } else {        // Even
            s += factor;
        }
    }

    return s;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
T
SinCosT<T, false>::cos(const T p_phase) {
    T s = 1;
    T phase = get_phase_within_base_interval(p_phase);

    for (unsigned i = 1; i < 7; i++) {
        unsigned n = (2*i);

        T factor = static_cast<T>(power(phase, n)) / factorial<T>(n);

        if (i % 2) {    // Odd
            s -= factor;
        } else {        // Even
            s += factor;
        }
    }

    return s;
}

} /* namespace dsp */

#endif /* _DSP_SINCOS_CPP_ad999842_a98a_44fa_8002_18aebe0ef4e9 */
