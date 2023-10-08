/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <dsp/BitReversal.hpp>

#include <stdint.h>

namespace dsp {

class BitReversalTest : public ::testing::Test {
protected:
    template<typename BitReversalT, typename T>
    void
    checkBitReversal(const BitReversalT &p_obj, const T * const p_lut, const size_t p_length) const {
        for (unsigned idx = 0; idx < p_length; idx++) {
            unsigned ridx = p_obj.getReverse(idx);
            EXPECT_EQ(p_lut[idx], ridx) << "when idx=" << idx;
        }
    }

public:
    BitReversalTest(void) {
        
    }
    
    virtual ~BitReversalTest() {
        
    }
};

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(BitReversalTest, ThreeBitPattern) {
    const unsigned nBits = 3;
    static const uint8_t lut[(1 << nBits)] = {
        0x00,   0x04,   0x02,   0x06,
        0x01,   0x05,   0x03,   0x07
    };

    checkBitReversal(BitReversalT<nBits>(), lut, sizeof(lut) / sizeof(lut[0]));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(BitReversalTest, FourBitPattern) {
    const unsigned nBits = 4;
    static const uint8_t lut[(1 << nBits)] = {
        0x00,   0x08,   0x04,   0x0C,
        0x02,   0x0A,   0x06,   0x0E,
        0x01,   0x09,   0x05,   0x0D,
        0x03,   0x0B,   0x07,   0x0F
    };

    checkBitReversal(BitReversalT<nBits>(), lut, sizeof(lut) / sizeof(lut[0]));
}

} /* namespace dsp */
