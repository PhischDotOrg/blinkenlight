/*-
 * $Copyright$
-*/

#ifndef _DSP_WINDOW_FUNCTION_HPP_e081398c_43e3_466a_afbe_fd550a4d8389
#define _DSP_WINDOW_FUNCTION_HPP_e081398c_43e3_466a_afbe_fd550a4d8389

#include <uart/UartDevice.hpp>
extern uart::UartDevice g_uart;

#if defined(USE_BUILTIN_MATH)
#include <dsp/SinCosLibM.hpp>

typedef dsp::SinCosT<float, true> Math_t;

template<> const float dsp::SinCosT<float, true>::PI = 3.14159265359f;
template<> const float dsp::SinCosT<float, true>::AMPLITUDE = 1.0f;

#else
#include <dsp/SinCos.hpp>
typedef dsp::SinCosT<float, false> Math_t;
#endif

namespace dsp {
    namespace WindowFunction {
        
/*******************************************************************************
 *
 ******************************************************************************/
template<typename InputTypeT, typename OutputTypeT, const unsigned t_nSamples>
OutputTypeT
CosineT(const InputTypeT &p_value, const unsigned p_idx) {
    return p_value * Math_t::sin((Math_t::PI * p_idx) / (static_cast<float>(t_nSamples) - 1.0f));
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename OutputTypeT, const unsigned t_nSamples>
OutputTypeT
CosineFactorT(const unsigned p_idx) {
    return Math_t::sin((Math_t::PI * p_idx) / (static_cast<float>(t_nSamples) - 1.0f));
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename InputTypeT, typename OutputTypeT, const unsigned t_nSamples>
OutputTypeT
HannT(const InputTypeT &p_value, const unsigned p_idx) {
    float factor = 0.5f * (1 - Math_t::cos((2*Math_t::PI*p_idx) / (static_cast<float>(t_nSamples) - 1.0f)));
    
    return p_value * factor;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename OutputTypeT, const unsigned t_nSamples>
OutputTypeT
HannFactorT(const unsigned p_idx) {
    return 0.5f * (1 - Math_t::cos((2*Math_t::PI*p_idx) / (static_cast<float>(t_nSamples) - 1.0f)));
}

    } /* namespace WindowFunction */
} /* namespace dsp */

#endif /* _DSP_WINDOW_FUNCTION_HPP_e081398c_43e3_466a_afbe_fd550a4d8389 */
