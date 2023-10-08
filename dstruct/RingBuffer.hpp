/*-
 * $Copyright$
-*/

#ifndef _DSTRUCT_RINGBUF_HPP_cfcc7272_3185_4ae2_915d_7c884e1679d6
#define _DSTRUCT_RINGBUF_HPP_cfcc7272_3185_4ae2_915d_7c884e1679d6

#include <sys/types.h>
#include <stdint.h>

namespace dstruct {

class RingBuffer {
private:
    RingBuffer &operator=(const RingBuffer &p_obj);
    RingBuffer(const RingBuffer &p_obj);

    void * const    m_buffer;
    const size_t    m_length;

public:
    RingBuffer(void * const p_buffer, const size_t p_length);
    ~RingBuffer(void);
};

}; /* namespace dstruct */

#endif /* _DSTRUCT_RINGBUF_HPP_cfcc7272_3185_4ae2_915d_7c884e1679d6 */