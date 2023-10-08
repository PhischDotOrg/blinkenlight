/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>
#include <dstruct/LockableVector.hpp>

#include <stdint.h>

using ::testing::Return;

namespace dstruct {

/*******************************************************************************
 *
 ******************************************************************************/
class LockMock {
public:
    MOCK_METHOD0(lock, int());
    MOCK_METHOD0(unlock, int());
};

/*******************************************************************************
 *
 ******************************************************************************/
class LockableVectorTest : public ::testing::Test {
protected:
    typedef uint8_t value_t;
    static const unsigned m_size = 16;
    typedef LockableVectorT<value_t, m_size, LockMock> LockableVector;
    
    
    LockableVector *m_obj;
    LockMock       *m_lock;

public:
    LockableVectorTest(void) : m_obj(NULL) {
        m_obj = new LockableVector();
        m_lock = &m_obj->m_mutex;
    }

    virtual ~LockableVectorTest() {
        delete m_obj;
    }
};

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(LockableVectorTest, CreateAndDelete) {

}

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(LockableVectorTest, Lock) {
    EXPECT_CALL(*m_lock, lock()).Times(1).WillOnce(Return(0));
    EXPECT_EQ(0, m_obj->lock());
}

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(LockableVectorTest, LockWithError) {
    int err = 0x4711;

    EXPECT_CALL(*m_lock, lock()).Times(1).WillOnce(Return(err));
    EXPECT_EQ(err, m_obj->lock());
}

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(LockableVectorTest, Unlock) {
    EXPECT_CALL(*m_lock, unlock()).Times(1).WillOnce(Return(0));
    EXPECT_EQ(0, m_obj->unlock());
}

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(LockableVectorTest, UnlockWithError) {
    int err = 0x4711;
    
    EXPECT_CALL(*m_lock, unlock()).Times(1).WillOnce(Return(err));
    EXPECT_EQ(err, m_obj->unlock());
}

} /* namespace dstruct */
