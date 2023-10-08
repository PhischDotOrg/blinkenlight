/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <dsp/Sine.hpp>
#include <dsp/SinCosLut.cpp>

#include <stdint.h>

/*******************************************************************************
 *
 ******************************************************************************/
namespace dsp {

class SineTest : public ::testing::Test {
protected:
    static const unsigned SAMPLE_RATE = 44100;

    typedef int16_t sample_t;
    typedef SineT<sample_t, SAMPLE_RATE>    Sine;

    int16_t get_sample(const unsigned p_freqInHz, const unsigned p_sampleRateInHz, const unsigned p_sample) const
    {
        const static int16_t half = 32767;
        const static double PI = 4 * atan(1);

        double phase = (double) (p_sample * p_freqInHz) / (double) p_sampleRateInHz;
        double d = half * ::sin(2 * PI * phase);

        assert(d > (-1 * half));
        assert(d < half);

        return round(d);
    }

public:
    SineTest(void) {
    };

    ~SineTest() {
    }
};

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(SineTest, DISABLED_Sine_440Hz) {
    const unsigned freq = 440;

    for (unsigned i = 0; i < 10; i++)
    {
        const sample_t expected = get_sample(freq, SAMPLE_RATE, i);

        const sample_t actual = Sine::get_sample(freq, i);

        const double error = 0.05;

        EXPECT_GE(abs(expected) * (1.0 + error), abs(actual)) << "i = " << i << ", expected = " << expected;
        EXPECT_LE(abs(expected) * (1.0 - error), abs(actual)) << "i = " << i << ", expected = " << expected;
    }
}

} /* namespace dsp */
