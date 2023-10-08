/*-
 * $Copyright$
-*/

#ifndef _DSTRUCT_LOCKABLE_VECTOR_HPP_ee5161d6_929a_4a87_954f_b1a39d0dd727
#define _DSTRUCT_LOCKABLE_VECTOR_HPP_ee5161d6_929a_4a87_954f_b1a39d0dd727

#include <dstruct/StaticVector.hpp>
#include <ipc/Mutex.hpp>

namespace dstruct {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename ValueT, unsigned t_size, typename MutexT = ipc::Mutex>
class LockableVectorT : public StaticVectorT<ValueT, t_size> {
    friend class LockableVectorTest;
public:
    LockableVectorT(void);
    virtual ~LockableVectorT();

    int lock(void);
    int unlock(void);

private:
    LockableVectorT(const LockableVectorT &);
    
    MutexT m_mutex;
}; 

} /* namespace dstruct */

#include "LockableVector.cpp"

#endif /* _DSTRUCT_LOCKABLE_VECTOR_HPP_ee5161d6_929a_4a87_954f_b1a39d0dd727 */
