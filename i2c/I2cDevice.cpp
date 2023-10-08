/*-
 * $Copyright$
-*/

#include "i2c/I2cDevice.hpp"

#include <stddef.h>
#include <stdint.h>
#include <stddef.h>

namespace i2c {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT>
DeviceT<BusT>::DeviceT(BusT * const p_bus, const uint8_t p_addr /* = 0 */,
  const uint8_t p_width /* = 4 */, const uint32_t p_pageSize /* = 0 */,
  const AddressMode &p_mode /* = RepeatedStart */) : m_bus(p_bus),
  m_addr(p_addr), m_width(p_width), m_pageSize(p_pageSize), m_mode(p_mode) {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT>
DeviceT<BusT>::~DeviceT() {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT>
ssize_t
DeviceT<BusT>::read(const uint32_t p_addr, uint8_t * const p_buffer,
  const size_t p_length) const {
    int rc = 0;
    size_t len = 0;

    rc = this->m_bus->start(this->m_addr & 0xFE, false);
    if (rc != 0)
        goto out;

    for (int i = this->m_width - 1; i >= 0; i--) {
        rc = this->m_bus->write((p_addr >> (i * 8)) & 0xFF);
        if (rc != 0)
            goto out;
    }

    switch (this->m_mode) {
    case None:
        break;
    case StartStop:
        rc = this->m_bus->stop();
        if (rc != 0)
            goto out;
        /* FALLTHRU */
    case RepeatedStart:
        rc = this->m_bus->start(this->m_addr | 0x01, true);
        break;
    default:
        rc = -1;
        goto out;
    }

    for (unsigned i = 0; i < p_length; i++, len++) {
        rc = this->m_bus->read(&p_buffer[i], i < (p_length - 1));
        if (rc)
            break;
    }

out:
    if (!rc)
        rc = this->m_bus->stop();
    else
        this->m_bus->reset();

    return (len);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT>
ssize_t
DeviceT<BusT>::write(const uint32_t p_addr, const uint8_t * const p_buffer,
  const size_t p_length) const {
    int rc = 0;
    unsigned i;
    size_t len = 0;

    rc = this->m_bus->start(this->m_addr & 0xFE, false);
    if (rc != 0)
        goto out;

    for (int i = this->m_width - 1; i >= 0; i--) {
        rc = this->m_bus->write((p_addr >> (i * 8)) & 0xFF);
        if (rc != 0) {
            goto out;
        }
    }

    switch (this->m_mode) {
    case None:
    case StartStop:
    case RepeatedStart:
        break;
    default:
        rc = -1;
        goto out;
    }

    for (i = 0; i < p_length; i++, len++) {
        rc = this->m_bus->write(p_buffer[i]);
        if (rc)
            break;
    }

out:
    if (!rc)
        rc = this->m_bus->stop();
    else
        this->m_bus->reset();

    return (len);
}

}; /* namespace i2c */

