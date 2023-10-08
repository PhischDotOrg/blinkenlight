/*-
 * $Copyright$
-*/

#ifndef _USBDEVICE_HPP_32f4ccff_87e2_4eac_87e7_6297472e365d
#define _USBDEVICE_HPP_32f4ccff_87e2_4eac_87e7_6297472e365d

#include "UsbCore.hpp"
#include <usb/Types.hpp>

namespace usb {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT> class DeviceT;

/*******************************************************************************
 *
 ******************************************************************************/
    namespace stm32f4 {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT> class InEndpointT;
template<typename UsbDeviceT> class OutEndpointT;
template<typename UsbCoreT> class UsbDeviceViaUsbCoreT;

/*******************************************************************************
 *
 ******************************************************************************/
class UsbDeviceBase {
public:
    typedef InEndpointT<UsbDeviceViaUsbCoreT<UsbCore> > InEndpoint;
    typedef OutEndpointT<UsbDeviceViaUsbCoreT<UsbCore> > OutEndpoint;

    enum DeviceSpeed_e {
        e_UsbFullSpeed = 0x3
    };

    void registerEndpoint(const unsigned p_endpointNumber, InEndpoint &p_endpoint);
    void unregisterEndpoint(const unsigned p_endpointNumber, InEndpoint &p_endpoint);

    void disableEndpointIrq(const InEndpoint &p_endpoint) const;
    void enableEndpointIrq(const InEndpoint &p_endpoint) const;

    void disableEndpointFifoIrq(const InEndpoint &p_endpoint) const;
    void enableEndpointFifoIrq(const InEndpoint &p_endpoint) const;

    void registerEndpoint(const unsigned p_endpointNumber, OutEndpoint &p_endpoint);
    void unregisterEndpoint(const unsigned p_endpointNumber, OutEndpoint &p_endpoint);
    
    void setHwAddress(const uint8_t p_address) const;

protected:
    /*******************************************************************************
     * Protected Data Types
     ******************************************************************************/
    const DeviceSpeed_e             m_deviceSpeed;

    static const size_t             m_maxInEndpoints = 4;
    static const size_t             m_maxOutEndpoints = 4;

    InEndpoint *                    m_inEndpoints[m_maxInEndpoints];
    OutEndpoint *                   m_outEndpoints[m_maxOutEndpoints];

    /*******************************************************************************
     * Protected Methods
     ******************************************************************************/
            UsbDeviceBase(intptr_t p_deviceAddr, const DeviceSpeed_e p_speed);
    virtual ~UsbDeviceBase();

    bool    isSuspendableState(void) const;
    
    void    disableEndpointIrq(const OutEndpoint &p_endpoint) const;
    void    enableEndpointIrq(const OutEndpoint &p_endpoint) const;
    void    enableOutEndpointsIrq(const uint32_t p_irq) const;

    void    enableInEndpointsIrq(const uint32_t p_irq) const;

    void    disableInterrupts(void) const;

    void    setupDeviceSpeed(const DeviceSpeed_e p_speed) const;

    /*******************************************************************************
     * IRQ Handlers
     ******************************************************************************/
    void    handleRxFIFO(const uint32_t p_rxStatus) const;
    void    handleEnumerationDone(void) const;
    
private:
    /*******************************************************************************
     * Private Variables
     ******************************************************************************/
    USB_OTG_DeviceTypeDef * const           m_usbDevice;
    const uint8_t                           m_maxConfigurations;

    /*******************************************************************************
     * Private Methods
     ******************************************************************************/
    void    disconnect(void) const;
    void    connect(void) const;

    void    handleUsbReset(void) const;
    void    handleStartOfFrame(void) const;
    void    handleInEndpointIrq(void) const;
    void    handleOutEndpointIrq(void) const;
    void    handleDisconnectIrq(void) const;

    void    disableEndpointIrq(const unsigned &p_endpointNumber, bool p_isOutEndpoint) const;
    void    enableEndpointIrq(const unsigned &p_endpointNumber, bool p_isOutEndpoint) const;
};

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbCoreT = UsbCore>
class UsbDeviceViaUsbCoreT : public UsbDeviceBase {
public:
    /*******************************************************************************
     *
     ******************************************************************************/
            UsbDeviceViaUsbCoreT(UsbCoreT &p_usbCore, const DeviceSpeed_e p_deviceSpeed = e_UsbFullSpeed);
    virtual ~UsbDeviceViaUsbCoreT();

    void        registerDevice(::usb::DeviceT<UsbDeviceViaUsbCoreT<UsbCoreT > > * const p_device);
    void        unregisterDevice(::usb::DeviceT<UsbDeviceViaUsbCoreT<UsbCoreT > > * const p_device);

    uint32_t    handleIrq(const uint32_t p_irq) const;


    void        initialize(void) const;
    void        terminate(void) const;

    void        start(void) const;
    void        stop(void) const;

    void        setupTxFifo(const InEndpointT< UsbDeviceViaUsbCoreT<UsbCoreT> > &p_endpoint) const;
    void        flushTxFifo(const InEndpointT< UsbDeviceViaUsbCoreT<UsbCoreT> > &p_endpoint) const;
    
    void        handleSetupPacket(const ::usb::SetupPacket_t &p_setupPacket) const;

    /*******************************************************************************
     * USB Standard Ctrl Transfer Methods
     ******************************************************************************/
    void        usbReset(void) const;

    /*******************************************************************************
     * Const-Expr. Method for Endpoint Classes
     ******************************************************************************/
    constexpr intptr_t getBaseAddr(void) const {
        return m_usbCore.getBaseAddr();
    };

#if !defined(NDEBUG)
    bool    isIrqHandled(const typename UsbCoreT::Interrupt_t p_irq) const;
#endif /* !defined(NDEBUG) */

private:
    /*******************************************************************************
     * Private Variables
     ******************************************************************************/
    UsbCoreT &                                          m_usbCore;
    ::usb::DeviceT<UsbDeviceViaUsbCoreT<UsbCoreT > > *  m_usbDevice; 
    
    typedef void (usb::stm32f4::UsbDeviceViaUsbCoreT<UsbCoreT>::*irq_handler_fn)() const;

    typedef struct irq_handler_s {
        uint32_t            m_irq;
        irq_handler_fn      m_fn;
    } irq_handler_t;

    static const irq_handler_t m_irq_handler[];

    /*******************************************************************************
     * Private Methods
     ******************************************************************************/
    void        setupTxFifos(void) const;

    void        handleUsbSuspend(void) const;
    void        handleRxFIFO(void) const;
    void        handleEnumerationDone(void) const;
    void        handleUsbReset(void) const;
};

/*******************************************************************************
 *
 ******************************************************************************/
typedef class UsbDeviceViaUsbCoreT<> UsbDevice;

    } /* namespace stm32f4 */
} /* namespace usb */

#include "UsbDevice.cpp"

#endif /* _USBDEVICE_HPP_32f4ccff_87e2_4eac_87e7_6297472e365d */
