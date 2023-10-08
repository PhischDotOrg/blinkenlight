/*-
 * $Copyright$
-*/

#ifndef _LPT_ACCESS_MOCK_HPP_3f3dc7f3_2a43_4e8b_a562_cf5bccaab6ba
#define _LPT_ACCESS_MOCK_HPP_3f3dc7f3_2a43_4e8b_a562_cf5bccaab6ba

/*******************************************************************************
 * 
 ******************************************************************************/
#if defined(DEBUG_BUILD) && defined(GMOCK_FOUND)

#include <gmock/gmock.h>

namespace lpt {

class LptAccessMock {
public:
    MOCK_CONST_METHOD1(open, int(const char * const p_filename));
    MOCK_CONST_METHOD0(close, int(void));

    MOCK_CONST_METHOD1(setData, int(const uint8_t p_data));
    MOCK_CONST_METHOD1(getData, int(uint8_t * const p_data));

    MOCK_CONST_METHOD1(getStatus, int(uint8_t * const p_data));
    MOCK_CONST_METHOD1(setControl, int(const uint8_t p_data));
    MOCK_CONST_METHOD1(getControl, int(uint8_t * const p_data));
};

} /* namespace lpt */
#else /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */
namespace lpt {
    class LptAccessMock;
} /* namespace lpt */
#endif /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */

#endif /* _LPT_ACCESS_MOCK_HPP_3f3dc7f3_2a43_4e8b_a562_cf5bccaab6ba */
