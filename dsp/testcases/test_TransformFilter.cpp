/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#define USE_BUILTIN_MATH

#include <dsp/TransformFilter.hpp>
#include <dsp/Complex.hpp>
#include <dstruct/StaticVector.hpp>
#include <dsp/WindowFunction.hpp>

#include <algorithm>

namespace dsp {

    namespace Filter {

/*******************************************************************************
 *
 ******************************************************************************/
class TransformFilterTest : public ::testing::Test {
public:
    typedef uint16_t sample_t;
    typedef dsp::ComplexT<float> complex_t;

    static const unsigned m_nSamples = 8192;
    static constexpr double m_precision = 2.0/100.0;

    static const unsigned m_bitWidth = sizeof(sample_t) * 8;
    static const unsigned m_maxUnsigned;
    static const unsigned m_maxSigned = (1 << (m_bitWidth - 1)) + ((1 << (m_bitWidth - 1)) - 1);

    void SetUp() {
        for (unsigned i = 0; i < m_nSamples; i++) {
            m_realSamples[i] = m_maxSigned + (m_maxSigned * sin(i));
            ASSERT_GE(this->m_maxUnsigned, m_realSamples[i]) << "i=" << i;

            m_complexSamples[i] = complex_t(i, i);
        }
    }

    virtual ~TransformFilterTest(void) {

    }

protected:
    dstruct::StaticVectorT<sample_t, m_nSamples> m_realSamples;
    dstruct::StaticVectorT<complex_t, m_nSamples> m_complexSamples;
};

 const unsigned TransformFilterTest::m_maxUnsigned = (1 << m_bitWidth) + ((1 << m_bitWidth) - 1);
 
/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(TransformFilterTest, CreateAndDelete) {
    
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(TransformFilterTest, TemporarilyTestPiConstantHere) {
#if defined(USE_BUILTIN_MATH)
    typedef dsp::SinCosT<float, true> Math_t;
#else
    typedef dsp::SinCosT<float, false> Math_t;
#endif /* defined(USE_BUILTIN_MATH) */

    EXPECT_FLOAT_EQ(Math_t::PI, 4 * atanf(1));
}

/*******************************************************************************
 *
 ******************************************************************************/
static TransformFilterTest::complex_t WindowFunctionCosine(const TransformFilterTest::sample_t &p_rawSample, const unsigned p_idx) {
    return dsp::WindowFunction::CosineT<TransformFilterTest::sample_t, TransformFilterTest::complex_t, TransformFilterTest::m_nSamples>(p_rawSample, p_idx);
}

TEST_F(TransformFilterTest, FilterRealToComplexWindowFunctionCosine) {
    dstruct::StaticVectorT<TransformFilterTest::complex_t, m_nSamples> fftFrame;

    dsp::Filter::transform2(m_realSamples.begin(), m_realSamples.end(), fftFrame.begin(), WindowFunctionCosine);

    for (unsigned i = 0; i < m_nSamples; i++) {
        double factor = sin((4.0 * atan(1) * i) / (m_nSamples - 1));

        TransformFilterTest::complex_t expected(m_realSamples[i] * factor);

        ASSERT_NEAR(expected.real(), fftFrame[i].real(), m_precision) << "for i=" << i << ", factor=" << factor;
        ASSERT_NEAR(expected.imag(), fftFrame[i].imag(), m_precision) << "for i=" << i << ", factor=" << factor;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
static TransformFilterTest::complex_t WindowFunctionHann(const TransformFilterTest::sample_t &p_rawSample, const unsigned p_idx) {
    return dsp::WindowFunction::HannT<const TransformFilterTest::sample_t, TransformFilterTest::complex_t, TransformFilterTest::m_nSamples>(p_rawSample, p_idx);
}

TEST_F(TransformFilterTest, FilterRealToComplexWindowFunctionHanning) {
    dstruct::StaticVectorT<complex_t, m_nSamples> fftFrame;

    dsp::Filter::transform2(m_realSamples.begin(), m_realSamples.end(), fftFrame.begin(), WindowFunctionHann);

    for (unsigned i = 0; i < m_nSamples; i++) {
        double factor = 0.5 * (1.0 - cos((2*4*atan(1)*i)/(m_nSamples -1)));

        complex_t expected(m_realSamples[i] * factor);

        ASSERT_NEAR(expected.real(), fftFrame[i].real(), m_precision) << "for i=" << i << ", factor=" << factor;
        ASSERT_NEAR(expected.imag(), fftFrame[i].imag(), m_precision) << "for i=" << i << ", factor=" << factor;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
static TransformFilterTest::complex_t
SquaredNormFunction(const TransformFilterTest::complex_t &p_sample) {
    return (p_sample.real() * p_sample.real()) + (p_sample.imag() * p_sample.imag());
}

TEST_F(TransformFilterTest, ForEachSquaredNorm) {
    dsp::Filter::for_each(m_complexSamples.begin(), m_complexSamples.end(), SquaredNormFunction);

    for (unsigned i = 0; i < m_nSamples; i++) {
        complex_t::value_type expected = (i * i) + (i * i);

        ASSERT_NEAR(expected, m_complexSamples[i].real(), m_precision) << "for i=" << i;
        ASSERT_NEAR(0, m_complexSamples[i].imag(), m_precision) << "for i=" << i;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
    } /* namespace Filter */
} /* namespace dsp */
