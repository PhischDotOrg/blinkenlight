/*-
 * $Copyright$
-*/

#ifndef _LPT_ACCESS_FREEBSD_HPP_c2a12e05_2787_4267_9d33_40b125d6d81c
#define _LPT_ACCESS_FREEBSD_HPP_c2a12e05_2787_4267_9d33_40b125d6d81c

#include <stdint.h>

namespace lpt {

class LptAccessFreeBSD {
private:
    int m_fd;
public:
    LptAccessFreeBSD(void);
    ~LptAccessFreeBSD();

    int open(const char * const p_filename);
    int close(void);

    int setData(const uint8_t p_data) const;
    int getData(uint8_t * const p_data) const;

    int getStatus(uint8_t * const p_data) const;
    int setControl(const uint8_t p_data) const;
    int getControl(uint8_t * const p_data) const;
};

} /* namespace lpt */

#endif /* _LPT_ACCESS_FREEBSD_HPP_c2a12e05_2787_4267_9d33_40b125d6d81c */
