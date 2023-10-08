/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <dsp/FilterChain.hpp>

#include <dsp/Complex.hpp>
#include <dstruct/StaticVector.hpp>

/* Required for FFT */
#include <dsp/Fft.hpp>
#include <dsp/BitReversal.cpp>

/*******************************************************************************
 *
 ******************************************************************************/
class FilterChainTest : public ::testing::Test {
protected:
    static const unsigned nSamplesInLb = 9;
    static const unsigned nSamples = 1 << nSamplesInLb;
    static const unsigned nDisplayBars = 10;
    static const unsigned cSamplingRate = 1 << 15;

    typedef dsp::ComplexT<float>                            Complex_t;
    typedef dstruct::StaticVectorT<uint16_t, nSamples>      InputBuffer_t;
    typedef dstruct::StaticVectorT<Complex_t, nSamples>     FftBuffer_t;
    typedef dsp::FftT<FftBuffer_t, nSamplesInLb>            FftObject_t;
    typedef dstruct::StaticVectorT<float, nSamples / 2>     AmplitudesBuffer_t;
    typedef dstruct::StaticVectorT<float, nDisplayBars>     OutputBuffer_t;

    typedef FilterChainT<FftObject_t, FftBuffer_t, AmplitudesBuffer_t>   FilterChain_t;

    FilterChain_t * m_obj;
    FftObject_t     m_fftObject;
    InputBuffer_t   m_input;
    OutputBuffer_t  m_output;

    void generateSamples(const unsigned p_frequency) {
        printf("%s(p_frequency=%i Hz)\n", __func__, p_frequency);

        unsigned idx = 0;
        for (InputBuffer_t::iterator i = m_input.begin(); i != m_input.end(); i++, idx++) {
            *i = generateSingleSample(idx, p_frequency);
        }
    }
    
private:
    static
    InputBuffer_t::value_type
    generateSingleSample(const unsigned p_idx, const unsigned p_frequency) {
        static const double PI = 4 * atan(1);

        const unsigned amplitude = 100;
        const unsigned offset = 128;

        const double spectrum = static_cast<double>(cSamplingRate) / static_cast<double>(nSamples);
        const double phase = (2 * PI) / static_cast<double>(nSamples);
        const double w = static_cast<double>(p_frequency) / static_cast<double>(spectrum);

        const double value = round(offset + (amplitude * cos(p_idx * w * phase)));
        
        return static_cast<InputBuffer_t::value_type>(value);
    }

public:
    FilterChainTest(void) : m_obj(NULL) {
        m_obj = new FilterChain_t(m_fftObject);
        printf("Sampling Rate %i Hz, nSamples = %i => Spektrum = %i Hz\n", cSamplingRate, nSamples, cSamplingRate / nSamples);
        for (unsigned i = 0; i < nDisplayBars; i++) {
            m_output[i] = 0;
        }
    }
    
    virtual ~FilterChainTest() {
        for (unsigned i = 0; i < nDisplayBars; i++) {
            printf("Bar %i = %f\n", i, m_output[i]);
        }
        
        delete m_obj;
    }
};

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(FilterChainTest, CreateAndDelete) {
    printf("nSamplesInLb=%u, nSamples=%u, nDisplayBars=%u\n", nSamplesInLb, nSamples, nDisplayBars);
    printf("sizeof(Complex_t)=%zu Bytes\n", sizeof(Complex_t));
    printf("sizeof(InputBuffer_t)=%zu Bytes\n", sizeof(InputBuffer_t));
    printf("sizeof(FftBuffer_t)=%zu Bytes\n", sizeof(FftBuffer_t));
    printf("sizeof(FftObject_t)=%zu Bytes\n", sizeof(FftObject_t));
    printf("sizeof(AmplitudesBuffer_t)=%zu Bytes\n", sizeof(AmplitudesBuffer_t));
    printf("sizeof(OutputBuffer_t)=%zu Bytes\n", sizeof(OutputBuffer_t));
    printf("sizeof(FilterChain_t)=%zu Bytes\n", sizeof(FilterChain_t));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(FilterChainTest, Filter65HzAt32kHzSamplingRate) {
    this->generateSamples(65);

    m_obj->filter(m_input, m_output);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(FilterChainTest, Filter110HzAt32kHzSamplingRate) {
    this->generateSamples(110);

    m_obj->filter(m_input, m_output);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(FilterChainTest, Filter220HzAt32kHzSamplingRate) {
    this->generateSamples(220);

    m_obj->filter(m_input, m_output);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(FilterChainTest, Filter440HzAt32kHzSamplingRate) {
    this->generateSamples(440);

    m_obj->filter(m_input, m_output);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(FilterChainTest, Filter880HzAt32kHzSamplingRate) {
    this->generateSamples(880);

    m_obj->filter(m_input, m_output);
}
