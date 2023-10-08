/*-
 * $Copyright$
-*/

#ifndef _DSP_BITREVERSAL_HPP_96B2BA85_B702_437B_B972_1C3E84654597
#define _DSP_BITREVERSAL_HPP_96B2BA85_B702_437B_B972_1C3E84654597

#include <stdint.h>
#include <stddef.h>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
namespace BitReversalTemplates {

#if !defined(DOXYGEN)
    /*
     * Template Meta-Programming Example from Wikibooks, via URL below on July 13th, 2013:
     *   http://en.wikibooks.org/wiki/C%2B%2B_Programming/Templates/Template_Meta-Programming#Example:_Compile-time_.22If.22
     *
     * This code is used to determine the width of the parameters to the write() and
     * read() methods below.
     */
    template <bool Condition, typename TrueResult, typename FalseResult>
    struct if_;

    template <typename TrueResult, typename FalseResult>
    struct if_<true, TrueResult, FalseResult>
    {
      typedef TrueResult m_result;
    };

    template <typename TrueResult, typename FalseResult>
    struct if_<false, TrueResult, FalseResult>
    {
      typedef FalseResult m_result;
    };

    template<unsigned t_numBits> struct VectorChoiceT {
        typedef typename if_<(t_numBits > sizeof(uint8_t) * 8),
            typename if_<(t_numBits > sizeof(uint16_t) * 8),
              typename if_<(t_numBits > sizeof(uint32_t) * 8),
                typename if_<(t_numBits > sizeof(uint64_t) * 8),
                  uint32_t[(t_numBits + 31) / 32], uint64_t>::m_result,
              uint32_t>::m_result,
            uint16_t>::m_result,
          uint8_t>::m_result Vector_t;
    };
#endif /* !defined(DOXYGEN) */
} /* namespace BitReversalTemplates */

template<const unsigned t_numBits>
class BitReversalT {
private:
#if defined(DOXYGEN)
    /*!
     * @brief Container for Pixels in a single Column.
     * 
     * The type \c ColVector_t is defined as an unsigned integer type that can
     * hold at least \c t_height bits.
     */
    typedef unsigned Vector_t;

    /*!
     * @brief Container for Pixels in a single Row.
     * 
     * The type \c RowVector_t is defined as an unsigned integer type that can
     * hold at least \c t_width bits.
     */
    typedef unsigned Vector_t;
#else
    typedef typename BitReversalTemplates::VectorChoiceT<t_numBits>::Vector_t Vector_t;
#endif /* defined(DOXYGEN) */
    static Vector_t m_masks[t_numBits];

public:
    BitReversalT(void);
    ~BitReversalT();

    constexpr Vector_t calculateMask(const unsigned p_Bit) const {
        return (1 << p_Bit);
    }

    unsigned getReverse(const unsigned p_Index) const;
};

} /* namespace dsp */

#include "BitReversal.cpp"

#endif /* _DSP_BITREVERSAL_HPP_96B2BA85_B702_437B_B972_1C3E84654597 */
