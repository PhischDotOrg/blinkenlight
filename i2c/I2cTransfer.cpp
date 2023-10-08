/*-
 * $Copyright$
-*/

#include <i2c/I2cTransfer.hpp>

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <stdio.h>
#include <stdint.h>

#if defined(__cplusplus)
#if !defined(__STDC_FORMAT_MACROS)
#error This code requires __STDC_FORMAT_MACROS to be defined!
#endif /* !defined(__STDC_FORMAT_MACROS) */
#endif /* defined(__cplusplus) */
#include <inttypes.h>

#include <errno.h>

namespace i2c {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT, typename DeviceT>
TransferT<BusT, DeviceT>::TransferT(BusT *p_bus, DeviceT *p_device, std::istream &p_istream, std::ostream &p_ostream)
  : m_bus(p_bus), m_device(p_device), m_istream(p_istream), m_ostream(p_ostream) {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT, typename DeviceT>
int
TransferT<BusT, DeviceT>::reset(void) const {
    return m_bus->reset();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT, typename DeviceT>
int
TransferT<BusT, DeviceT>::scan(void) const {
    int rc = 0;
    char buffer[16];

    m_ostream << "Devices found: " << std::endl;

    for (uint16_t addr = 0; addr < 256; addr += 2) {
        rc = m_bus->start(addr, false);
        if (rc) {
            rc = m_bus->reset();
            if (rc)
                goto out;
        } else {
            snprintf(buffer, sizeof(buffer), "0x%.02" PRIx16, addr);
            m_ostream << buffer << std::endl;

            rc = m_bus->stop();
            if (rc)
                goto out;
        }
    }

out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT, typename DeviceT>
ssize_t
TransferT<BusT, DeviceT>::read(off_t p_offset, size_t p_length, bool p_binary) const {
    char *buffer = new char[p_length];
    ssize_t len = m_device->read(p_offset, (uint8_t *) buffer, p_length);
    if (len > 0) {
        if (p_binary) {
            m_ostream.write(buffer, len);
        } else {
            static const int bpl = 16; // Bytes per line
            char outp[1024];

            uint32_t pre = p_offset % bpl;
            uint32_t post = pre > 0 ? bpl - pre + 1 : 0;

            uint32_t low = p_offset - pre;
            uint32_t top = p_offset + len + post;

            for (uint32_t i = 0; i < (top - low); i++) {
                if (!(i % bpl)) {
                    snprintf(outp, sizeof(outp), "[0x%.08" PRIx32 "] ", low + i);
                    m_ostream << outp;
                }

                if ((i >= pre) && (i < (top - low - post))) {
                    snprintf(outp, sizeof(outp), "%.02x", (unsigned char) buffer[i - pre]);
                } else {
                    snprintf(outp, sizeof(outp), "..");
                }
                m_ostream << outp;

                if ((i + 1) < (top - low)) {
                    if (!((i + 1) % bpl))
                        m_ostream << std::endl;
                    else if (!((i + 1) % 4))
                        m_ostream << " ";
                }
            }
            m_ostream << std::endl;
        }
    } else {
        len = -1 * EIO;
    }
    delete[] buffer;
    return len;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename BusT, typename DeviceT>
ssize_t
TransferT<BusT, DeviceT>::write(off_t p_offset, size_t p_length, const uint8_t * const p_data) const {
    ssize_t len = -1 * ENOSYS;

    if (p_data == NULL) {
        char *buffer = new char[p_length];
        m_istream.read(buffer, p_length);
        len = m_istream.gcount();
        len = m_device->write(p_offset, (uint8_t *) buffer, len);
        delete[] buffer;
    } else {
        len = m_device->write(p_offset, p_data, p_length);
    }

    return (len);
}

} /* namespace i2c */
