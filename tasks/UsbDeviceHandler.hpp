/*-
 * $Copyright$
-*/

#ifndef _USBDEVICEHANDLER_HPP_032cb8aa_2e25_41ae_bb21_980893548bca
#define _USBDEVICEHANDLER_HPP_032cb8aa_2e25_41ae_bb21_980893548bca

#include "tasks/Task.hpp"

namespace tasks {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT>    
class UsbDeviceHandlerT : public Task {
public:
    UsbDeviceHandlerT(const char * const p_name, UsbDeviceT &p_usbDevice, unsigned p_priority);
    virtual ~UsbDeviceHandlerT();

private:
    virtual void run(void);
    
    UsbDeviceT &    m_usbDevice;
};

}; /* namespace tasks */

/*******************************************************************************
 *
 ******************************************************************************/
#include "UsbDeviceHandler.cpp"

#endif /* _USBDEVICEHANDLER_HPP_032cb8aa_2e25_41ae_bb21_980893548bca */

