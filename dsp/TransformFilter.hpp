/*-
 * $Copyright$
-*/

#ifndef _DSP_TRANSFORM_FILTER_HPP_f29ff93c_c3ea_4492_b357_4de369a6646e
#define _DSP_TRANSFORM_FILTER_HPP_f29ff93c_c3ea_4492_b357_4de369a6646e

namespace dsp {

namespace Filter {

template <typename InputIteratorT, typename OutputIteratorT, typename UnaryOperationT>
OutputIteratorT transform(InputIteratorT p_inputBegin,
                          InputIteratorT p_inputEnd,
                          OutputIteratorT p_result,
                          UnaryOperationT &p_operation);

template <typename InputIteratorT, typename OutputIteratorT, typename UnaryOperationT>
OutputIteratorT transform2(InputIteratorT p_inputBegin,
                          InputIteratorT p_inputEnd,
                          OutputIteratorT p_result,
                          UnaryOperationT &p_operation);

template<typename InputIteratorT, typename OperationT>
OperationT for_each(InputIteratorT p_inputBegin, InputIteratorT p_inputEnd, OperationT p_operation);

template<typename ArrayT, typename OperationT>
typename ArrayT::value_type
bandpass(const ArrayT &p_array, const unsigned p_center, const unsigned p_halfWidth, OperationT p_operation);

template<typename ArrayT, typename OperationT>
typename ArrayT::value_type
hipass(const ArrayT &p_array, const unsigned p_center, const unsigned p_halfWidth, OperationT p_operation);

#if 0
template <typename InputIteratorT, typename OutputIteratorT, typename UnaryOperationT>
OutputIteratorT transform(InputIteratorT p_inputBegin,
                          InputIteratorT p_inputEnd,
                          OutputIteratorT p_result,
                          UnaryOperationT &p_operation);

template <typename FirstInputIteratorT, typename SecondInputIteratorT, typename OutputIteratorT, typename BinaryOperationT>
OutputIteratorT transform(FirstInputIteratorT p_firstInputBegin,
                          FirstInputIteratorT p_firstIntputEnd,
                          SecondInputIteratorT p_secondInputBegin,
                          BinaryOperationT &p_result);
#endif
    
} /* namespace Filter */

} /* namespace dsp */

#include "TransformFilter.cpp"

#endif /* _DSP_TRANSFORM_FILTER_HPP_f29ff93c_c3ea_4492_b357_4de369a6646e */
