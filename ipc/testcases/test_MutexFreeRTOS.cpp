/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>
#include <ipc/MutexFreeRTOS.hpp>

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/task.h>
    
void vApplicationTickHook(void) {};
void vApplicationStackOverflowHook(TaskHandle_t /* xTask */, char * /* pcTaskName */) {};
void vApplicationIdleHook(void) {};
void vApplicationMallocFailedHook(void) {};

unsigned char ucHeap[configTOTAL_HEAP_SIZE];

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */

namespace ipc {

/*******************************************************************************
 *
 ******************************************************************************/
class MutexFreeRTOSTest : public ::testing::Test {
protected:
    MutexFreeRTOS *m_obj;
    
public:
    MutexFreeRTOSTest(void) : m_obj(NULL) {
        m_obj = new MutexFreeRTOS();
    }

    virtual ~MutexFreeRTOSTest() {
        delete m_obj;
    }
};

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(MutexFreeRTOSTest, CreateAndDelete) {

}

/*******************************************************************************
 * 
 ******************************************************************************/
TEST_F(MutexFreeRTOSTest, LockAndUnlock) {
    EXPECT_EQ(0, m_obj->lock());
    EXPECT_EQ(0, m_obj->unlock());
}

} /* namespace dstruct */
