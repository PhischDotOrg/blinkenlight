/*-
 * $Copyright$
-*/

#ifndef __I2C_DEVICE_HPP
#define __I2C_DEVICE_HPP

#include "i2c/I2cTypes.hpp"
#include "i2c/I2cBus.hpp"

#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>

#if defined(DEBUG_BUILD) && defined(GMOCK_FOUND)
#include <gmock/gmock.h>
#endif /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */

namespace i2c {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT>
class DeviceT {
public:
    DeviceT(BusT * const p_bus, const uint8_t p_addr = 0, const uint8_t p_width = 4, const uint32_t p_pageSize = 0, const AddressMode &p_mode = RepeatedStart);
    ~DeviceT();

    ssize_t read(const uint32_t p_addr, uint8_t * const p_buffer, const size_t p_length) const;
    ssize_t write(const uint32_t p_addr, const uint8_t * const p_buffer, const size_t p_length) const;

protected:
    BusT * const    m_bus;
    uint8_t         m_addr;
    uint8_t         m_width;
    uint32_t        m_pageSize;
    AddressMode     m_mode;
};

typedef DeviceT<i2c::I2cBus> I2cDevice;

};

#endif /* !__I2C_DEVICE_HPP */
