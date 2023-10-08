/*-
 * $Copyright$
-*/

#ifndef _OUTENDPOINT_HPP_669fcf90_b666_4583_97b7_e50a9d1447d9
#define _OUTENDPOINT_HPP_669fcf90_b666_4583_97b7_e50a9d1447d9

#include <usb/Types.hpp>

namespace usb {
    namespace stm32f4 {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT = UsbDevice>
class OutEndpointT {
private:
    UsbDeviceT &                        m_usbDevice;
    const unsigned                      m_endpointNumber;
    USB_OTG_OUTEndpointTypeDef * const  m_endpoint;
    volatile uint32_t * const           m_rxFifoAddr;

    /*******************************************************************************
     * Typedefs and static buffer for IRQ Handler
     ******************************************************************************/
    typedef void (usb::stm32f4::OutEndpointT<UsbDeviceT> ::*irq_handler_fn)();

    typedef struct irq_handler_s {
        uint32_t m_irq;
        irq_handler_fn m_fn;
    } irq_handler_t;

    static const irq_handler_t m_irq_handler[];

    /*******************************************************************************
     * Static buffer for Setup Packet
     ******************************************************************************/
    typedef union RxBuffer_u {
        uint32_t                m_rxBuffer32[2];
        uint8_t                 m_rxBuffer8[sizeof(m_rxBuffer32) / sizeof(m_rxBuffer32[0])];
        ::usb::SetupPacket_t    m_setupPacket;
    } RxBuffer_t;
    RxBuffer_t      m_rxBuffer;
    unsigned        m_rxBufferCurPos;

    /*******************************************************************************
     * Private Functions
     ******************************************************************************/
    void                setNack(const bool p_nack) const;
    void                handleSetupDone(void);
    void                handleTransferComplete();

public:
    OutEndpointT(UsbDeviceT &p_usbDevice, const unsigned p_endpointNumber = 0);
    ~OutEndpointT();

    unsigned        getEndpointNumber(void) const { return this->m_endpointNumber; }

    void            initialize(void) const;
    void            terminate(void) const;
    
    void            reset(void) const;

    void            disable(void) const;
    void            enable(void) const;

    void            handleIrq(void);

    void            enableSetupPackets(const unsigned p_numPackets) const;

    void            handleRxData(const size_t p_numBytes);

#if 0
    void disableIrq(void) const {
        this->m_usbDevice.disableEndpointIrq(*this);
    }

    void enableIrq(void) const {
        this->m_usbDevice.enableEndpointIrq(*this);
    }
#endif
};

/*******************************************************************************
 *
 ******************************************************************************/
typedef OutEndpointT<> OutEndpoint;

    } /* namespace stm32f4 */
} /* namespace usb */

#include "OutEndpoint.cpp"

#endif /* _OUTENDPOINT_HPP_669fcf90_b666_4583_97b7_e50a9d1447d9 */
