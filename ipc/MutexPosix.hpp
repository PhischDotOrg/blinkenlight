/*-
 * $Copyright$
-*/

#ifndef _IPC_MUTEX_POSIX_HPP_9956937f_744a_4980_9798_0b91cb041695
#define _IPC_MUTEX_POSIX_HPP_9956937f_744a_4980_9798_0b91cb041695

namespace ipc {

class MutexPosix {
private:
    void * m_mutex;
public:
    MutexPosix(void);
    ~MutexPosix();
    
    int lock(void);
    int unlock(void);
};

} /* namespace ipc */

#endif /* _IPC_MUTEX_POSIX_HPP_9956937f_744a_4980_9798_0b91cb041695 */
