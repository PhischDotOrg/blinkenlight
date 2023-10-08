/*-
 * $Copyright$
-*/

#ifndef __I2C_I2CBUSFREEBSD_HPP
#define __I2C_I2CBUSFREEBSD_HPP

#include <sys/types.h>
#include <stdint.h>

/*******************************************************************************
 *
 ******************************************************************************/
namespace i2c {

class I2cBusFreeBSD {
private:
    int             fd;

public:
    I2cBusFreeBSD();
    ~I2cBusFreeBSD();

    int open(const char * const p_filename);
    int close(void);

    int start(const uint8_t p_addr, const bool p_repeated) const;
    int stop(void) const;
    int read(uint8_t * const p_data, const bool p_ack) const;
    int write(const uint8_t p_data) const;

    int reset(void) const;
};

} /* namespace i2c */

#endif /* __I2C_I2CBUSFREEBSD_HPP */

