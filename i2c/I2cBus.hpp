/*-
 * $Copyright$
-*/

#ifndef __I2C_I2CBUSDRIVER_HPP
#define __I2C_I2CBUSDRIVER_HPP

#include <stddef.h>
#include <stdint.h>

#include <i2c/I2cBusDarwin.hpp>
#include <i2c/I2cBusFreeBSD.hpp>
#include <i2c/I2cBusLinux.hpp>
#include <i2c/I2cBusMock.hpp>
#include <i2c/I2cBusViaGpio.hpp>

/*******************************************************************************
 * 
 ******************************************************************************/
#if !defined(IIC_ENV)
#define IIC_ENV Undefined
#endif

namespace i2c {

typedef enum I2cBusDriverImpl_e {
    Undefined,
    Darwin,
    Embedded,
    FreeBSD,
    Gpio,
    GTest,
    Linux
} I2cBusDriverImpl_t;

template<I2cBusDriverImpl_t> struct I2cBusDriverChoice;

template<> struct I2cBusDriverChoice<Undefined> {
    typedef void m_type;
};

template<> struct I2cBusDriverChoice<Darwin> {
    typedef I2cBusDarwin m_type;
};

template<> struct I2cBusDriverChoice<Embedded> {
    typedef I2cBusLinux m_type;
};

template<> struct I2cBusDriverChoice<FreeBSD> {
    typedef I2cBusFreeBSD m_type;
};

template<> struct I2cBusDriverChoice<Gpio> {
    typedef I2cBusViaGpioT< typename gpio::GpioPin > m_type;
};

template<> struct I2cBusDriverChoice<GTest> {
    typedef I2cBusMock m_type;
};

template<> struct I2cBusDriverChoice<Linux> {
    typedef I2cBusLinux m_type;
};

struct I2cBusDriverT {
    typedef I2cBusDriverChoice<IIC_ENV>::m_type m_type;
};

typedef I2cBusDriverT::m_type I2cBus;

} /* namespace i2c */

#endif /* __I2C_I2CBUSDRIVER_HPP */
