/*-
 * $Copyright$
-*/

#ifndef _I2C_BUS_VIA_GPIO_HPP_df171367_c5e1_4613_b4b7_5f5769d3edd8
#define _I2C_BUS_VIA_GPIO_HPP_df171367_c5e1_4613_b4b7_5f5769d3edd8

#include <stdint.h>

#include <gpio/GpioPin.hpp>

namespace i2c {

template <typename PinT>
class I2cBusViaGpioT {
    static const int m_delay = 100;

private:
    PinT * const m_scl;
    PinT * const m_sda;

    int set(const PinT * const p_pin, const typename PinT::mode_t p_value) const;

    bool is_idle(void) const;

    int start_condition(void) const;

    int tx_bit(const bool p_bit) const;
    int rx_bit(bool * const p_bit) const;

public:
    I2cBusViaGpioT(PinT * const p_scl, PinT * const p_sda);
    ~I2cBusViaGpioT();

    int start(const uint8_t p_addr, const bool p_repeated) const;
    int stop(void) const;
    int read(uint8_t * const p_data, const bool p_ack) const;
    int write(const uint8_t p_data) const;

    int reset(void) const;
}; /* class I2cBusViaGpioT */

}; /* namespace i2c */

#endif /* _I2C_BUS_VIA_GPIO_HPP_df171367_c5e1_4613_b4b7_5f5769d3edd8 */
