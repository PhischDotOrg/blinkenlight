/*-
 * $Copyright$
-*/

#include <i2c/I2cBusViaGpio.hpp>
#include <gpio/GpioPin.hpp>

#include <assert.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>

namespace i2c {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
I2cBusViaGpioT<PinT>::I2cBusViaGpioT(PinT * const p_scl, PinT * const p_sda)
    : m_scl(p_scl), m_sda(p_sda) {
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
I2cBusViaGpioT<PinT>::~I2cBusViaGpioT() {
}

template<typename PinT>
int
I2cBusViaGpioT<PinT>::set(const PinT * const p_pin, const typename PinT::mode_t p_value) const {
    int rc = -1;
    assert(p_pin != NULL);
    typename PinT::mode_t value;

    usleep(this->m_delay);

    rc = p_pin->set(p_value);
    if (rc)
        goto out;

    usleep(this->m_delay);

    rc = p_pin->get(value);
    if (rc)
        goto out;

    if ((p_value == PinT::HiZ) && (value == PinT::On))
        goto done;

    if (value != p_value) {
        rc = -1;
        goto out;
    }

done:
    rc = 0;
out:
    return rc;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
bool
I2cBusViaGpioT<PinT>::is_idle(void) const {
    int rc = -1;
    bool idle = false;
    typename PinT::mode_t value;

    rc = this->m_scl->get(value);
    if (rc || value != PinT::On)
        goto out;

    rc = this->m_sda->get(value);
    if (rc || value != PinT::On)
        goto out;

    idle = true;

out:
    return (idle);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
int
I2cBusViaGpioT<PinT>::start_condition(void) const {
    int rc = -1;

    rc = this->set(m_sda, PinT::Off);
    if (rc)
        goto out;

    rc = this->set(m_scl, PinT::Off);
    if (rc)
        goto out;

    rc  = 0;
out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
int
I2cBusViaGpioT<PinT>::tx_bit(const bool p_bit) const {
    int rc = -1;
    typename PinT::mode_t value;

    rc = this->set(m_scl, PinT::Off);
    if (rc)
        goto out;

    /*
     * Set pin(s) directly instead of our private method. The latter will read the
     * line back after setting it which won't work if the slave is pulling the
     * clock low.
     */
    rc = this->m_sda->set(p_bit ? PinT::HiZ : PinT::Off);
    if (rc)
        goto out;

    usleep(this->m_delay);

    rc = this->m_scl->set(PinT::HiZ);
    if (rc)
        goto out;

    usleep(this->m_delay);

    do {
      rc = this->m_scl->get(value);
      if (rc)
          goto out;
    } while (value != PinT::On);

    rc = this->m_sda->get(value);
    if (rc)
        goto out;

    if ((p_bit && (value != PinT::On))
      || (!p_bit && (value != PinT::Off))) {
        rc = -1;
        goto out;
    }

    rc = this->set(m_scl, PinT::Off);
    if (rc)
        goto out;

    rc  = 0;
out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
int
I2cBusViaGpioT<PinT>::rx_bit(bool * const p_bit) const {
    int rc = -1;
    typename PinT::mode_t value;

    rc = this->set(m_scl, PinT::Off);
    if (rc)
        goto out;

    /*
     * Set pin(s) directly instead of our private method. The latter will read the
     * line back after setting it which won't work if the slave is pulling the
     * clock low, or is attempting to send a low bit.
     */
    rc = this->m_sda->set(PinT::HiZ);
    if (rc)
        goto out;

    usleep(this->m_delay);

    rc = this->m_scl->set(PinT::HiZ);
    if (rc)
        goto out;

    usleep(this->m_delay);

    do {
      rc = this->m_scl->get(value);
      if (rc)
          goto out;
    } while (value != PinT::On);

    rc = this->m_sda->get(value);
    if (rc)
        goto out;

    rc  = 0;

    if (p_bit != NULL) {
        if (value == PinT::Off) {
            *p_bit = false;
        } else {
            *p_bit = true;
        }
    }

    rc = this->set(m_scl, PinT::Off);

out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
int
I2cBusViaGpioT<PinT>::start(const uint8_t p_addr, const bool p_repeated) const {
    int rc = -1;
    bool value;

    assert(m_scl != NULL);
    assert(m_sda != NULL);

    bool idle = this->is_idle();
    if (p_repeated) {
        rc = this->set(m_scl, PinT::HiZ);
        assert(!rc);

        rc = this->set(m_sda, PinT::HiZ);
        assert(!rc);
    } else if (!idle) {
        rc = -1;
        goto out;
    }

    rc = this->start_condition();
    if (rc != 0)
        goto out;

    for (int i = 7; i >= 0; i--) {
        rc = this->tx_bit((p_addr >> i) & 0x1);
        if (rc != 0)
            goto out;
    }

    rc = this->rx_bit(&value);
    if (rc != 0 || value) {
        rc = -1;
        goto out;
    }

    rc = 0;
out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
int
I2cBusViaGpioT<PinT>::stop(void) const {
    int rc = -1;

    assert(m_scl != NULL);
    assert(m_sda != NULL);

    rc = this->set(m_scl, PinT::Off);
    if (rc)
        goto out;

    rc = this->set(m_sda, PinT::Off);
    if (rc)
        goto out;

    rc = this->set(m_scl, PinT::HiZ);
    if (rc)
        goto out;

    rc = this->set(m_sda, PinT::HiZ);
    if (rc)
        goto out;

    rc = 0;
out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
int
I2cBusViaGpioT<PinT>::read(uint8_t * const p_data, const bool p_ack) const {
    int rc = -1;
    bool value;

    assert(m_scl != NULL);
    assert(m_sda != NULL);

    if (p_data == NULL)
        return (EINVAL);

    for (int i = ((sizeof(*p_data) * 8)- 1); i >= 0; i--) {
        rc = this->rx_bit(&value);
        if (rc != 0)
            goto out;

        *p_data <<= 1;
        if (value)
            *p_data |= 1;
    }

    rc = this->tx_bit(!p_ack);
    if (rc)
        goto out;

out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
int
I2cBusViaGpioT<PinT>::write(const uint8_t p_data) const {
    int rc = -1;
    bool value;

    assert(m_scl != NULL);
    assert(m_sda != NULL);

    for (int i = ((sizeof(p_data) * 8)- 1); i >= 0; i--) {
        rc = this->tx_bit((p_data >> i) & 0x1);
        if (rc != 0)
            goto out;
    }

    rc = this->rx_bit(&value);
    if (rc || value) {
        rc = -1;
        goto out;
    }

out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename PinT>
int
I2cBusViaGpioT<PinT>::reset(void) const {
    int rc = -1;

    assert(m_scl != NULL);
    assert(m_sda != NULL);

    for (int i = 0; i < 9; i++) {
        rc = this->rx_bit(NULL);
        if (rc != 0)
            goto out;
    }

    rc = this->stop();
    if (rc)
        goto out;

    rc = 0;
out:
    return (rc);
}

} /* namespace i2c */
