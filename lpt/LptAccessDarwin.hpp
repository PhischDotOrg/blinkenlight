/*-
 * $Copyright$
-*/

#ifndef _LPT_ACCESS_DARWIN_H_2A6F5D09_FFE8_4258_A298_83C7F33855D8
#define _LPT_ACCESS_DARWIN_H_2A6F5D09_FFE8_4258_A298_83C7F33855D8

#include <stdint.h>

namespace lpt {

class LptAccessDarwin {
private:
    int m_fd;
public:
    LptAccessDarwin(void);
    ~LptAccessDarwin();

    int open(const char * const p_filename);
    int close(void);

    int setData(const uint8_t p_data) const;
    int getData(uint8_t * const p_data) const;
    int getStatus(uint8_t * const p_data) const;
    int setControl(const uint8_t p_data) const;
    int getControl(uint8_t * const p_data) const;
};

} /* namespace lpt */

#endif /* _LPT_ACCESS_DARWIN_H_2A6F5D09_FFE8_4258_A298_83C7F33855D8 */

