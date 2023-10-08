/*-
 * $Copyright$
-*/

#ifndef _HEARTBEAT_HPP_a5964436_f7c6_4492_be3f_a6bff7e8d6c8
#define _HEARTBEAT_HPP_a5964436_f7c6_4492_be3f_a6bff7e8d6c8

#include "tasks/Heartbeat.hpp"

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */

#include "gpio/GpioPin.hpp"
#include "gpio/GpioEngine.hpp"
#include "gpio/GpioAccess.hpp"

#include "uart/Uart.hpp"

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/semphr.h"
#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */

namespace tasks {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UartT, typename PinT>
HeartbeatT<UartT, PinT>::HeartbeatT(const char * const p_name, UartT &p_uart, PinT &p_led,
 const unsigned p_priority, const unsigned p_periodMs /* = 1000 */)
  : Task(p_name, p_priority), m_uart(p_uart), m_led(p_led), m_periodMs(p_periodMs) {
    
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UartT, typename PinT>
HeartbeatT<UartT, PinT>::~HeartbeatT() {
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename UartT, typename PinT>
void
HeartbeatT<UartT, PinT>::run(void) {
    this->m_uart.printf("Task '%s' starting...\r\n", this->m_name);

    TickType_t period = ((this->m_periodMs * 1000) / 2) / portTICK_RATE_MICROSECONDS;
    do {
        this->m_led.set(PinT::On);
        vTaskDelay(period);

        this->m_led.set(PinT::Off);
        vTaskDelay(period);
    } while (1);
}

} /* namespace tasks */

#endif /* _HEARTBEAT_HPP_a5964436_f7c6_4492_be3f_a6bff7e8d6c8 */
