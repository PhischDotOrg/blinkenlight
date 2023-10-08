/*-
 * $Copyright$
-*/

#ifndef _DSTRUCT_LOCKABLE_VECTOR_CPP_b757e8cf_4635_4613_b241_bcb677e3a134
#define _DSTRUCT_LOCKABLE_VECTOR_CPP_b757e8cf_4635_4613_b241_bcb677e3a134

#include "LockableVector.hpp"

namespace dstruct {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename ValueT, unsigned t_size, typename MutexT>
LockableVectorT<ValueT, t_size, MutexT>::LockableVectorT(void) {
    
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename ValueT, unsigned t_size, typename MutexT>
LockableVectorT<ValueT, t_size, MutexT>::~LockableVectorT() {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename ValueT, unsigned t_size, typename MutexT>
int
LockableVectorT<ValueT, t_size, MutexT>::lock(void) {
    return m_mutex.lock(0);
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename ValueT, unsigned t_size, typename MutexT>
int
LockableVectorT<ValueT, t_size, MutexT>::unlock(void) {
    return m_mutex.unlock();
}

} /* namespace dstruct */

#endif /* _DSTRUCT_LOCKABLE_VECTOR_CPP_b757e8cf_4635_4613_b241_bcb677e3a134 */

