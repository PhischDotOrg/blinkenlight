/*-
 * $Copyright$
-*/
#ifndef _DSP_CONSTANTQ_HPP_49e1fac3_2d9a_4135_9888_36773484bd59
#define _DSP_CONSTANTQ_HPP_49e1fac3_2d9a_4135_9888_36773484bd59

#include <dsp/Complex.hpp>
#include <dstruct/StaticVector.hpp>

#include <cmath>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
template<unsigned nBands, typename ComplexT = dsp::ComplexT<float> >
class ConstantQT {
protected:
    unsigned        m_nBandSamples[nBands];         // Required samples per frequency band
    unsigned        m_BandFilterOffset[nBands];     // Offset of filter factors within array of all filter factors.

    /* Array with pre-calculated filter window function values */
    static const unsigned m_filterFactorsSize = 10 * 1024;
    ComplexT        m_filterFactors[m_filterFactorsSize];

    static float
    getWindowFactor(const float p_PI, const unsigned p_idx, const unsigned p_width);

public:
    ConstantQT(const unsigned p_freqMin, const unsigned p_freqMax, const unsigned p_freqSampling);
    ~ConstantQT();

    template<typename InputVectorT, typename OutputVectorT>
    void
    filter(const InputVectorT &p_input, OutputVectorT &p_output) const;
};

} /* namespace dsp */

#include "ConstantQ.cpp"

#endif /* _DSP_CONSTANTQ_HPP_49e1fac3_2d9a_4135_9888_36773484bd59 */
