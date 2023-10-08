/*-
 * $Copyright$
-*/

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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include <lpt/LptAccess.hpp>

#include <gpio/GpioAccess.hpp>
#include <gpio/GpioAccessViaLpt.cpp>

#include <gpio/GpioEngine.hpp>
#include <gpio/GpioPin.hpp>
#include <gpio/GpioPin.cpp>

#include <uart/UartAccess.hpp>
#include <uart/UartAccessLinux.cpp>
#include <uart/UartDevice.hpp>
#include <uart/UartDevice.cpp>

#include <tasks/Heartbeat.hpp>

static uart::UartAccess uart_access(stdout);
static uart::UartDevice g_uart(&uart_access);

static lpt::LptAccess           lpt_access;
static gpio::GpioAccess         gpio_access(&lpt_access);
static gpio::GpioEngine         gpio_engine(&gpio_access);

static gpio::GpioPin            g_led(&gpio_engine, 0);

static tasks::HeartbeatT<>      heartbeat("Heartbeat", g_uart, g_led, 4, 500);

char ucHeap[64 * 1024]; // FreeRTOS Heap

int
main(int /* argc */, char **  /* argv */) {
    g_led.set(gpio::Pin::Off);

    g_uart.printf("Copyright (c) 2013-2014, Philip Schulz <phs@phisch.org>\r\n");
    g_uart.printf("All rights reserved.\r\n");
    g_uart.printf("\r\n");

    g_uart.printf("Starting FreeRTOS Scheduler...\r\n");

    vTaskStartScheduler();

    g_uart.printf("FATAL ERROR!\r\n");
    return (-1);
}

#if defined(__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

void
halt(const char * const p_file, const unsigned p_line) {
    g_uart.printf("%s(): %s : %d\r\n", __func__, p_file, p_line);
    while (1) { };
}

void
assert_failed(uint8_t *p_file, uint32_t p_line) {
    halt(reinterpret_cast<char *>(p_file), p_line);
}

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined (__cplusplus) */

