/*-
 * $Copyright$
-*/

#include "i2c/I2cBusFreeBSD.hpp"

#include <sys/types.h>
#include <sys/ioctl.h>
#include <dev/iicbus/iic.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

namespace i2c {

/*******************************************************************************
 *
 ******************************************************************************/
I2cBusFreeBSD::I2cBusFreeBSD(void) : fd(0) {

}

/*******************************************************************************
 *
 ******************************************************************************/
I2cBusFreeBSD::~I2cBusFreeBSD() {
    if (fd)
        close();
}

/*******************************************************************************
 *
 ******************************************************************************/
int
I2cBusFreeBSD::open(const char *p_filename) {
    if (!fd)
        fd = ::open(p_filename, O_RDWR);

    return (fd == 0 ? ENXIO : 0);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
I2cBusFreeBSD::close(void) {
    int rc = ::close(fd);
    fd = 0;
    return rc;
}

/*******************************************************************************
 *
 ******************************************************************************/
int
I2cBusFreeBSD::start(uint8_t p_addr, bool p_repeated) const {
    int rc = -1;
    struct iiccmd cmd;

    if (!fd)
        goto out;

    cmd.slave = p_addr;
    rc = ioctl(fd, p_repeated ? I2CRPTSTART : I2CSTART, &cmd);

out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
I2cBusFreeBSD::stop(void) const {
    int rc = -1;

    if (!fd)
        goto out;

    rc = ioctl(fd, I2CSTOP);

out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
I2cBusFreeBSD::read(uint8_t *p_data, bool p_ack) const {
    int rc = -1;
    struct iiccmd cmd;

    if (fd < 0)
        goto out;

    cmd.count = 1;
    cmd.last  = p_ack ? 0 : 1;
    cmd.buf   = (char *) p_data;
    rc = ioctl(fd, I2CREAD, &cmd);
    if (rc)
        fprintf(stderr, "ioctl(I2CREAD) failed with rc=%i\n", rc);

out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
I2cBusFreeBSD::write(uint8_t p_data) const {
    int rc = -1;
    struct iiccmd cmd;

    if (fd < 0)
        goto out;

    cmd.count = 1;
    cmd.buf   = (char *) &p_data;
    rc = ioctl(fd, I2CWRITE, &cmd);

out:
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
I2cBusFreeBSD::reset(void) const {
    int rc = -1;
    struct iiccmd cmd;

    if (fd < 0)
        goto out;

    /*
     * Man pages says argument is ignored, but indicates that an argument is
     * taken by the ioctl(2) call.
     */
    rc = ioctl(fd, I2CRSTCARD, &cmd);

out:
    return (rc);
}

} /* namespace i2c */
