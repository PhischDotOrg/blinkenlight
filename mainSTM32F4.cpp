/*-
 * $Copyright$
-*/

#if defined(CALBRATION)
#define DEBUG_FRAME_FILTER
#define DEBUG_WS2812B_DISPLAY
#define SAMPLING_DELAY 1000u
#else
#define SAMPLING_DELAY 0u
#endif

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/semphr.h"
    
int __errno;

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */

#include <stddef.h>

#include <devices/PwrViaSTM32F4.hpp>
#include <devices/FlashViaSTM32F4.hpp>
#include <devices/RccViaSTM32F4.hpp>
#include <devices/ScbViaSTM32F4.hpp>
#include <devices/NvicViaSTM32F4.hpp>

#include <devices/Sr74x595.hpp>
#include <devices/LedMatrixGTM2088RGB.hpp>
#include <devices/Ws2812bStrip.hpp>

#include <dma/DmaChannel.hpp>
#include <dma/DmaEngineViaSTM32F4.cpp>

#include <gpio/GpioAccess.hpp>
#include <gpio/GpioAccessViaSTM32F4.cpp>

#include <gpio/GpioEngine.hpp>
#include <gpio/GpioPin.hpp>
#include <gpio/GpioPin.cpp>

#include <timer/Timer.hpp>

#include <uart/UartAccess.hpp>
#include <uart/UartDevice.hpp>
#include <uart/UartDevice.cpp>

#include <tasks/FrameSampler.hpp>
#include <tasks/FrameFilter.hpp>
#include <tasks/FrameDisplayer.hpp>
#include <tasks/Heartbeat.hpp>
#include <tasks/LedMatrixDisplay.hpp>
#include <tasks/RuntimeStats.hpp>
#include <tasks/Ws2812bDisplay.hpp>

#include <dsp/ConstantQ.hpp>

#include <dstruct/LockableVector.hpp>

#include <spi/SpiAccessViaSTM32F4.cpp>

#include <spi/SpiAccess.hpp>
#include <spi/SpiDevice.hpp>
#include <spi/SpiDevice.cpp>

#include <dsp/FilterChain.hpp>

#include <dsp/Complex.hpp>

#include "stm32f4xx.h"

#include <type_traits>

/*******************************************************************************
 *
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

extern char stext, etext;
extern char sdata, edata;
extern char sbss, ebss;
extern char bstack, estack;

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */

/*******************************************************************************
 * System Devices
 ******************************************************************************/
static devices::RccViaSTM32F4::PllConfiguration pllCfg(336, 8, devices::RccViaSTM32F4::e_PllP_Div2, 7,
                                                  devices::RccViaSTM32F4::e_APBPrescaler_Div4,
                                                  devices::RccViaSTM32F4::e_APBPrescaler_Div2,
                                                  devices::RccViaSTM32F4::e_AHBPrescaler_None,
                                                  devices::RccViaSTM32F4::e_PllSourceHSE,
                                                  devices::RccViaSTM32F4::e_SysclkPLL,
                                                  16000000,
                                                   8000000);

static devices::PwrViaSTM32F4           pwr(PWR);
static devices::FlashViaSTM32F4         flash(FLASH);
static devices::RccViaSTM32F4           rcc(RCC, pllCfg, flash, pwr);
static devices::ScbViaSTM32F4           scb(SCB);
static devices::NvicViaSTM32F4          nvic(NVIC, scb);

/*******************************************************************************
 * GPIO Engine Handlers 
 ******************************************************************************/
static gpio::GpioAccessViaSTM32F4_GpioA gpio_A(rcc);
static gpio::GpioEngine                 gpio_engine_A(&gpio_A);

static gpio::GpioAccessViaSTM32F4_GpioB gpio_B(rcc);
static gpio::GpioEngine                 gpio_engine_B(&gpio_B);

static gpio::GpioAccessViaSTM32F4_GpioC gpio_C(rcc);
static gpio::GpioEngine                 gpio_engine_C(&gpio_C);

static gpio::GpioAccessViaSTM32F4_GpioD gpio_D(rcc);
static gpio::GpioEngine                 gpio_engine_D(&gpio_D);

/*******************************************************************************
 * DMA Engines
 ******************************************************************************/
static dma::DmaEngineViaSTM32F4_Dma1    dma_1(rcc);
static dma::DmaEngineViaSTM32F4_Dma2    dma_2(rcc);

/*******************************************************************************
 * DMA Streams and Channels
 ******************************************************************************/
static dma::DmaStreamViaSTM32F4         sr_spiTxDmaStream(dma_1, 4);
static dma::DmaChannel                  sr_spiTxDmaChannel(sr_spiTxDmaStream, 0);

static dma::DmaStreamViaSTM32F4         sr_spiRxDmaStream(dma_1, 3);
static dma::DmaChannel                  sr_spiRxDmaChannel(sr_spiRxDmaStream, 0);

static dma::DmaStreamViaSTM32F4         adc_dmaStream(dma_2, 0);
static dma::DmaChannel                  ada_dmaChannel(adc_dmaStream, 0);

static dma::DmaStreamViaSTM32F4         ws2812b_spiTxDmaStream(dma_2, 3);
static dma::DmaChannel                  ws2812b_spiTxDmaChannel(ws2812b_spiTxDmaStream, 3);

static dma::DmaStreamViaSTM32F4         ws2812b_spiRxDmaStream(dma_2, 2);
static dma::DmaChannel                  ws2812b_spiRxDmaChannel(ws2812b_spiRxDmaStream, 3);

/*******************************************************************************
 * UART
 ******************************************************************************/
static gpio::GpioPin                    uart_tx(&gpio_engine_C, 6);
static gpio::GpioPin                    uart_rx(&gpio_engine_C, 7);
static uart::UartAccessSTM32F4_Uart6    uart_access(rcc, uart_rx, uart_tx);
uart::UartDevice                        g_uart(&uart_access);

/*******************************************************************************
 * LEDs
 ******************************************************************************/
static gpio::GpioPin                    g_led_green(&gpio_engine_D, 12);
static gpio::GpioPin                    g_led_orange(&gpio_engine_D, 13);
static gpio::GpioPin                    g_led_red(&gpio_engine_D, 14);

/*******************************************************************************
 * SPI Pins
 ******************************************************************************/
static gpio::GpioPin                    ws2812b_nsel(&gpio_engine_A, 4);
static gpio::GpioPin                    ws2812b_mosi(&gpio_engine_B, 5);
static gpio::GpioPin                    ws2812b_sclk(&gpio_engine_A, 5);
static gpio::GpioPin                    ws2812b_miso(&gpio_engine_A, 6);

/*******************************************************************************
 * SPI Handlers
 ******************************************************************************/
static spi::SpiAccessViaSTM32F4_Spi1    ws2812b_spibus(rcc, ws2812b_spiTxDmaChannel, ws2812b_spiRxDmaChannel, ws2812b_sclk, ws2812b_nsel, ws2812b_mosi, ws2812b_miso, spi::SpiAccess::e_SpiPrescaler512);
static spi::SpiDevice                   ws2812b_spidev(&ws2812b_spibus, 0);

/*******************************************************************************
 * A/C Converter
 ******************************************************************************/
static gpio::GpioPin                    adc_pin(&gpio_engine_B, 1);
static devices::AdcViaSTM32F4_Adc1      adc(rcc, ada_dmaChannel);

/*******************************************************************************
 * Timer
 ******************************************************************************/
static gpio::GpioPin                    timer_pin(&gpio_engine_D, 15);
static timer::TimerViaSTM32F4_Tim4      adc_timer(rcc);
static timer::TimerOutputChannelViaSTM32F4T<TIM4_BASE, timer::TimerViaSTM32F4::e_TimerViaSTM32F4_Channel4>  adc_timer_channel(adc_timer);

/*******************************************************************************
 * Data Buffers
 ******************************************************************************/
static const unsigned nSamples = 1212;
static const unsigned nRawFrames = 2;

/* 
 * A/D Sampler stores raw samples (unsigned 16-Bit integers, but values are
 * within 8-Bit Range) in this buffer.
 */
dstruct::LockableVectorT<
  uint16_t,
  nSamples
>                                   rawFrames[nRawFrames];

/* 
 * Filter will store transformed display frames in this buffer. The FrameDisplayer
 * task will need to  map this to actual LED bars.
 */
static const unsigned nDisplayFrames = nRawFrames;
static const unsigned nDisplayBars = 20;
static dstruct::LockableVectorT<
  float,
  nDisplayBars
>                                   displayFrames[nRawFrames];

/*******************************************************************************
 * The magic Constant Q Filter
 ******************************************************************************/
//static dsp::ConstantQT<nDisplayBars>    constantQ(64, 16384, 32768);
//static dsp::ConstantQT<nDisplayBars>    constantQ(96, 10000, 32768);
static dsp::ConstantQT<nDisplayBars>    constantQ(100, 12000, 32768);

/*******************************************************************************
 * WS2812b Stuff
 ******************************************************************************/
static devices::Ws2812bStripT<300, decltype(ws2812b_spidev)>    ws2812b_strip(ws2812b_spidev);

/*******************************************************************************
 * Tasks
 ******************************************************************************/
static tasks::Heartbeat             heartbeat_gn("heartbt", g_uart, g_led_green, 3, 1000);

QueueHandle_t                       samplerToFilterQueue;
QueueHandle_t                       filterToDisplayerQueue;

static tasks::FrameSamplerT<
  std::remove_reference<decltype(rawFrames[0])>::type,
  nRawFrames,
  decltype(adc_timer_channel),
  decltype(adc),
  decltype(g_uart)
>                                   frameSampler("frm_smpl ", 1, g_uart, rawFrames, adc_timer_channel, adc, SAMPLING_DELAY);

static tasks::FrameFilterT<
  std::remove_reference<decltype(rawFrames[0])>::type,
  std::remove_reference<decltype(displayFrames[0])>::type,
  nDisplayFrames,
  decltype(constantQ),
  decltype(g_led_orange),
  decltype(g_uart)
>                                   frameFilter("frm_fltr", 2, g_uart, displayFrames, constantQ);

static tasks::Ws2812bDisplayT<
    std::remove_reference<decltype(displayFrames[0])>::type,
    decltype(ws2812b_strip),
    decltype(g_uart)
>                                   ws2812bDisplay("ws2812b", g_uart, ws2812b_strip, 3);

#if defined(WITH_PROFILING)
static timer::TimerViaSTM32F4_Tim2 profiling_timer(rcc);

extern "C" {
    static uint32_t profilingTicks;

    void
    setupFreeRtosProfilingTimer(void) {
        profiling_timer.setup(33, 233);
        profiling_timer.enableUpdateIrq();
        profiling_timer.enable();
    };
    
    uint32_t 
    getFreeRtosProfilingTimer(void) {
        return profilingTicks;
    }

    void
    TIM2_IRQHandler(void) {
        profilingTicks++;
        profiling_timer.handleIrq();
    }
} /* extern "C" */

static tasks::RuntimeStatsT<decltype(g_uart)> runtime_stats("rt_stats", 0, g_uart, 5000);
#endif /* defined(WITH_PROFILING) */

/*******************************************************************************
 *
 ******************************************************************************/
int
main(void) {
    g_led_green.enable(gpio::GpioAccessViaSTM32F4::e_Output, gpio::GpioAccessViaSTM32F4::e_None, gpio::GpioAccessViaSTM32F4::e_Gpio);

    adc_pin.enable(gpio::GpioAccessViaSTM32F4::e_Analog, gpio::GpioAccessViaSTM32F4::e_None, gpio::GpioAccessViaSTM32F4::e_Gpio);

    g_uart.printf("Copyright (c) 2013-2015, Philip Schulz <phs@phisch.org>\r\n");
    g_uart.printf("All rights reserved.\r\n");
    g_uart.printf("\r\n");
    g_uart.printf("      Code: [0x0%x - 0x0%x]\t(%d Bytes)\r\n", &stext, &etext, &etext - &stext);
    g_uart.printf("      Data: [0x%x - 0x%x]\t(%d Bytes)\r\n", &sdata, &edata, &edata - &sdata);
    g_uart.printf("       BSS: [0x%x - 0x%x]\t(%d Bytes)\r\n", &sbss, &ebss, &ebss - &sbss);
    g_uart.printf(" Total RAM: [0x%x - 0x%x]\t(%d Bytes)\r\n", &sdata, &ebss, &ebss - &sdata);
    g_uart.printf("     Stack: [0x%x - 0x%x]\t(%d Bytes)\r\n", &bstack, &estack, &estack - &bstack);
    g_uart.printf("\r\n");

    unsigned sysclk = rcc.getSysclkSpeedInHz() / 1000;
    unsigned ahb    = rcc.getAhbSpeedInHz() / 1000;
    unsigned apb1   = rcc.getApb1SpeedInHz() / 1000;
    unsigned apb2   = rcc.getApb2SpeedInHz() / 1000;
    
    g_uart.printf("CPU running @ %d kHz\r\n", sysclk);
    g_uart.printf("        AHB @ %d kHz\r\n", ahb);
    g_uart.printf("       APB1 @ %d kHz\r\n", apb1);
    g_uart.printf("       APB2 @ %d kHz\r\n", apb2);
    g_uart.printf("\r\n");
    
    nvic.enableIrq(adc);
    nvic.enableIrq(adc_dmaStream);

    nvic.enableIrq(ws2812b_spiTxDmaStream);
    nvic.enableIrq(ws2812b_spiRxDmaStream);
    nvic.enableIrq(ws2812b_spibus);

#if defined(WITH_PROFILING)
    nvic.enableIrq(profiling_timer);

    g_led_orange.enable(gpio::GpioAccessViaSTM32F4::e_Output, gpio::GpioAccessViaSTM32F4::e_None, gpio::GpioAccessViaSTM32F4::e_Gpio);
    frameFilter.setActiveIndicationPin(&g_led_orange);
#endif /* defined(WITH_PROFILING) */

    /*
     * The timers run at twice the AHB speed. This is because the TIMPRE in the
     * RCC_DCKCFGR Register is set to zero, and our AHB clocks are down-divided
     * from the PLL Clock.
     * 
     * The ADC Timer is a APB1 Peripheral, thus being clocked at 42 MHz. Hence,
     * the timer frequency is 84 MHz. To get a timer overflow frequency of 2^15
     * or 32768 kHz we'd have to divide the Timer clock down by a factor of about
     * 2563.477.
     * 
     * Setting up a prescaler of 11 and a timer value of 233 gives us about
     * 32.774 kHz which is probably good enough for a visual display ;-)
     * 
     */
    adc_timer.setup(11 /* Prescaler */, 233 /* Timer Value */);
//    adc_timer.setup(20 /* Prescaler */, 175 /* Timer Value */);
    adc_timer.enable();
    adc_timer.setOutputPin(timer_pin);

    samplerToFilterQueue = xQueueCreate(2, sizeof(void *));
    if (samplerToFilterQueue == NULL) {
        g_uart.printf("Failed to create Sampler<->Filter Queue\r\n");
        goto bad;
    }
    frameSampler.setTxQueue(&samplerToFilterQueue);
    frameFilter.setRxQueue(frameSampler.getTxQueue());

    filterToDisplayerQueue = xQueueCreate(2, sizeof(void *));
    if (filterToDisplayerQueue == NULL) {
        g_uart.printf("Failed to create Filter<->Displayer Queue\r\n");
        goto bad;
    }
    frameFilter.setTxQueue(&filterToDisplayerQueue);
    ws2812bDisplay.setRxQueue(&filterToDisplayerQueue);

    if (SysTick_Config(SystemCoreClock / 1000)) {
        g_uart.printf("FATAL: Capture Error!\r\n");
        goto bad;
    }

    g_uart.printf("Starting FreeRTOS Scheduler...\r\n");
    
    vTaskStartScheduler();

bad:
    if (samplerToFilterQueue != NULL) {
        vQueueDelete(samplerToFilterQueue);
    }

    if (filterToDisplayerQueue != NULL) {
        vQueueDelete(filterToDisplayerQueue);
    }

    g_led_red.set(gpio::Pin::On);
    g_uart.printf("FATAL ERROR!\r\n");
    while (1) ;

    return (0);
}

/*******************************************************************************
 *
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */
void
halt(const char * const p_file, const unsigned p_line) {
    g_uart.printf("%s(): %s : %d\r\n", __func__, p_file, p_line);
    g_led_red.enable(gpio::GpioAccessViaSTM32F4::e_Output, gpio::GpioAccessViaSTM32F4::e_None, gpio::GpioAccessViaSTM32F4::e_Gpio);
    g_led_red.set(gpio::Pin::On);
    while (1) { };
}

void
assert_failed(uint8_t *p_file, uint32_t p_line) {
    halt(reinterpret_cast<char *>(p_file), p_line);
}

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined (__cplusplus) */

/*******************************************************************************
 * Interrupt Handlers 
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

void
ADC_IRQHandler(void) {
    adc.handleIrq();
}

void
DMA2_Stream0_IRQHandler(void) {
    adc_dmaStream.handleIrq();
}

void
SPI1_IRQHandler(void) {
    ws2812b_spibus.handleIrq();
}

void
DMA2_Stream2_IRQHandler(void) {
    ws2812b_spiRxDmaStream.handleIrq();
}

void
DMA1_Stream3_IRQHandler(void) {
    sr_spiRxDmaStream.handleIrq();
}

void
DMA1_Stream4_IRQHandler(void) {
    sr_spiTxDmaStream.handleIrq();
}

void
DMA2_Stream3_IRQHandler(void) {
    ws2812b_spiTxDmaStream.handleIrq();
}

void
FPU_IRQHandler(void) {
    halt(__FILE__, __LINE__);    
}

void
FPU_Init(void) {
    SCB->CPACR = 0xF << 20;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined (__cplusplus) */
