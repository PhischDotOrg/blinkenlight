/*-
 * $Copyright$
-*/

#ifndef _DSP_FFT_HPP_17a03428_131b_4d9e_98af_a4d024d07434
#define _DSP_FFT_HPP_17a03428_131b_4d9e_98af_a4d024d07434

#include <dsp/BitReversal.hpp>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename VectorT, unsigned t_lengthInLb>
class FftT {
    typedef typename VectorT::value_type ComplexT;
private:
    void calculateFactor(const unsigned k, const unsigned l, ComplexT &p_factor);

    BitReversalT<t_lengthInLb>  m_bitReversal;
    ComplexT                    m_factors[t_lengthInLb][1 << t_lengthInLb];

public:
    FftT(void) {
        for (unsigned l = 0; l < t_lengthInLb; l++) {
            for (unsigned k = 0; k < (1 << t_lengthInLb); k++) {
                calculateFactor(k, l, m_factors[l][k]);
            }
        }
    };

    ~FftT() {
    };
    
    void applyFft(VectorT &p_vector);
};

} /* namespace dsp */

#include "Fft.cpp"

#endif /* _DSP_FFT_HPP_17a03428_131b_4d9e_98af_a4d024d07434 */
