/*-
 * $Copyright$
-*/

#ifndef _LPT_ACCESS_LINUX_H_52f01cff_e7a3_49ec_ac02_d29648c337c7
#define _LPT_ACCESS_LINUX_H_52f01cff_e7a3_49ec_ac02_d29648c337c7

#include <stdint.h>

namespace lpt {

class LptAccessLinux {
private:
    int m_fd;
public:
    LptAccessLinux(void);
    ~LptAccessLinux();

    int open(const char * const p_filename);
    int close(void);

    int setData(const uint8_t p_data) const;
    int getData(uint8_t * const p_data) const;

    int getStatus(uint8_t * const p_data) const;
    int setControl(const uint8_t p_data) const;
    int getControl(uint8_t * const p_data) const;
};

} /* namespace lpt */

#endif /* _LPT_ACCESS_LINUX_H_52f01cff_e7a3_49ec_ac02_d29648c337c7 */