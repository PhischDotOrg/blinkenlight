/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <dsp/Sine.hpp>
#include <dsp/Sine.cpp>
#include <dsp/BitReversal.hpp>
#include <dsp/Fft.hpp>

#include <kiss_fft.h>

#include <dsp/Complex.hpp>

#include <stdint.h>
#include <math.h>

#if defined(HAVE_FFTW)
#include <fftw3.h>
#endif /* defined(HAVE_FFTW) */

#include <complex>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
class FftTest : public ::testing::Test {
public:
    typedef dsp::ComplexT<float> Complex;
//    typedef std::complex<float> Complex;
    
    FftTest(void) : m_samples(m_nSamples) {
        for (unsigned i = 0; i < m_nSamples; i++) {
            const float phase = ((2.0f * 4.0f * atanf(1) * (float) m_freq * (float) i)) / ((float) m_sampleRate);

            m_samples[i] = sinf(phase);
            printf("m_samples[%i]=(%f, %f)\n", i, m_samples[i].real(), m_samples[i].imag());
        }
    }

    virtual ~FftTest() {

    }

    static const unsigned m_lengthInLb = 3;
    static const unsigned m_nSamples = 1 << m_lengthInLb;
    static const unsigned m_freq = 5;

protected:
    std::vector<Complex> m_samples;
    
    static const unsigned m_sampleRate = m_nSamples;

    typedef SineT<int8_t, m_nSamples> Sine;
    
    void printSamples(void) const {
        for (unsigned i = 0; i < m_nSamples / 2; i++) {
            printf("%i => real=%f, imag=%f\n", i, m_samples[i].real(), m_samples[i].imag());
            printf("      amp=%f\n", m_samples[i].abs2());
//            printf("      amp=%f (%f)\n", std::norm(m_samples[i]), (m_samples[i].real() * m_samples[i].real()) + (m_samples[i].imag() * m_samples[i].imag()));
        }
    }
};

/*******************************************************************************
 *
 ******************************************************************************/
static FftTest::Complex
getFactor(const unsigned k, const unsigned n) {
    const float PI = 4.0f * atanf(1);
    
    float phase = -2.0f * PI * ((float) k) / ((float) n);

#if 1
    FftTest::Complex factor(cosf(phase), sinf(phase));
#else
    FftTest::Complex factor = std::exp(FftTest::Complex(phase));
#endif
    return factor;
}

/*******************************************************************************
 *
 ******************************************************************************/
void
fft_r(const unsigned p_lengthInLb, const FftTest::Complex * const p_vector, FftTest::Complex * const p_fft) {
    unsigned n = 1 << p_lengthInLb;

    if (n == 1) {
        *p_fft = *p_vector;
    } else {
        assert(p_lengthInLb > 0);

        unsigned n_2 = (1 << (p_lengthInLb - 1));

        assert((n_2 * 2) == n);

        FftTest::Complex *even = new FftTest::Complex[n_2];
        FftTest::Complex *even_fft = new FftTest::Complex[n_2];
        FftTest::Complex *odd  = new FftTest::Complex[n_2];
        FftTest::Complex *odd_fft  = new FftTest::Complex[n_2];

        for (unsigned i = 0; i < n_2; i++) {
            even[i] = p_vector[2 * i];
            odd[i] = p_vector[(2 * i) + 1];
        }

        fft_r(p_lengthInLb - 1, even, even_fft);
        fft_r(p_lengthInLb - 1, odd, odd_fft);

        for (unsigned k = 0; k < n_2; k++)
        {
            FftTest::Complex factor = getFactor(k, n);
            FftTest::Complex tmp = odd_fft[k] * factor;

            p_fft[k] = even_fft[k] + tmp;
            p_fft[k + n_2] = even_fft[k] - tmp;
        }

        delete[] odd_fft;
        delete[] odd;
        delete[] even_fft;
        delete[] even;
    }
}


/*******************************************************************************
 *
 ******************************************************************************/
void
fft_r2(const unsigned n, const FftTest::Complex * const p_vector, FftTest::Complex * const p_fft) {
    if (n == 1) {
        *p_fft = *p_vector;
    } else {
        unsigned n_2 = n/2;

        FftTest::Complex *even = new FftTest::Complex[n_2];
        FftTest::Complex *even_fft = new FftTest::Complex[n_2];
        FftTest::Complex *odd  = new FftTest::Complex[n_2];
        FftTest::Complex *odd_fft  = new FftTest::Complex[n_2];

        for (unsigned i = 0; i < n_2; i++) {
            even[i] = p_vector[2 * i];
            odd[i] = p_vector[(2 * i) + 1];
        }

        fft_r2(n_2, even, even_fft);
        fft_r2(n_2, odd, odd_fft);

        for (unsigned k = 0; k < n_2; k++)
        {
            FftTest::Complex factor = getFactor(k, n);
            FftTest::Complex tmp = odd_fft[k] * factor;

            p_fft[k] = even_fft[k] + tmp;
            p_fft[k + n_2] = even_fft[k] - tmp;
        }

        delete[] odd_fft;
        delete[] odd;
        delete[] even_fft;
        delete[] even;
    }
}

/*******************************************************************************
 * Algorithm taken from:
 * 
 *  http://introcs.cs.princeton.edu/java/97data/InplaceFFT.java.html
 * 
 * (retrieved on Jan 24th, 2015)
 ******************************************************************************/
template<typename T>
void
fft_java(const unsigned p_lengthInLb, T &p_vector) {
    unsigned N = 1 << p_lengthInLb;

    BitReversalT<32> bitReversal;
    for (unsigned idx = (1u << p_lengthInLb) - 1; idx > 1; idx--) {
        unsigned ridx = bitReversal.getReverse(idx);
        if (ridx < idx) {
            std::swap(p_vector[idx], p_vector[ridx]);
        }
    }

    // butterfly updates
    for (unsigned L = 2; L <= N; L *= 2) {
        for (unsigned k = 0; k < L/2; k++) {
            FftTest::Complex factor = getFactor(k, L);
            
            for (unsigned j = 0; j < N/L; j++) {
                unsigned l = j*L + k;
                unsigned r = j*L + k + L/2;

                FftTest::Complex tmp = factor * p_vector[r];

                p_vector[r] = p_vector[l] - tmp; 
                p_vector[l] += tmp; 
            }
        }
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
void
fft_naive(const unsigned p_lengthInLb, const FftTest::Complex * const p_vector, FftTest::Complex * const p_fft) {
    const float PI = 4.0f * atanf(1);
    const unsigned N = (1 << p_lengthInLb);

    for (unsigned k = 0; k < N; k++) {
        FftTest::Complex value;

        for (unsigned j = 0; j < N; j++) {
            float phase = -2.0f * PI * ((float) k * (float) j) / ((float) N);
            FftTest::Complex factor(cosf(phase), sinf(phase));
            
            value += p_vector[j] * factor;
        }
        
        p_fft[k] = value;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(FftTest, InPlace) {
    dsp::FftT<decltype(m_samples), m_lengthInLb> fft;
    fft.applyFft(m_samples);

    printSamples();
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(FftTest, InPlaceJava) {
    fft_java(this->m_lengthInLb, m_samples);

    printSamples();
}

#if defined(HAVE_FFTW)
/*******************************************************************************
 * See http://www.fftw.org/fftw3_doc/Complex-One_002dDimensional-DFTs.html#Complex-One_002dDimensional-DFTs
 ******************************************************************************/
TEST_F(FftTest, DISABLED_Fftw) {
    fftw_complex *in, *out;
    fftw_plan p;

    const unsigned N = this->m_nSamples;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    for (unsigned i = 0; i < sizeof(m_samples)/sizeof(m_samples[0]); i++) {
        in[i][0] = m_samples[i].real();
        in[i][1] = m_samples[i].imag();
    }
    
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p); /* repeat as needed */

    for (unsigned i = 0; i < sizeof(m_samples)/sizeof(m_samples[0]); i++) {
        m_samples[i].real() = out[i][0];
        m_samples[i].imag() = out[i][1];
    }

    printSamples();

    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
}
#endif /* defined(HAVE_FFTW) */

} /* namespace dsp */
