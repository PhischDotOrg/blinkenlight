/*-
 * $Copyright$
-*/

#include <lpt/LptAccessLinux.hpp>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/ppdev.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#if !defined(__STDC_FORMAT_MACROS)
#error This code requires __STDC_FORMAT_MACROS to be defined!
#endif
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

namespace lpt {

/*******************************************************************************
 *
 ******************************************************************************/
LptAccessLinux::LptAccessLinux(void) : m_fd(-1) {
}

/*******************************************************************************
 *
 ******************************************************************************/
LptAccessLinux::~LptAccessLinux() {
    if (m_fd != -1)
        this->close();
}

/*******************************************************************************
 *
 ******************************************************************************/
int
LptAccessLinux::open(const char * const p_filename) {
    static const char * const default_filename = "/dev/parport0";
    const char * filename = p_filename;
    int rc = -1;

    if (filename == NULL)
        filename = default_filename;

    m_fd = ::open(filename, O_RDWR);
    if (m_fd == -1) {
        fprintf(stderr, "LptAccessLinux::open(%s) failed with rc=0x%i: %s\n",
          filename, errno, strerror(errno));
        rc = errno;
        goto out;
    }

    rc = ioctl(m_fd, PPCLAIM);
    if (rc == -1) {
        fprintf(stderr, "LptAccessLinux::open(): ioctl(PPCLAIM) failed "
          "with rc=%i: %s\n", errno, strerror(errno));
        rc = errno;
        goto out;
    }

    rc = 0;
out:
    if ((rc != 0) && (m_fd != -1))
        this->close();
    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
LptAccessLinux::close(void) {
    int rc = 0;
    if (m_fd != -1) {
        ioctl(m_fd, PPRELEASE);
        rc = ::close(m_fd);
        m_fd = -1;
    }
    return rc;
}

/*******************************************************************************
 *
 ******************************************************************************/
int
LptAccessLinux::setData(const uint8_t p_data) const {
    assert(m_fd != -1);

    int rc = ioctl(m_fd, PPWDATA, &p_data);
    if (rc != 0) {
        fprintf(stderr, "LptAccessLinux::setData(0x%.02" PRIx8 ") failed with "
          "errno=%i: %s\n", p_data, errno, strerror(errno));
        rc = errno;
    }

    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
LptAccessLinux::getData(uint8_t * const p_data) const {
    assert(m_fd != -1);
    assert(p_data != NULL);

    int rc = ioctl(m_fd, PPRDATA, p_data);
    if (rc != 0) {
        fprintf(stderr, "LptAccessLinux::getData() failed with  errno=%i: %s\n",
          errno, strerror(errno));
        rc = errno;
    }

    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
LptAccessLinux::getStatus(uint8_t * const p_data) const {
    assert(m_fd != -1);
    assert(p_data != NULL);

    int rc = ioctl(m_fd, PPRSTATUS, p_data);
    if (rc != 0) {
        fprintf(stderr, "LptAccessLinux::getStatus() failed with "
          "errno=%i: %s\n", errno, strerror(errno));
        rc = errno;
    }

    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
LptAccessLinux::setControl(const uint8_t p_data) const {
    assert(m_fd != -1);

    int rc = ioctl(m_fd, PPWCONTROL, &p_data);
    if (rc != 0) {
        fprintf(stderr, "LptAccessLinux::setControl(0x%.02" PRIx8 ") failed with "
          "errno=%i: %s\n", p_data, errno, strerror(errno));
        rc = errno;
    }

    return (rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
LptAccessLinux::getControl(uint8_t * const p_data) const {
    assert(m_fd != -1);
    assert(p_data != NULL);

    int rc = ioctl(m_fd, PPRCONTROL, p_data);
    if (rc != 0) {
        fprintf(stderr, "LptAccessLinux::getControl() failed with "
          "errno=%i: %s\n", errno, strerror(errno));
        rc = errno;
    }

    return (rc);
}

} /* namespace lpt */

