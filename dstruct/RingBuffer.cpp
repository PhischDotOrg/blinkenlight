/*-
 * $Copyright$
-*/

#include <dstruct/RingBuffer.hpp>

namespace dstruct {

/*******************************************************************************
 *
 ******************************************************************************/
RingBuffer::RingBuffer(void * const p_buffer, const size_t p_length)
  : m_buffer(p_buffer), m_length(p_length) {
}

/*******************************************************************************
 *
 ******************************************************************************/
RingBuffer::~RingBuffer(void) {

}

} /* namespace dstruct */
