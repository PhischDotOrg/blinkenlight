/*-
 * $Copyright$
-*/

#ifndef _DEVICE_CPP_6566c54d_ecde_4527_9b5c_0917357d9d1b
#define _DEVICE_CPP_6566c54d_ecde_4527_9b5c_0917357d9d1b

#include "Device.hpp"

namespace usb {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
DeviceT<UsbHwDeviceT>::DeviceT(UsbHwDeviceT& p_usbHwDevice, const UsbDeviceDescriptor_t& p_deviceDescriptor,
  const UsbConfigurationDescriptor_t& p_configurationDescriptor, const UsbStringDescriptors_t &p_stringDescriptors) : 
    m_usbHwDevice(p_usbHwDevice),
    m_deviceDescriptor(p_deviceDescriptor),
    m_deviceQualifierDescriptor(m_deviceDescriptor),
    m_configurationDescriptor(p_configurationDescriptor),
    m_stringDescriptors(p_stringDescriptors),
    m_deviceState(::usb::UsbDeviceState_t::e_Detached),
    m_defaultCtrlPipe(NULL),
    m_deviceStatus { 0x1 }
{
    this->m_usbHwDevice.registerDevice(this);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
DeviceT<UsbHwDeviceT>::~DeviceT() {
    this->m_usbHwDevice.unregisterDevice(this);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::initialize() {
    assert(this->m_defaultCtrlPipe != NULL);

    this->attach();
    this->powerUp();

    this->m_usbHwDevice.initialize();

    this->m_defaultCtrlPipe->initialize();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::terminate() {
    assert(this->m_defaultCtrlPipe != NULL);

    this->m_defaultCtrlPipe->terminate();
//    this->m_usbHwDevice.terminate();
    
    this->powerDown();
    this->detach();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::registerDefaultCtrlPipe(DefaultCtrlPipe * const p_defaultCtrlPipe) {
    assert(this->m_defaultCtrlPipe == NULL);
    assert(p_defaultCtrlPipe != NULL);
    
    this->m_defaultCtrlPipe = p_defaultCtrlPipe;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::unregisterDefaultCtrlPipe(DefaultCtrlPipe * const p_defaultCtrlPipe) {
    assert(this->m_defaultCtrlPipe = p_defaultCtrlPipe);
    
    this->m_defaultCtrlPipe = NULL;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::attach() {
    this->m_deviceState = e_Attached;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::detach() {
    this->m_deviceState = e_Detached;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::powerUp() {
    this->m_deviceState = e_Powered;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::powerDown() {
    this->m_deviceState = e_Attached;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::usbReset() {
    this->m_deviceState = e_Default;
    
    this->m_usbHwDevice.usbReset();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::start() const {
    this->m_usbHwDevice.start();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::stop() const {
    this->m_usbHwDevice.stop();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::handleSetupPacket(const ::usb::SetupPacket_t &p_setupPacket) const {
    assert(this->m_defaultCtrlPipe != NULL);
    this->m_defaultCtrlPipe->handleSetupPacket(p_setupPacket);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::handleDeviceRequest(const ::usb::SetupPacket_t &p_setupPacket) const {
    switch (p_setupPacket.m_bRequest) {
    case e_SetAddress:
        this->setAddress(p_setupPacket.m_wValue & 0x7F);
        break;
    case e_GetDescriptor:
        this->getDescriptor(p_setupPacket.m_wValue, p_setupPacket.m_wLength);
        break;
    case e_SetConfiguration:
        this->setConfiguration(p_setupPacket.m_wValue);
        break;
    case e_GetStatus:
        this->getStatus(p_setupPacket.m_wLength);
        break;
    default:
        assert(false);
        break;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::setAddress(const uint8_t p_address) const {
    this->m_usbHwDevice.setHwAddress(p_address);

    /* Acknowledge the setAddress() command on the Default Ctrl Endpoint */
    assert(this->m_defaultCtrlPipe != NULL);
    this->m_defaultCtrlPipe->write(NULL, 0, 0);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::setConfiguration(const uint8_t /* p_configuration */) const {
    /* Acknowledge the setAddress() command on the Default Ctrl Endpoint */
    assert(this->m_defaultCtrlPipe != NULL);
    this->m_defaultCtrlPipe->write(NULL, 0, 0);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::getStatus(const uint8_t p_len) const {
    assert(this->m_defaultCtrlPipe != NULL);
    this->m_defaultCtrlPipe->write(reinterpret_cast<const uint8_t * const>(&this->m_deviceStatus), sizeof(this->m_deviceStatus), p_len);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::getDescriptor(const uint16_t p_descriptor, const size_t p_len) const {
    const UsbDescriptorTypeId_t descriptorType = static_cast<const UsbDescriptorTypeId_t>((p_descriptor >> 8) & 0x07);
    uint8_t                     descriptorId = p_descriptor & 0xFF;

    switch (descriptorType) {
    case e_Device:
        this->getDeviceDescriptor(descriptorId, p_len);
        break;
    case e_String:
        this->getStringDescriptor(descriptorId, p_len);
        break;
    case e_Configuration:
        this->getConfigurationDescriptor(descriptorId, p_len);
        break;
    case e_DeviceQualifier:
        this->getDeviceQualifierDescriptor(descriptorId, p_len);
        break;
    case e_Interface:
    case e_Endpoint:
    case e_OtherSpeedConfig:
        /* FIXME Not yet implemented */
        assert(false);
        break;
    }
}


/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::getDeviceDescriptor(const uint8_t p_descriptorId, const size_t p_len) const {
    assert(p_descriptorId == 0);

    assert(this->m_defaultCtrlPipe != NULL);
    this->m_defaultCtrlPipe->write(reinterpret_cast<const uint8_t * const>(&this->m_deviceDescriptor), sizeof(this->m_deviceDescriptor), p_len);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::getDeviceQualifierDescriptor(const uint8_t p_descriptorId, const size_t p_len) const {
    assert(p_descriptorId == 0);

    assert(this->m_defaultCtrlPipe != NULL);
    this->m_defaultCtrlPipe->write(reinterpret_cast<const uint8_t * const>(&this->m_deviceQualifierDescriptor), sizeof(this->m_deviceQualifierDescriptor), p_len);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::getConfigurationDescriptor(const uint8_t p_descriptorId, const size_t p_len) const {
    assert(p_descriptorId == 0);

    assert(this->m_defaultCtrlPipe != NULL);
    this->m_defaultCtrlPipe->write(reinterpret_cast<const uint8_t * const>(&this->m_configurationDescriptor), p_len, p_len);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
void
DeviceT<UsbHwDeviceT>::getStringDescriptor(const uint8_t p_descriptorId, const size_t p_len) const {
    UsbStringDescriptorId_t stringDescriptor = static_cast<UsbStringDescriptorId_t>(p_descriptorId);

    if (p_descriptorId >= e_StrDesc_Max) {
        goto out;
    }

    assert(this->m_defaultCtrlPipe != NULL);

    switch (stringDescriptor) {
    case e_StrDesc_LanguageId: {
        static uint8_t  buffer[64];
        UsbLangId_t *   cur = reinterpret_cast<UsbLangId_t *>(&buffer[2]);
        unsigned        idx;

        buffer[1] = e_String;

        for (idx = 0; idx < this->m_stringDescriptors.m_stringDescriptorTable.m_languageIds.m_numLanguages; idx++, cur++) {
            * cur = this->m_stringDescriptors.m_stringDescriptorTable.m_languageIds.m_langIds[idx];
        }

        buffer[0] = 2 + idx * sizeof(UsbLangId_t);

        this->m_defaultCtrlPipe->write(buffer, buffer[0], p_len);
    } break;
    case e_StrDesc_Manufacturer:
    case e_StrDesc_Product:
    case e_StrDesc_SerialNumber:
    case e_StrDesc_Configuration:
    case e_StrDesc_Interface:
        this->m_defaultCtrlPipe->writeString(this->m_stringDescriptors.m_stringDescriptors[stringDescriptor], p_len);
        break;
    default:
        break;
    }

out:
    return;
}

/*******************************************************************************
 *
 ******************************************************************************/
} /* namespace usb */

#endif /* _DEVICE_CPP_6566c54d_ecde_4527_9b5c_0917357d9d1b */
