/*-
 * $Copyright$
-*/

#ifndef _DEFAULTCTRLPIPE_HPP_737b7320_93fb_4a66_ab3f_3febfbc74fd9
#define _DEFAULTCTRLPIPE_HPP_737b7320_93fb_4a66_ab3f_3febfbc74fd9

#include <usb/Types.hpp>

namespace usb {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT>
class DefaultCtrlPipeT {
public:
    DefaultCtrlPipeT(UsbDeviceT &p_usbDevice, InEndpointT &p_inEndpoint, OutEndpointT &p_outEndpoint);
    ~DefaultCtrlPipeT();

    void initialize(void) const;
    void terminate(void) const;

    void write(const uint8_t * const p_data, const size_t p_dataLength, const size_t p_txLength);
    void writeString(const ::usb::UsbStringDescriptor &p_string, const size_t p_len);
    
    /*******************************************************************************
     * Callbacks
     ******************************************************************************/
    void handleSetupPacket(const ::usb::SetupPacket_t &p_setupPacket) const;

private:
    UsbDeviceT &    m_usbDevice;
    InEndpointT &   m_inEndpoint;
    OutEndpointT &  m_outEndpoint;
};

/*******************************************************************************
 *
 ******************************************************************************/
} /* namespace usb */

#include "DefaultCtrlPipe.cpp"

#endif /* _DEFAULTCTRLPIPE_HPP_737b7320_93fb_4a66_ab3f_3febfbc74fd9 */
