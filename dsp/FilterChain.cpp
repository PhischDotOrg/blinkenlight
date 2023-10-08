/*-
 * $Copyright
-*/

#ifndef _FILTER_CHAIN_CPP_c25f57ff_6c58_4791_a0ee_0d424fcebc3b
#define _FILTER_CHAIN_CPP_c25f57ff_6c58_4791_a0ee_0d424fcebc3b

#include <uart/UartDevice.hpp>
extern uart::UartDevice g_uart;

#include "FilterChain.hpp"

#include <dsp/Fft.hpp>
#include <dsp/TransformFilter.hpp>
#include <dsp/WindowFunction.hpp>

#include <algorithm>

/*******************************************************************************
 *
 ******************************************************************************/
template<typename FftObjectT, typename FftBufferT, typename AmplitudesBufferT>
template<typename InputBufferT, typename OutputBufferT>
void
FilterChainT<FftObjectT, FftBufferT, AmplitudesBufferT>::filter(InputBufferT &p_input, OutputBufferT &p_output) {
    const unsigned nBands = OutputBufferT::SIZE;

    /* Apply Window Function to Samples */
    for (unsigned idx = 0; idx < InputBufferT::SIZE; idx++) {
        /*
         * This line does more than just calling the window function. First,
         * it "normalizes" the p_rawSample around zero: The ADC has an offset of
         * 1/2 Vdd which means the p_rawSample value will oscillate around 128.
         * 
         * Second, the call converts the normalized sample to a float (or whatever
         * the FftBufferT::value_type::value_type is). This is done because
         * otherwise the trick with subtracting 128 from the does not work.
         */
        typedef typename FftBufferT::value_type::value_type float_t;
        float_t value = (static_cast<float_t>(p_input[idx]) - 128) / 128.0f;
        this->m_fftBuffer[idx] = this->m_windowFunction.getFactor(idx) * value;
    }
    
    /* Perform FFT on (windowed) Samples */
    this->m_fftObject.applyFft(this->m_fftBuffer);

    /*
     * Calculate the squared norm of half the samples. The FFT input was all real,
     * so the upper half of the spectrum will just be a mirrored copy. Using the
     * squared norm of the samples will save ourselves from calculating the
     * sqrt() on the vector.
     */
    dsp::Filter::transform(
            this->m_fftBuffer.begin(),
            this->m_fftBuffer.begin() + (this->m_fftBuffer.SIZE / 2),
            this->m_amplitudes.begin(),
            SquaredNormFunction
    );

    /* "Low-pass" Filter in 0-th Band. May contain DC Components of Signal */
    p_output[0] = m_amplitudes[0];

    /* Lowest Bandpass Filter is single band only */
    p_output[1] = m_amplitudes[1];

    /*
     * Band Pass Filters; total number of filters is nBands - 3 as first band
     * pass was done above.
     */
    p_output[2] = this->bandpass<2>(this->m_bandpass2);
    p_output[3] = this->bandpass<3>(this->m_bandpass3);
    p_output[4] = this->bandpass<4>(this->m_bandpass4);
    p_output[5] = this->bandpass<5>(this->m_bandpass5);
    p_output[6] = this->bandpass<6>(this->m_bandpass6);
    p_output[7] = this->bandpass<7>(this->m_bandpass7);
    p_output[8] = this->bandpass<8>(this->m_bandpass8);

    /* Last filter Band is Hi-Pass Filter */
    p_output[nBands - 1] = dsp::Filter::hipass(this->m_amplitudes, AmplitudesBufferT::SIZE - 1, AmplitudesBufferT::SIZE/2, FilterWindowFunction< AmplitudesBufferT::SIZE/2>);
}

#endif /* _FILTER_CHAIN_CPP_c25f57ff_6c58_4791_a0ee_0d424fcebc3b */
