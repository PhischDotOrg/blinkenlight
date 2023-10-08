/*-
 * $Copyright$
-*/
#ifndef _LPT_ACCESS_EMBEDDED_HPP_0d8da968_1832_46b5_bfd9_85b24622c616
#define _LPT_ACCESS_EMBEDDED_HPP_0d8da968_1832_46b5_bfd9_85b24622c616

#include <stdint.h>

namespace lpt {

class LptAccessEmbedded {
public:
    LptAccessEmbedded(void);
    ~LptAccessEmbedded();

    int open(const char * const p_filename);
    int close(void);

    int setData(const uint8_t p_data) const;
    int getData(uint8_t * const p_data) const;

    int getStatus(uint8_t * const p_data) const;
    int setControl(const uint8_t p_data) const;
    int getControl(uint8_t * const p_data) const;
};

} /* namespace lpt */

#endif /* _LPT_ACCESS_EMBEDDED_HPP_0d8da968_1832_46b5_bfd9_85b24622c616 */
