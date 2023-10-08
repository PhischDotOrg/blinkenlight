/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <dsp/SinCosLibM.hpp>

#include <math.h>
#include <stdint.h>


namespace dsp {
    
template<> const int8_t SinCosT<int8_t, true>::PI = 127;
template<> const int8_t SinCosT<int8_t, true>::AMPLITUDE = 127;

template<> const double SinCosT<double, true>::PI = 4 * ::atan(1);
template<> const double SinCosT<double, true>::AMPLITUDE = 1.0;

template<> const float SinCosT<float, true>::PI = 4 * ::atanf(1);
template<> const float SinCosT<float, true>::AMPLITUDE = 1.0f;

static double c_precision = 1.0/10000.0;

/*******************************************************************************
 *
 ******************************************************************************/
TEST(SinCosTest, SinWithMathLib8) {
    const double PI = 4 * atan(1);

    typedef SinCosT<int8_t, true> SinCos_t;

    for (int i = -1 * SinCos_t::PI; i <= 1 * SinCos_t::PI; i++) {
        int expected = SinCosT<int8_t, true>::AMPLITUDE * ::sin(PI * (static_cast<double>(i) / SinCosT<int8_t, true>::PI));

        int8_t actual = SinCos_t::sin(i);

        if (((i % (2 * SinCos_t::PI)) == 0) || ((i % (2 * SinCos_t::PI)) == SinCos_t::PI))
            EXPECT_EQ(0, actual) << "zero-phase @ " << i;

        EXPECT_NEAR(expected, actual, 1) << "phase = " << i;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST(SinCosTest, CosWithMathLib8) {
    const double PI = 4 * atan(1);

    typedef SinCosT<int8_t, true> SinCos_t;

    for (int i = -1 * SinCos_t::PI; i <= 1 * SinCos_t::PI; i++) {
        int expected = SinCosT<int8_t, true>::AMPLITUDE * ::cos(PI * (static_cast<double>(i) / SinCosT<int8_t, true>::PI));

        int8_t actual = SinCos_t::cos(i);

        EXPECT_EQ(expected, actual) << "phase = " << i;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST(SinCosTest, SinWithMathLibFloat) {
    typedef SinCosT<float, true> SinCos_t;

    for (float i = -2.0 * SinCos_t::PI; i <= 2.0 * SinCos_t::PI; i += 0.1) {
        float expected = ::sin(i);
        float actual = SinCos_t::sin(i);

        EXPECT_NEAR(expected, actual, c_precision) << "phase = " << i;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST(SinCosTest, CosWithMathLibFloat) {
    typedef SinCosT<float, true> SinCos_t;

    for (float i = -2.0 * SinCos_t::PI; i <= 2.0 * SinCos_t::PI; i += 0.1) {
        float expected = ::cos(i);
        float actual = SinCos_t::cos(i);

        EXPECT_NEAR(expected, actual, c_precision) << "phase = " << i;
    }
}

} /* namespace dsp */
