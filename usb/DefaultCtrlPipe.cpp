/*-
 * $Copyright$
-*/

#ifndef _DEFAULTCTRLPIPE_CPP_29f87cb2_c4e9_463a_b1ed_be19a27a9fa9
#define _DEFAULTCTRLPIPE_CPP_29f87cb2_c4e9_463a_b1ed_be19a27a9fa9

#include "DefaultCtrlPipe.hpp"

namespace usb {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT>
DefaultCtrlPipeT<UsbDeviceT, InEndpointT, OutEndpointT>::DefaultCtrlPipeT(UsbDeviceT& p_usbDevice, InEndpointT& p_inEndpoint, OutEndpointT& p_outEndpoint)
  : m_usbDevice(p_usbDevice), m_inEndpoint(p_inEndpoint), m_outEndpoint(p_outEndpoint) {
    this->m_usbDevice.registerDefaultCtrlPipe(this);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT>
DefaultCtrlPipeT<UsbDeviceT, InEndpointT, OutEndpointT>::~DefaultCtrlPipeT() {
    this->m_usbDevice.unregisterDefaultCtrlPipe(this);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT>
void
DefaultCtrlPipeT<UsbDeviceT, InEndpointT, OutEndpointT>::initialize() const {
    this->m_outEndpoint.initialize();
    this->m_inEndpoint.initialize();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT>
void
DefaultCtrlPipeT<UsbDeviceT, InEndpointT, OutEndpointT>::terminate() const {
    this->m_outEndpoint.terminate();
    this->m_inEndpoint.terminate();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT>
void
DefaultCtrlPipeT<UsbDeviceT, InEndpointT, OutEndpointT>::handleSetupPacket(const ::usb::SetupPacket_t &p_setupPacket) const {
    const UsbRecipient_t usbRecipient = static_cast<UsbRecipient_t>(p_setupPacket.m_bmRequestType & 0x0F);

    switch (usbRecipient) {
    case e_RecipientDevice:
        this->m_usbDevice.handleDeviceRequest(p_setupPacket);
        break;
    case e_RecipientInterface:
    case e_RecipientEndpoint:
    case e_RecipientOther:
    default:
        /* FIXME Not yet implemented */
        assert(false);
        break;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT>
void
DefaultCtrlPipeT<UsbDeviceT, InEndpointT, OutEndpointT>::write(const uint8_t * const p_data, const size_t p_dataLength, const size_t p_txLength) {
    this->m_inEndpoint.write(p_data, p_dataLength, p_txLength);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT>
void
DefaultCtrlPipeT<UsbDeviceT, InEndpointT, OutEndpointT>::writeString(const ::usb::UsbStringDescriptor &p_string, const size_t p_len) {
    this->m_inEndpoint.writeString(p_string, p_len);
}

} /* namespace usb */

#endif /* _DEFAULTCTRLPIPE_CPP_29f87cb2_c4e9_463a_b1ed_be19a27a9fa9 */
