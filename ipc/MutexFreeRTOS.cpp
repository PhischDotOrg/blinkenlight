/*-
 * $Copyright$
-*/

#include <ipc/MutexFreeRTOS.hpp>

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/semphr.h"

#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */

#include <assert.h>

namespace ipc {

/*******************************************************************************
 *
 ******************************************************************************/
MutexFreeRTOS::MutexFreeRTOS(void) : m_mutex(NULL) {
    m_mutex = xSemaphoreCreateRecursiveMutex();
}

/*******************************************************************************
 *
 ******************************************************************************/
MutexFreeRTOS::~MutexFreeRTOS() {
    vSemaphoreDelete(m_mutex);
}

/*******************************************************************************
 *
 ******************************************************************************/
int
MutexFreeRTOS::lock(const TickType_t p_wait /* = portMAX_DELAY */) const {
    return xSemaphoreTakeRecursive(m_mutex, p_wait) == pdTRUE ? 0 : -1;
}

/*******************************************************************************
 *
 ******************************************************************************/
int
MutexFreeRTOS::unlock() const {
    return xSemaphoreGiveRecursive(m_mutex) == pdTRUE ? 0 : -1;
}

} /* namespace ipc */
