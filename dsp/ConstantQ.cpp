/*-
 * $Copyright$
-*/
#ifndef _DSP_CONSTANTQ_CPP_569a9bd1_4eea_4a12_b29d_399261c4387c
#define _DSP_CONSTANTQ_CPP_569a9bd1_4eea_4a12_b29d_399261c4387c

#include "ConstantQ.hpp"

#if defined(DEBUG_CONSTANT_Q)
#include <uart/UartDevice.hpp>
extern uart::UartDevice g_uart;
#endif /* defined(DEBUG_CONSTANT_Q) */

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
template<unsigned nBands, typename ComplexT>
ConstantQT<nBands, ComplexT>::ConstantQT(const unsigned p_freqMin, const unsigned p_freqMax, const unsigned p_freqSampling) {
    float       bins;               // Number of bands per octave
    float       frequencies[nBands];// Center frequencies of filter bands
    unsigned    nTotalFactors;      // Required minimum size of array w/ window function values.
    float       constantQ;          // Delta factor ("Q") between filter bands
    float       PI = 4 * atan(static_cast<float>(1));

    bins = nBands / ::log2(static_cast<float>(p_freqMax) / static_cast<float>(p_freqMin));

    constantQ = 1.0f / (::pow(2, (1.0 / bins)) - 1.0f);

    nTotalFactors = 0;
    this->m_BandFilterOffset[0] = 0;

    for (unsigned k = 0; k < nBands; k++) {
        frequencies[k] = p_freqMin * ::pow(2, k / bins);
        m_nBandSamples[k] = ::round(constantQ * (static_cast<float>(p_freqSampling) / static_cast<float>(frequencies[k])));

        nTotalFactors += m_nBandSamples[k];

        if (k > 0) {
            m_BandFilterOffset[k] = m_BandFilterOffset[k - 1] + m_nBandSamples[k - 1];
        }

#if defined(DEBUG_CONSTANT_Q)
        g_uart.printf("Band %d => Center @ %d Hz, %d Samples\r\n", k, ((unsigned) (frequencies[k] * 1000) + 500) / 1000, m_nBandSamples[k]);
#endif /* defined(DEBUG_CONSTANT_Q) */
    }

    assert(nTotalFactors == (m_BandFilterOffset[nBands - 1] + m_nBandSamples[nBands - 1]));
    assert(m_filterFactorsSize >= nTotalFactors);

    for (unsigned k = 0; k < nBands; k++) {
        unsigned offs = this->m_BandFilterOffset[k];
        assert(nTotalFactors > (offs + (m_nBandSamples[k] - 1)));

        for (unsigned idx = 0; idx < m_nBandSamples[k]; idx++) {
            float windowFactor = getWindowFactor(PI, idx, m_nBandSamples[k]);
            float phase = (2.0f * PI * constantQ) * (static_cast<float>(idx) / static_cast<float>(m_nBandSamples[k]));

            m_filterFactors[offs + idx] = ComplexT(cos(phase), sin(phase));
            m_filterFactors[offs + idx] *= windowFactor;
        }
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
template<unsigned nBands, typename ComplexT>
ConstantQT<nBands, ComplexT>::~ConstantQT() {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<unsigned nBands, typename ComplexT>
float
ConstantQT<nBands, ComplexT>::getWindowFactor(const float p_PI, const unsigned p_idx, const unsigned p_width) {
    const float alpha = 25.0/46.0;
    const float phase = (2 * p_PI * p_idx) / (p_width - 1);
    const float factor = alpha - (1 - alpha) * ::cos(phase);

    assert(0 <= factor);
    assert(1 >= factor);

    return factor;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<unsigned nBands, typename ComplexT>
template<typename InputVectorT, typename OutputVectorT>
void
ConstantQT<nBands, ComplexT>::filter(const InputVectorT &p_input, OutputVectorT &p_output) const {
    assert(p_input.size() >= this->m_nBandSamples[0]);
    assert(p_output.size() >= nBands);

    for (unsigned k = 0; k < nBands; k++) {
        ComplexT value(0);

        const unsigned offs = this->m_BandFilterOffset[k];

        for (unsigned n = 0; n < this->m_nBandSamples[k]; n++) {
            float sample = p_input[n] - 128.0f;
            ComplexT tmp = this->m_filterFactors[offs + n];
            tmp *= sample;

            value += tmp;
        }

        p_output[k] = value.abs2() / static_cast<float>(this->m_nBandSamples[k] * this->m_nBandSamples[k]);
    }
}

} /* namespace dsp */

#endif /* _DSP_CONSTANTQ_CPP_569a9bd1_4eea_4a12_b29d_399261c4387c */

