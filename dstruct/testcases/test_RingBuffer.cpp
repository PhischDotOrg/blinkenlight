/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>
#include <dstruct/RingBuffer.hpp>

namespace dstruct {

/*******************************************************************************
 *
 ******************************************************************************/
class RingBufferTest : public ::testing::Test {
protected:
    uint8_t         m_buffer[256];
    RingBuffer *    m_obj;

public:
    RingBufferTest(void) : m_obj(NULL) {
        m_obj = new RingBuffer(m_buffer, sizeof(m_buffer));
    }

    virtual ~RingBufferTest() {
        delete m_obj;
    }
};

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(RingBufferTest, CreateAndDelete) {

}

} /* namespace dstruct */
