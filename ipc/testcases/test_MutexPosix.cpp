/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>
#include <ipc/MutexPosix.hpp>

#include <stdint.h>

namespace ipc {

/*******************************************************************************
 *
 ******************************************************************************/
class MutexPosixTest : public ::testing::Test {
protected:
    MutexPosix *m_obj;
    
public:
    MutexPosixTest(void) : m_obj(NULL) {
        m_obj = new MutexPosix();
    }

    virtual ~MutexPosixTest() {
        delete m_obj;
    }
};

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(MutexPosixTest, CreateAndDelete) {

}

} /* namespace dstruct */
