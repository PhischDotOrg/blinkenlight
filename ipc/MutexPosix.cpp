/*-
 * $Copyright$
-*/

#include <ipc/MutexPosix.hpp>
#include <assert.h>

#include "MutexPosix.hpp"

#include <pthread.h>

namespace ipc {

/*******************************************************************************
 * 
 ******************************************************************************/
MutexPosix::MutexPosix() : m_mutex(NULL) {
    m_mutex = new pthread_mutex_t;
    int rc = pthread_mutex_init(static_cast<pthread_mutex_t *>(m_mutex), NULL);
    assert(!rc);
}

/*******************************************************************************
 * 
 ******************************************************************************/
MutexPosix::~MutexPosix() {
    pthread_mutex_destroy(static_cast<pthread_mutex_t *>(m_mutex));
    delete static_cast<pthread_mutex_t *>(m_mutex);
}

/*******************************************************************************
 * 
 ******************************************************************************/
int
MutexPosix::lock() {
    return pthread_mutex_lock(static_cast<pthread_mutex_t *>(m_mutex));
}

/*******************************************************************************
 * 
 ******************************************************************************/
int
MutexPosix::unlock() {
    return pthread_mutex_unlock(static_cast<pthread_mutex_t *>(m_mutex));
}

} /* namespace ipc */
