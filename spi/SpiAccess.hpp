/*-
 * $Copyright$
-*/

#ifndef _SPI_ACCESS_HPP_31fc33e8_6d4f_4052_9fb8_072302deb083
#define _SPI_ACCESS_HPP_31fc33e8_6d4f_4052_9fb8_072302deb083

#include <spi/Spi.hpp>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>

#if defined(DEBUG_BUILD) && defined(GMOCK_FOUND)
#include <gmock/gmock.h>
#endif /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */

/*******************************************************************************
 * 
 ******************************************************************************/
#if !defined(SPI_ENV)
#define SPI_ENV Undefined
#endif

#include "spi/SpiAccessViaGpio.hpp"
#include "spi/SpiAccessViaI2c.hpp"
#include "spi/SpiAccessViaSTM32F4.hpp"

namespace spi {

typedef enum SpiAccessImpl_e {
    Gpio,
    GTest,
    I2c,
    STM32F4,
    Undefined,
} SpiAccessImpl_t;

template<SpiAccessImpl_t> struct SpiAccessChoice;

class SpiAccessMock;

template<> struct SpiAccessChoice<Gpio> {
    typedef SpiAccessViaGpio m_type;
};

template<> struct SpiAccessChoice<GTest> {
    typedef SpiAccessMock m_type;
};

template<> struct SpiAccessChoice<I2c> {
    typedef SpiAccessViaI2cT<i2c::I2cDevice> m_type;
};

template<> struct SpiAccessChoice<STM32F4> {
    typedef SpiAccessViaSTM32F4<true, dma::DmaChannel> m_type;
};

template<> struct SpiAccessChoice<Undefined> {
    typedef void m_type;
};

struct SpiAccessT {
    typedef SpiAccessChoice<SPI_ENV>::m_type m_type;
};

typedef SpiAccessT::m_type SpiAccess;

/*******************************************************************************
 *
 ******************************************************************************/
template<bool doMultiByteTransferT, typename AccessT> class ShiftHelperT;

template<typename AccessT>
class ShiftHelperT<false, AccessT> {
public:
    static ssize_t shift(const AccessT * const p_access, uint32_t p_bits, const uint8_t * const p_tx /* = NULL */, uint8_t * const p_rx /* = NULL */, const spi::Mode p_mode) {
        int rc = -1;

        assert(p_bits > 0);

        uint8_t bits, rx = 0, tx;
        uint32_t remain = p_bits, idx = 0;
        do {
            if (remain < 8) {
                bits = remain;
            } else {
                bits = 8;
            }

            if (p_tx != NULL) {
                tx = p_tx[idx];
            } else {
                tx = 0xff;
            }

            rc = p_access->shift(bits, &rx, tx, p_mode);
            if (rc != 0)
                break;

            if (p_rx != NULL)
                p_rx[idx] = rx;

            remain -= bits;
            idx++;
        } while(remain > 0);

        return (p_bits - remain);
    }
};

/*******************************************************************************
 *
 ******************************************************************************/
template<typename AccessT>
class ShiftHelperT<true, AccessT> {
public:
    static ssize_t shift(AccessT * const p_access, const uint32_t p_bits, const uint8_t * const p_tx /* = NULL */, uint8_t * const p_rx /* = NULL */, const spi::Mode p_mode) {
        ssize_t rc = p_access->shift(p_bits, p_rx, p_tx, p_mode);
        if (rc) {
            rc = -1;
        } else {
            rc = p_bits;
        }
        return (rc);
    }
};

} /* namespace spi */

#endif /* _SPI_ACCESS_HPP_31fc33e8_6d4f_4052_9fb8_072302deb083 */
