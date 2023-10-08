/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>
#include <dsp/Complex.hpp>
#include <dsp/ConstantQ.hpp>

#include <stdint.h>
#include <math.h>

namespace dsp {
    
/*******************************************************************************
 *
 ******************************************************************************/
class ConstantQTest : public ::testing::Test {
public:
    typedef dsp::ComplexT<float> Complex;

    ConstantQTest(void) : m_obj(m_minFreq, m_maxFreq, m_sampleRate), m_samples(m_nSamples) {
        for (unsigned i = 0; i < m_nSamples; i++) {
            double fSpectrum = m_sampleRate / m_nSamples;
            double phase = (2.0f * 4.0f * atan(1)) / m_nSamples;
            double w = m_freq / fSpectrum;

            m_samples[i] = round(64.0 * cos(i * w * phase));
        }
    }

    virtual ~ConstantQTest() {
        
    }

protected:
    static const unsigned m_lengthInLb  = 14;
    static const unsigned m_nSamples    = 1 << m_lengthInLb;
    static const unsigned m_sampleRate  = 1 << 15;

    static const unsigned m_nBands      = 10;

    static const unsigned m_minFreq     = 48;
    static const unsigned m_maxFreq     = m_sampleRate / 2;
    
    ConstantQT<m_nBands>                m_obj;
    std::vector<float>                  m_samples;

    static const unsigned               m_freq = 440;
}; /* class ConstantQTest */

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ConstantQTest, CreateAndDelete) {
    printf("sizeof(m_obj)=%zu\n", sizeof(m_obj));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ConstantQTest, Filter) {
    std::vector<float> output(m_nBands);

    m_obj.filter(m_samples, output);

    for (unsigned i = 0; i < m_nBands; i++) {
        printf("Band %i\t%f\n", i, output[i]);
    }
}

} /* namespace dsp */
