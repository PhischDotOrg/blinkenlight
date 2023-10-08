/*-
 * $Copyright$
-*/

#ifndef _DSP_BITREVERSAL_HPP_9644e07e_d901_4f72_b9a7_4b422a686442
#define _DSP_BITREVERSAL_HPP_9644e07e_d901_4f72_b9a7_4b422a686442

#include <dsp/BitReversal.hpp>

namespace dsp {

template<const unsigned t_numBits> typename BitReversalT<t_numBits>::Vector_t BitReversalT<t_numBits>::m_masks[t_numBits];

/*******************************************************************************
 *
 ******************************************************************************/
template<const unsigned t_numBits>
BitReversalT<t_numBits>::BitReversalT(void) {
    for (unsigned bit = 0; bit < t_numBits; bit++) {
        this->m_masks[bit] = calculateMask(bit);
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
template<const unsigned t_numBits>
BitReversalT<t_numBits>::~BitReversalT() {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<const unsigned t_numBits>
unsigned
BitReversalT<t_numBits>::getReverse(const unsigned p_Index) const {
    unsigned ridx = 0;
    for (unsigned bit = 0; bit < t_numBits; bit++) {
        if (p_Index & m_masks[bit]) {
            ridx += (1 << (t_numBits - (bit + 1)));
        }
    }
    return ridx;
}

} /* namespace dsp */

#endif /* _DSP_BITREVERSAL_HPP_9644e07e_d901_4f72_b9a7_4b422a686442 */
