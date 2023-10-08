/*-
 * $Copyright$
-*/

#ifndef _DEVICE_HPP_4ca24439_07fb_48f8_8b73_6a4b9c5d9f3a
#define _DEVICE_HPP_4ca24439_07fb_48f8_8b73_6a4b9c5d9f3a

#include "Types.hpp"

namespace usb {

/*******************************************************************************
 *
 ******************************************************************************/
    namespace stm32f4 {
        template<typename UsbHwDeviceT> class InEndpointT;
        template<typename UsbHwDeviceT> class OutEndpointT;
    } /* namespace stm32f4 */
    
/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT, typename InEndpointT, typename OutEndpointT> class DefaultCtrlPipeT;

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbHwDeviceT>
class DeviceT {
public:
    typedef stm32f4::InEndpointT<UsbHwDeviceT>                                  InEndpoint;
    typedef stm32f4::OutEndpointT<UsbHwDeviceT>                                 OutEndpoint;
    typedef DefaultCtrlPipeT<DeviceT<UsbHwDeviceT>, InEndpoint, OutEndpoint>    DefaultCtrlPipe;

    DeviceT(UsbHwDeviceT &p_usbHwDevice, const UsbDeviceDescriptor_t &p_deviceDescriptor, const UsbConfigurationDescriptor_t &p_configurationDescriptor, const ::usb::UsbStringDescriptors_t &p_stringDescriptors);
    ~DeviceT();

    void registerDefaultCtrlPipe(DefaultCtrlPipe * const p_defaultCtrlPipe);
    void unregisterDefaultCtrlPipe(DefaultCtrlPipe * const p_defaultCtrlPipe);

    void initialize(void);
    void terminate(void);

    void start(void) const;
    void stop(void) const;
    
    void attach(void);
    void powerUp(void);
    void usbReset(void);
    void assignAddress(void);
    void configureDevice(void);
    void suspend(void);
    void resume(void);
    void powerDown(void);
    void detach(void);
    
    /*******************************************************************************
     * Callbacks
     ******************************************************************************/
    void handleSetupPacket(const ::usb::SetupPacket_t &p_setupPacket) const;
    void handleDeviceRequest(const ::usb::SetupPacket_t &p_setupPacket) const;

 private:
    /*******************************************************************************
     * Private Variables
     ******************************************************************************/
    UsbHwDeviceT &                              m_usbHwDevice;
    const ::usb::UsbDeviceDescriptor_t &        m_deviceDescriptor;
    const ::usb::UsbDeviceQualifierDescriptor_t m_deviceQualifierDescriptor;
    const ::usb::UsbConfigurationDescriptor_t & m_configurationDescriptor;
    const ::usb::UsbStringDescriptors_t &       m_stringDescriptors;
    UsbDeviceState_t                            m_deviceState;
    DefaultCtrlPipe *                           m_defaultCtrlPipe;
    UsbDeviceStatus_t                           m_deviceStatus;

    /*******************************************************************************
     * Private Functions
     ******************************************************************************/

    /*******************************************************************************
     * USB Standard Ctrl Transfer Methods
     ******************************************************************************/
    void setAddress(const uint8_t p_address) const;
    void getDescriptor(const uint16_t p_descriptor, const size_t p_len) const;
    void setConfiguration(const uint8_t p_configuration) const;
    void getStatus(const uint8_t p_len) const;
    
    /*******************************************************************************
     * GetDescriptor() Methods
     ******************************************************************************/
    void getDeviceDescriptor(const uint8_t p_descriptorId, const size_t p_len) const;
    void getDeviceQualifierDescriptor(const uint8_t p_descriptorId, const size_t p_len) const;
    void getStringDescriptor(const uint8_t p_descriptorId, const size_t p_len) const;
    void getConfigurationDescriptor(const uint8_t p_descriptorId, const size_t p_len) const;
    
}; /* class DeviceT */
    
/*******************************************************************************
 *
 ******************************************************************************/
} /* namespace usb */

/*******************************************************************************
 *
 ******************************************************************************/
#include "Device.cpp"

#endif /* _DEVICE_HPP_4ca24439_07fb_48f8_8b73_6a4b9c5d9f3a */
