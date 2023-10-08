/*-
 * $Copyright$
-*/

#ifndef __I2C_OPERATION_HPP
#define __I2C_OPERATION_HPP

#include <i2c/I2cBus.hpp>
#include <i2c/I2cDevice.hpp>

#include <stddef.h>
#include <stdint.h>
#include <strings.h>
#include <iostream>

namespace i2c {

template<typename BusT, typename DeviceT>
class TransferT {
private:
    BusT *m_bus;
    DeviceT *m_device;

    std::istream &m_istream;
    std::ostream &m_ostream;

public:
    TransferT(BusT *p_bus, DeviceT *p_device, std::istream &p_istream, std::ostream &p_ostream);

    ssize_t write(off_t p_offset, size_t p_length, const uint8_t * const p_data) const;
    ssize_t read(off_t p_offset, size_t p_length, bool p_binary) const;
    int reset(void) const;
    int scan(void) const;
};

typedef TransferT<i2c::I2cBus, i2c::I2cDevice> Transfer;

};/* namespace i2c */

#if defined(DEBUG_BUILD)
#if defined(GMOCK_FOUND)
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace i2c {

/*******************************************************************************
 *
 ******************************************************************************/
class I2cDeviceMock {
public:
    MOCK_CONST_METHOD3(read, ssize_t(const uint32_t p_addr, uint8_t * const p_buffer, const size_t p_length));
    MOCK_CONST_METHOD3(write, ssize_t(const uint32_t p_addr, const uint8_t * const p_buffer, const size_t p_length));
};

} /* namespace i2c */

#endif /* defined(GMOCK_FOUND) */
#endif /* defined(DEBUG_BUILD) */

#endif /* __I2C_OPERATION_HPP */


