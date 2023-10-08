/*-
 * $Copyright$
-*/

#ifndef _COMPLEX_CPP_386758cd_69fd_4380_b149_c36db1cb2cfc
#define _COMPLEX_CPP_386758cd_69fd_4380_b149_c36db1cb2cfc

#include "Complex.hpp"
#include <assert.h>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T>::ComplexT(const T &p_real /* = T() */, const T &p_imag /* = T() */)
  : m_real(p_real), m_imag(p_imag) {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T>::ComplexT(const ComplexT &p_obj)
  : m_real(p_obj.m_real), m_imag(p_obj.m_imag) {

}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T>::~ComplexT() {
    
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T> &
ComplexT<T>::operator=(const ComplexT &p_rhs) {
    if (this != &p_rhs) {
        this->m_real = p_rhs.m_real;
        this->m_imag = p_rhs.m_imag;
    }

    return *this;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T> &
ComplexT<T>::operator+=(const ComplexT &p_rhs) {
    if (this != &p_rhs) {
        this->m_real += p_rhs.real();
        this->m_imag += p_rhs.imag();
    }

    return *this;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T> &
ComplexT<T>::operator-=(const ComplexT &p_rhs) {
    assert(this != &p_rhs);

    this->m_real -= p_rhs.real();
    this->m_imag -= p_rhs.imag();

    return *this;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T> &
ComplexT<T>::operator*=(const ComplexT &p_rhs) {
    assert(this != &p_rhs);

    T real = this->m_real;
    T imag = this->m_imag;
    
    this->m_real = real * p_rhs.real() - imag * p_rhs.imag();
    this->m_imag = real * p_rhs.imag() + imag * p_rhs.real();

    return *this;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T> operator+(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs) {
    ComplexT<T> val(p_lhs);
    
    val += p_rhs;
    
    return val;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T> operator-(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs) {
    ComplexT<T> val(p_lhs);
    
    val -= p_rhs;
    
    return val;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
ComplexT<T> operator*(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs) {
    ComplexT<T> val(p_lhs);
    
    val *= p_rhs;
    
    return val;
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
bool
operator==(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs) {
    return (p_lhs.real() == p_rhs.real()) && (p_lhs.imag() == p_rhs.imag());
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
bool
operator<(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs) {
    return p_lhs.real() < p_rhs.real();
}

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
bool
operator>(const ComplexT<T> &p_lhs, const ComplexT<T> &p_rhs) {
    return p_lhs.real() > p_rhs.real();
}

} /* namespace dsp */

/*******************************************************************************
 *
 ******************************************************************************/
#if defined(DEBUG_BUILD) && defined(GMOCK_FOUND)
#include <ostream>
namespace dsp {

template<typename T> std::ostream&
operator<<(std::ostream &p_stream, const ComplexT<T> &p_value) {
    p_stream << "{" << p_value.real() << ", " << p_value.imag() << "}";
    return p_stream;
}

} /* dsp */
#endif /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */

#endif
