/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <dsp/SinCos.hpp>
#include <dsp/SinCosLut.cpp>

namespace dsp {

const int8_t SinCosT<int8_t, false>::PI = sizeof(m_lut) / sizeof(m_lut[0]);
const int8_t SinCosT<int8_t, false>::AMPLITUDE = 127;    

static double c_precision = 1.0/1000.0;

/*******************************************************************************
 *
 ******************************************************************************/
TEST(SinCosTest, SinNoMathLib8) {
    const double PI = 4 * atan(1);

    typedef SinCosT<int8_t, false> SinCos_t;

    for (int i = -1 * SinCos_t::PI; i < SinCos_t::PI; i++) {
        int expected = round(SinCos_t::AMPLITUDE * ::sin((i * PI) / (2*SinCos_t::PI)));
        int8_t actual = SinCos_t::sin(i);

        if (((i % 256) == (-2*SinCos_t::PI)) || ((i % 256) == 0))
            EXPECT_EQ(0, actual) << "zero-phase @ " << i;
        if ((i % 256) == (-1*SinCos_t::PI))
            EXPECT_EQ(-1 * SinCos_t::AMPLITUDE, actual) << "neg. max. @ " << i;
        if ((i % 256) == (1*SinCos_t::PI))
            EXPECT_EQ(SinCos_t::AMPLITUDE, actual) << "pos. max. @ " << i;

        EXPECT_EQ(expected, actual) << "phase = " << i;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST(SinCosTest, CosNoMathLib8) {
    const double PI = 4 * atan(1);

    typedef SinCosT<int8_t, false> SinCos_t;

    for (int i = -1 * SinCos_t::PI; i < SinCos_t::PI; i++) {
        int expected = round(SinCos_t::AMPLITUDE * ::cos((i * PI) / (2*SinCos_t::PI)));
        int8_t actual = SinCos_t::cos(i);

        if (((i % 256) == (-1*SinCos_t::PI) || ((i % 256) == (1*SinCos_t::PI))))
            EXPECT_EQ(0, actual) << "zero-phase = " << i;
        if ((i % 256) == (-2*SinCos_t::PI))
            EXPECT_EQ(-1 * SinCos_t::AMPLITUDE, actual) << "neg. max. @ " << i;
        if ((i % 256) == 0)
            EXPECT_EQ(SinCos_t::AMPLITUDE, actual) << "pos. max. @ " << i;

        EXPECT_EQ(expected, actual) << "phase = " << i;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST(SinCosTest, SinNoMathLibFloat) {
    typedef SinCosT<float, false> SinCos_t;

    const float factor = 281.0;
    for (float i = -1.0 * factor * SinCos_t::PI; i <= 1.0 * factor * SinCos_t::PI; i += 0.1) {
        float expected = ::sin(i);
        float actual = SinCos_t::sin(i);

        EXPECT_NEAR(expected, actual, c_precision) << "phase = " << i;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST(SinCosTest, CosNoMathLibFloat) {
    typedef SinCosT<float, false> SinCos_t;

    const float factor = 325.0;

    for (float i = -1.0 * factor * SinCos_t::PI; i <= 1.0 * factor * SinCos_t::PI; i += 0.1) {
        float expected = ::cos(i);
        float actual = SinCos_t::cos(i);

        EXPECT_NEAR(expected, actual, c_precision) << "phase = " << i;
    }
}

} /* namespace dsp */
