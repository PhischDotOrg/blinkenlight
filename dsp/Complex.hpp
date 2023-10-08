/*-
 * $Copyright$
-*/

#ifndef _DSP_COMPLEX_HPP_bcdaedfb_c1a0_49c5_8966_a3c97d1144fb
#define _DSP_COMPLEX_HPP_bcdaedfb_c1a0_49c5_8966_a3c97d1144fb

/*******************************************************************************
 *
 ******************************************************************************/
namespace dsp {

template <typename T = float>
class ComplexT {
    friend class ComplexTest;

private:
    T   m_real;
    T   m_imag;

public:
    ComplexT(const T &p_real = T(), const T &p_imag = T());
    ComplexT(const ComplexT &p_obj);

    template<typename U>
    ComplexT(const ComplexT<U> &p_obj);

    ~ComplexT();

    ComplexT & operator=(const ComplexT &p_rhs);
    ComplexT & operator+=(const ComplexT &);
    ComplexT & operator-=(const ComplexT &);
    ComplexT & operator*=(const ComplexT &);

    T real(void) const { return this->m_real; }
    T imag(void) const { return this->m_imag; }

    /*
     * Return the square of the absolute value. Useful for use on a
     * microcontroller b/c you don't need to calculate the square root
     */
    T abs2(void) const {
        return ((this->real() * this->real()) + (this->imag() * this->imag()));
    }

    typedef T value_type;
};

template<typename T> ComplexT<T> operator+(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs);
template<typename T> ComplexT<T> operator+(const ComplexT<T> &p_lhs, const T& p_val);
template<typename T> ComplexT<T> operator+(const T& p_val, const ComplexT<T>& p_rhs);

template<typename T> ComplexT<T> operator-(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs);
template<typename T> ComplexT<T> operator-(const ComplexT<T> &p_lhs, const T& p_val);
template<typename T> ComplexT<T> operator-(const T& p_val, const ComplexT<T>& p_rhs);

template<typename T> ComplexT<T> operator*(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs);
template<typename T> ComplexT<T> operator*(const ComplexT<T> &p_lhs, const T& p_val);
template<typename T> ComplexT<T> operator*(const T& p_val, const ComplexT<T>& p_rhs);

template<typename T> ComplexT<T> operator/(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs);
template<typename T> ComplexT<T> operator/(const ComplexT<T> &p_lhs, const T& p_val);
template<typename T> ComplexT<T> operator/(const T& p_val, const ComplexT<T>& p_rhs);

template<typename T> ComplexT<T> operator+(const ComplexT<T> &p_rhs);
template<typename T> ComplexT<T> operator-(const ComplexT<T> &p_rhs);

template<typename T> bool operator==(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs);
template<typename T> bool operator==(const ComplexT<T> &p_lhs, const T &p_val);
template<typename T> bool operator==(const T &p_val, const ComplexT<T> &p_rhs);

template<typename T> bool operator!=(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs);
template<typename T> bool operator!=(const ComplexT<T> &p_lhs, const T &p_val);
template<typename T> bool operator!=(const T &p_val, const ComplexT<T> &p_rhs);

template<typename T> bool operator<(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs);
template<typename T> bool operator>(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs);

} /* dsp */

#if defined(DEBUG_BUILD) && defined(GMOCK_FOUND)
#include <ostream>
namespace dsp {
    template<typename T> std::ostream& operator<<(std::ostream &p_stream, const ComplexT<T> &p_value);
} /* dsp */
#endif /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */

#include "Complex.cpp"

#endif /* _DSP_COMPLEX_HPP_bcdaedfb_c1a0_49c5_8966_a3c97d1144fb */
