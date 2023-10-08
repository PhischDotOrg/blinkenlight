/*-
 * $Copyright$
-*/

#ifndef _IPC_MUTEX_FREERTOS_HPP_c5840793_efdd_4e50_bd8c_ec73024cb480
#define _IPC_MUTEX_FREERTOS_HPP_c5840793_efdd_4e50_bd8c_ec73024cb480

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/semphr.h"
#if defined(__cplusplus)
} /* extern "C" */
#endif /* defined(__cplusplus) */

namespace ipc {

/*!
 * @brief Mutex Class for a FreeRTOS context.
 *
 * This class provides a class interface for a recursive FreeRTOS Mutex.
 *
 * FreeRTOS is special in a way that a mutex can be created, but not aquired
 * before the FreeRTOS scheduler has been started. In order to allow code using
 * the MutexFreeRTOS class to be run before the scheduler has been started, this
 * class provides the MutexFreeRTOS::init() method. Prior to initalizing the
 * mutex, the lock and unlock operations are no-ops. Only when the mutex has
 * been properly initialized, the lock and unlock operations perform actual
 * mutex operations. The user must ensure that no calls to MutexFreeRTOS::lock()
 * are made between the call to MutexFreeRTOS::init() and starting the FreeRTOS
 * scheduler.
 */
class MutexFreeRTOS {
private:
    static const unsigned m_timeoutMs = 1000;
    void * m_mutex;
public:
    MutexFreeRTOS(void);
    ~MutexFreeRTOS();

    /*!
     * @brief Initializes the Mutex object.
     *
     * This method creates the underlying Mutex object within the FreeRTOS
     * context. Prior to having called this method, the MutexFreeRTOS::lock()
     * and MutexFreeRTOS::unlock() methods are essentially no-ops.
     */
    void init(void);

    /*!
     * @brief Attempts to aquire the Mutex.
     *
     * Attempts to aquire the Mutex with a maximum timeout of
     * MutexFreeRTOS::m_timeoutMs (milliseconds).
     *
     * Note that this method can be called prior to having initialized the Mutex
     * via MutexFreeRTOS::init(). However, the mutex will not actually be
     * aquired in that state.
     *
     * This is useful if you need to use generic code that utilizes this class
     * prior to starting the FreeRTOS task scheduler.
     */
    int lock(const TickType_t p_wait = portMAX_DELAY) const;

    /*!
     * @brief Releases the Mutex.
     *
     * Releases the Mutex.
     * 
     * Note that this method can be called prior to having initialized the Mutex
     * via MutexFreeRTOS::init(). However, the mutex will not actually be
     * released in that state.
     *
     * This is useful if you need to use generic code that utilizes this class
     * prior to starting the FreeRTOS task scheduler.
     */
    int unlock(void) const;
};

} /* namespace ipc */

#endif /* _IPC_MUTEX_FREERTOS_HPP_c5840793_efdd_4e50_bd8c_ec73024cb480 */
