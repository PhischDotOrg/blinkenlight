/*-
 * $Copyright$
-*/

#ifndef _DSP_TRANSFORM_FILTER_CPP_1b093994_cd21_40da_97d6_543d5ab243e8
#define _DSP_TRANSFORM_FILTER_CPP_1b093994_cd21_40da_97d6_543d5ab243e8

#include <dsp/TransformFilter.hpp>

namespace dsp {
    namespace Filter {

/*******************************************************************************
 *
 ******************************************************************************/
template <typename InputIteratorT, typename OutputIteratorT, typename UnaryOperationT>
OutputIteratorT
transform(InputIteratorT p_inputBegin, InputIteratorT p_inputEnd, OutputIteratorT p_result, UnaryOperationT &p_operation) {
    for (unsigned idx = 0; p_inputBegin != p_inputEnd; idx++, p_inputBegin++, p_result++) {
        *p_result = p_operation(*p_inputBegin);
    }
    return p_result;
}

/*******************************************************************************
 *
 ******************************************************************************/
template <typename InputIteratorT, typename OutputIteratorT, typename UnaryOperationT>
OutputIteratorT
transform2(InputIteratorT p_inputBegin, InputIteratorT p_inputEnd, OutputIteratorT p_result, UnaryOperationT &p_operation) {
    for (unsigned idx = 0; p_inputBegin != p_inputEnd; idx++, p_inputBegin++, p_result++) {
        *p_result = p_operation(*p_inputBegin, idx);
    }
    return p_result;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename InputIteratorT, typename OperationT>
OperationT
for_each(InputIteratorT p_inputBegin, InputIteratorT p_inputEnd, OperationT p_operation) {
    for ( ; p_inputBegin != p_inputEnd; p_inputBegin++) {
        *p_inputBegin = p_operation(*p_inputBegin);
    }

    return p_operation;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename ArrayT, typename OperationT>
typename ArrayT::value_type
bandpass(const ArrayT &p_array, const unsigned p_center, const unsigned p_halfWidth, OperationT p_operation) {
    typename ArrayT::value_type value = 0;
    const unsigned len = (2 * p_halfWidth) + 1;
    const unsigned left = p_center - p_halfWidth;

    for (unsigned idx = 0; idx < len; idx++) {
        value +=  p_array[left + idx] * p_operation(1 + idx);
    }

    return value;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename ArrayT, typename OperationT>
typename ArrayT::value_type
hipass(const ArrayT &p_array, const unsigned p_center, const unsigned p_halfWidth, OperationT p_operation) {
    typename ArrayT::value_type value = 0;
    const unsigned len = p_halfWidth;
    const unsigned left = p_center - p_halfWidth;

    for (unsigned idx = 0; idx < len; idx++) {
        value +=  p_array[left + idx] * p_operation(1 + idx);
    }
    
    return value;
}

    } /* namespace Filter */
} /* namespace dsp */

#endif /* _DSP_TRANSFORM_FILTER_CPP_1b093994_cd21_40da_97d6_543d5ab243e8 */

