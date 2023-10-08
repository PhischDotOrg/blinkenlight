/*-
 * $Copyright$
-*/

#ifndef _SIN_COS_HPP_e89c9797_795d_435d_bc4b_5a4334bd902d
#define _SIN_COS_HPP_e89c9797_795d_435d_bc4b_5a4334bd902d

#include <stdint.h>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T, bool useMathLib_t = true> class SinCosT;

/*******************************************************************************
 *
 ******************************************************************************/
template<>
class SinCosT<int8_t, false> {
private:
    static const int8_t m_lut[64];

    typedef SinCosT<int8_t, false> THIS;

public:
    SinCosT(void) {
    }

    ~SinCosT() {
    }

    static int8_t sin(const int8_t p_phase) {
        const int8_t quadrantLen = sizeof(m_lut) / sizeof(m_lut[0]);
        const int8_t offset = p_phase % quadrantLen;

        int8_t value;
        if (offset > 0) {
            if (p_phase < quadrantLen) {
                value = THIS::m_lut[0 + offset];
            } else /* if (offset >= quadrantLen) */ {
                value = THIS::m_lut[(quadrantLen - offset) % quadrantLen];
            }
        } else if (offset < 0) {
            if (p_phase > (-1 * quadrantLen)) {
                value = 0 - THIS::m_lut[0 - offset];
            } else {
                value = 0 - THIS::m_lut[(quadrantLen + offset) % quadrantLen];
            }
        } else /* (offset == 0) */ {
            if ((p_phase == 0) || (p_phase == -128)) {
                value = THIS::m_lut[offset];
            } else if (p_phase == quadrantLen) {
                value = THIS::m_lut[quadrantLen - 1];
            } else if (p_phase == (-1 * quadrantLen)) {
                value = -1 * THIS::m_lut[quadrantLen - 1];
            } else {
                value = 0;
            }
        }

        return value;        
    };

    static int8_t cos(const int8_t p_phase) {
        return THIS::sin(p_phase + THIS::PI);
    };

    static const int8_t PI;
    static const int8_t AMPLITUDE;
};

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
class SinCosT<T, false> {
private:
    typedef SinCosT<T, false> THIS;

public:
    SinCosT(void);
    ~SinCosT();

    static T sin(const T p_phase);
    static T cos(const T p_phase);
    
    static constexpr T PI = 3.14159265359;
    static constexpr T AMPLITUDE = 1.0;
};

} /* namespace dsp */

#include <dsp/SinCos.cpp>

#endif /* _SIN_COS_HPP_e89c9797_795d_435d_bc4b_5a4334bd902d */
