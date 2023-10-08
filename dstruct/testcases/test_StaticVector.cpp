/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>
#include <dstruct/StaticVector.hpp>

#include <stdint.h>

namespace dstruct {

/*******************************************************************************
 *
 ******************************************************************************/
class StaticVectorTest : public ::testing::Test {
protected:
    typedef uint8_t value_t;
    static const unsigned m_size = 16;
    typedef StaticVectorT<value_t, m_size> StaticVector;
    
    StaticVector *m_obj;
    
public:
    StaticVectorTest(void) : m_obj(NULL) {
        m_obj = new StaticVector();
    }

    virtual ~StaticVectorTest() {
        delete m_obj;
    }
};

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(StaticVectorTest, CreateAndDelete) {

}

} /* namespace dstruct */
