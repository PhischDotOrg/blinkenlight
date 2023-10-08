/*-
 * $Copyright$
-*/

#ifndef _IPC_MUTEX_HPP_89c2c78f_f7b9_49f0_a18c_9ee0373b45c0
#define _IPC_MUTEX_HPP_89c2c78f_f7b9_49f0_a18c_9ee0373b45c0

#include <ipc/IpcEnv.hpp>

#include <ipc/MutexPosix.hpp>
#include <ipc/MutexFreeRTOS.hpp>

namespace ipc {

template<IpcEnv_t> struct MutexChoice;

template<> struct MutexChoice<Undefined> {
    typedef void m_type;
};

template<> struct MutexChoice<Posix> {
    typedef MutexPosix m_type;
};

template<> struct MutexChoice<FreeRTOS> {
    typedef MutexFreeRTOS m_type;
};

struct MutexT {
    typedef MutexChoice<IPC_ENV>::m_type m_type;
};

typedef MutexT::m_type Mutex;

} /* namespace ipc */

#endif /* _IPC_MUTEX_HPP_89c2c78f_f7b9_49f0_a18c_9ee0373b45c0 */
