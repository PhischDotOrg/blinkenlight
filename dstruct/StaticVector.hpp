/*-
 * $Copyright$
-*/

#ifndef _DSTRUCT_STATIC_VECTOR_HPP_ed1271ef_e84d_44f0_b7ef_9f591e4563b9
#define _DSTRUCT_STATIC_VECTOR_HPP_ed1271ef_e84d_44f0_b7ef_9f591e4563b9

#include <sys/types.h>

namespace dstruct {

template<typename ValueT, unsigned t_size>
class StaticVectorT {
public:
    typedef ValueT * iterator;
    typedef const ValueT * const_iterator;

    typedef ValueT & reference;
    typedef const ValueT & const_reference;

    typedef ValueT value_type;
    typedef const ValueT const_value;
    
    StaticVectorT(void);
    virtual ~StaticVectorT();

    ValueT *data(void) { return this->m_data; }
    const ValueT *data(void) const { return this->m_data; }

    static const size_t SIZE = t_size;
    static size_t size() { return SIZE; }

    iterator begin() { return this->m_data; }
    const_iterator begin() const { return const_cast<StaticVectorT *>(this)->begin(); }

    iterator end() { return this->m_data + t_size; }
    const_iterator end() const { return const_cast<StaticVectorT *>(this)->end(); }
    
    reference operator[] (unsigned idx) { return this->m_data[idx]; }
    const_reference operator[] (unsigned idx) const { return const_cast<StaticVectorT *>(this)->operator[](idx); }

private:
    StaticVectorT(const StaticVectorT &);
    
    ValueT  m_data[t_size];
}; /* class StaticVectorT */

} /* namespace dstruct */

#include "StaticVector.cpp"

#endif /* _DSTRUCT_STATIC_VECTOR_HPP_ed1271ef_e84d_44f0_b7ef_9f591e4563b9 */
