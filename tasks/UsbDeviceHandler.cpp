/*-
 * $Copyright$
-*/

#ifndef _USBDEVICEHANDLER_CPP_507edde2_3f3c_4aad_b436_52618216b7e3
#define _USBDEVICEHANDLER_CPP_507edde2_3f3c_4aad_b436_52618216b7e3

#include <tasks/UsbDeviceHandler.hpp>

namespace tasks {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT>
UsbDeviceHandlerT<UsbDeviceT>::UsbDeviceHandlerT(const char* const p_name, UsbDeviceT& p_usbDevice, unsigned p_priority)
  : ::tasks::Task(p_name, p_priority), m_usbDevice(p_usbDevice) {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT>
UsbDeviceHandlerT<UsbDeviceT>::~UsbDeviceHandlerT() {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UsbDeviceT>
void
UsbDeviceHandlerT<UsbDeviceT>::run(void) {
    this->m_usbDevice.initialize();

    do {
        this->m_usbDevice.start();
        vTaskSuspend(NULL);
        this->m_usbDevice.stop();
    } while (0);

    this->m_usbDevice.terminate();
}

/*******************************************************************************
 *
 ******************************************************************************/
} /* namespace tasks */

#endif /* _USBDEVICEHANDLER_CPP_507edde2_3f3c_4aad_b436_52618216b7e3 */