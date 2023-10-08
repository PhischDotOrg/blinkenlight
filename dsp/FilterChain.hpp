/*-
 * $Copyright
-*/
#ifndef _FILTER_CHAIN_HPP_bd99eb73_5112_484b_8047_12bf175bdc55
#define _FILTER_CHAIN_HPP_bd99eb73_5112_484b_8047_12bf175bdc55

#include <dsp/WindowFunction.hpp>

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T, const unsigned t_Width>
class WindowFunctionT {
private:
    T   m_factors[t_Width];

public:
    template<typename OperationT>
    void
    initialize(OperationT p_operation) {
        for (unsigned idx = 0; idx < t_Width; idx++) {
            m_factors[idx] = p_operation(idx);
        }
    }
    
    T
    getFactor(const unsigned int p_idx) const {
        return this->m_factors[p_idx];
    }
    
    typedef T value_type;
};

#define FILTER_WINDOW_WIDTH(_f) ((2 * (1 << (((_f) - 1) - 1))) + 3)

/*******************************************************************************
 *
 ******************************************************************************/
template<typename FftObjectT, typename FftBufferT, typename AmplitudesBufferT>
class FilterChainT {
public:
    FilterChainT(FftObjectT &p_fftObject) : m_fftObject(p_fftObject) {
        m_windowFunction.initialize(dsp::WindowFunction::CosineFactorT<typename FftBufferT::value_type::value_type, FftBufferT::SIZE>);

        m_bandpass2.initialize(dsp::WindowFunction::HannFactorT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(2)>);
        m_bandpass3.initialize(dsp::WindowFunction::HannFactorT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(3)>);
        m_bandpass4.initialize(dsp::WindowFunction::HannFactorT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(4)>);
        m_bandpass5.initialize(dsp::WindowFunction::HannFactorT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(5)>);
        m_bandpass6.initialize(dsp::WindowFunction::HannFactorT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(6)>);
        m_bandpass7.initialize(dsp::WindowFunction::HannFactorT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(7)>);
        m_bandpass8.initialize(dsp::WindowFunction::HannFactorT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(8)>);
    }

    ~FilterChainT() {
    }
    
    template<typename InputBufferT, typename OutputBufferT>
    void
    filter(InputBufferT &p_input, OutputBufferT &p_output);

private:
    WindowFunctionT<typename FftBufferT::value_type::value_type, FftBufferT::SIZE>  m_windowFunction;

    WindowFunctionT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(2)> m_bandpass2;
    WindowFunctionT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(3)> m_bandpass3;
    WindowFunctionT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(4)> m_bandpass4;
    WindowFunctionT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(5)> m_bandpass5;
    WindowFunctionT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(6)> m_bandpass6;
    WindowFunctionT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(7)> m_bandpass7;
    WindowFunctionT<typename AmplitudesBufferT::value_type, FILTER_WINDOW_WIDTH(8)> m_bandpass8;

    template<unsigned t_Filter>
    unsigned
    getFilterCenter(void) const {
        return (1 << (t_Filter - 1));
    }

    template<unsigned t_Filter>
    unsigned
    getFilterHalfWidth(void) const {
        return (1 << ((t_Filter - 1) - 1));
    }

    template<unsigned t_WindowWidth>
    static
    typename AmplitudesBufferT::value_type
    FilterWindowFunction(const unsigned p_idx) {
        return dsp::WindowFunction::HannFactorT<typename AmplitudesBufferT::value_type, t_WindowWidth>(p_idx);
    }

    static
    typename AmplitudesBufferT::value_type
    SquaredNormFunction(const typename FftBufferT::value_type &p_sample) {
        return p_sample.abs2();
    }

    template<unsigned n, typename WindowFunctionT>
    typename WindowFunctionT::value_type
    bandpass(const WindowFunctionT &p_window) {
        static const unsigned center = this->getFilterCenter<n>();
        static const unsigned halfWidth = this->getFilterHalfWidth<n>();
        
        typename WindowFunctionT::value_type value = 0;
        
        const unsigned len = (2 * halfWidth) + 1;
        const unsigned left = center - halfWidth;

        for (unsigned idx = 0; idx < len; idx++) {
            value +=  this->m_amplitudes[left + idx] * p_window.getFactor(1 + idx);
        }

        return value;
    }

public:
    FftObjectT &        m_fftObject;
    FftBufferT          m_fftBuffer;
    AmplitudesBufferT   m_amplitudes;
};

#include "FilterChain.cpp"

#endif /* _FILTER_CHAIN_HPP_bd99eb73_5112_484b_8047_12bf175bdc55 */
