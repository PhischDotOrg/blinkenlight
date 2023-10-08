/*-
 * $Copyright$
-*/

#include "i2c/I2cBusDarwin.hpp"

#if defined(__cplusplus)
#if !defined(__STDC_FORMAT_MACROS)
#error This code requires __STDC_FORMAT_MACROS to be defined!
#endif /* !defined(__STDC_FORMAT_MACROS) */
#endif /* defined(__cplusplus) */
#include <inttypes.h>

#include <stdio.h>

namespace i2c {

/*******************************************************************************
 * 
 ******************************************************************************/
I2cBusDarwin::I2cBusDarwin(void) {
}

/*******************************************************************************
 * 
 ******************************************************************************/
I2cBusDarwin::~I2cBusDarwin() {
}

/*******************************************************************************
 * 
 ******************************************************************************/
int
I2cBusDarwin::reset(void) const {
    return (0);
}

/*******************************************************************************
 * 
 ******************************************************************************/
int
I2cBusDarwin::start(const uint8_t /* p_addr */, const bool /* p_repeated */) const {
    return (0);
};

/*******************************************************************************
 * 
 ******************************************************************************/
int
I2cBusDarwin::stop(void) const {
    return (0);
}

/*******************************************************************************
 * 
 ******************************************************************************/
int
I2cBusDarwin::read(uint8_t * const /* p_data */, const bool /* p_ack */) const {
    return (0);
}

/*******************************************************************************
 * 
 ******************************************************************************/
int
I2cBusDarwin::write(const uint8_t /* p_data */) const {
    return (0);
}

/*******************************************************************************
 * 
 ******************************************************************************/
int
I2cBusDarwin::open(const char * const /* p_filename */) {
    return (0);
}

/*******************************************************************************
 * 
 ******************************************************************************/
int
I2cBusDarwin::close(void) {
    return (0);
}

} /* namespace i2c */

