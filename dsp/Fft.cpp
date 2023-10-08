/*-
 * $Copyright$
-*/


#ifndef _DSP_FILTER_FFT_CPP_7eb2efbd_1eba_4558_a45a_af48d62da46f
#define _DSP_FILTER_FFT_CPP_7eb2efbd_1eba_4558_a45a_af48d62da46f

#include "Fft.hpp"
#include <dsp/SinCos.hpp>
#include <dsp/BitReversal.hpp>
#include <dsp/SinCos.hpp>

#include <algorithm>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename VectorT, unsigned t_lengthInLb>
void
FftT<VectorT, t_lengthInLb>::calculateFactor(const unsigned k, const unsigned l, ComplexT &p_factor) {
#if defined(USE_BUILTIN_MATH)
    typedef dsp::SinCosT<typename ComplexT::value_type, true> SinCos_t;
#else
    typedef dsp::SinCosT<typename ComplexT::value_type, false> SinCos_t;
#endif
    const typename ComplexT::value_type PI = SinCos_t::PI;

    const unsigned n = 2 << l;
    
    typename ComplexT::value_type phase = -2.0f * PI * ((typename ComplexT::value_type) k) / ((typename ComplexT::value_type) n);

    p_factor = ComplexT(SinCos_t::cos(phase), SinCos_t::sin(phase));
}

/*******************************************************************************
 * Algorithm taken from:
 * 
 * http://de.wikipedia.org/wiki/Schnelle_Fourier-Transformation#Implementierung_als_nichtrekursiver_Algorithmus
 * (retrieved on Jan 24th, 2015)
 * 
 * The Wikipedia article seems to have a bug in that (in this implementation)
 * the getFactor() method should not be called as getFactor(element, 1 << layer),
 * but instead as getFactor(element, 2 << layer).
 ******************************************************************************/
template<typename VectorT, unsigned t_lengthInLb>
void
FftT<VectorT, t_lengthInLb>::applyFft(VectorT &p_vector) {
    ComplexT factor;
    unsigned N = t_lengthInLb;

    /*
     * Step 1: Re-order samples. Samples are p_vector[x] where x := 0..2^n
     * 'x' can be expressed in binary as x := { x_(n-1), x_(n-2), ...,
     * x_1, x_0 }.
     * Sample p_vector[x] must be exchanged w/ p_vector[y] where
     * 'y' is in  binary form: y := { x_0, x_1, ..., x_(n-2), x_(n-1) }.
     */
    for (unsigned idx = (1u << t_lengthInLb) - 1; idx > 1; idx--) {
        unsigned ridx = m_bitReversal.getReverse(idx);
        if (ridx < idx) {
            std::swap(p_vector[idx], p_vector[ridx]);
        }
    }

    for (unsigned layer = 0; layer < N; layer++) {
        unsigned sections = 1u << (N - layer - 1);
        for (unsigned section = 0; section < sections; section++) {
            unsigned elements = 1u << layer;
            for (unsigned element = 0; element < elements; element++) {
                unsigned l = ((1u << (layer + 1)) * section) + element;
                unsigned r = l + (1u << layer);

                ComplexT tmp = m_factors[layer][element] * p_vector[r];

                p_vector[r] = p_vector[l] - tmp;
                p_vector[l] += tmp;
            }
        }
    }
}

} /* namespace dsp */

#endif /* _DSP_FILTER_FFT_CPP_7eb2efbd_1eba_4558_a45a_af48d62da46f */
        