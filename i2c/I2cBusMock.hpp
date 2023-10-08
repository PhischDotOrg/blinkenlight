/*-
 * $Copyright$
-*/

#ifndef _I2C_BUS_MOCK_HPP_03f51a03_719d_4140_9539_be0cc125c9e2
#define _I2C_BUS_MOCK_HPP_03f51a03_719d_4140_9539_be0cc125c9e2

/*******************************************************************************
 * 
 ******************************************************************************/
#if defined(DEBUG_BUILD) && defined(GMOCK_FOUND)

#include <gmock/gmock.h>

namespace i2c {

class I2cBusMock {
public:
    MOCK_CONST_METHOD1(open, int(const char * const p_filename));
    MOCK_CONST_METHOD0(close, int(void));

    MOCK_CONST_METHOD2(start, int(const uint8_t p_addr, const bool p_repeated));
    MOCK_CONST_METHOD0(stop, int(void));
    MOCK_CONST_METHOD2(read, int(uint8_t * const p_data, const bool p_ack));
    MOCK_CONST_METHOD1(write, int(const uint8_t p_data));
    MOCK_CONST_METHOD0(reset, int(void));
};

} /* namespace i2c */
#else /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */
namespace i2c {
class I2cBusMock;
} /* namespace i2c */  
#endif /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */

#endif /* _I2C_BUS_MOCK_HPP_03f51a03_719d_4140_9539_be0cc125c9e2 */