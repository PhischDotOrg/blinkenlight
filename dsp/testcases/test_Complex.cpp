/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <dsp/Complex.hpp>

namespace dsp {

/*******************************************************************************
 *
 ******************************************************************************/
class ComplexTest : public ::testing::Test {
protected:
    typedef int complex_t;
    typedef ComplexT<complex_t> Complex;

    Complex a;
    Complex b;

    static const complex_t  A_REAL;
    static const complex_t  A_IMAG;
    
    static const complex_t  B_REAL;
    static const complex_t  B_IMAG;

    void testSizeOf(void) const {
        /* Total size of class object */
        EXPECT_EQ(2 * sizeof(complex_t), sizeof(Complex));
        /* Offset of m_real attribute */
        EXPECT_EQ(0u, reinterpret_cast<intptr_t>(&a.m_real) -reinterpret_cast<intptr_t>(&a));
        /* Offset of m_imag attribute */
        EXPECT_EQ((intptr_t) sizeof(complex_t), reinterpret_cast<intptr_t>(&a.m_imag) - reinterpret_cast<intptr_t>(&a));
    }

public:
    ComplexTest(void) : a(A_REAL, A_IMAG), b(B_REAL, B_IMAG) {
        
    }
    
    virtual ~ComplexTest(void) {
        
    }
};

const ComplexTest::complex_t ComplexTest::A_REAL = 2;
const ComplexTest::complex_t ComplexTest::A_IMAG = 3;

const ComplexTest::complex_t ComplexTest::B_REAL = 4;
const ComplexTest::complex_t ComplexTest::B_IMAG = 5;

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ComplexTest, CreateAndDelete) {
    EXPECT_EQ(A_REAL, a.real());
    EXPECT_EQ(A_IMAG, a.imag());

    EXPECT_EQ(B_REAL, b.real());
    EXPECT_EQ(B_IMAG, b.imag());
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ComplexTest, SizeOf) {
    testSizeOf();
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ComplexTest, Copy) {
    Complex c(a);

    EXPECT_EQ(a.real(), c.real());
    EXPECT_EQ(a.imag(), c.imag());
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ComplexTest, Assign) {
    Complex c;

    EXPECT_EQ(ComplexTest::complex_t(), c.real());
    EXPECT_EQ(ComplexTest::complex_t(), c.imag());

    c = a;

    EXPECT_EQ(a.real(), c.real());
    EXPECT_EQ(a.imag(), c.imag());
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ComplexTest, Add) {
    Complex c;

    EXPECT_EQ(ComplexTest::complex_t(), c.real());
    EXPECT_EQ(ComplexTest::complex_t(), c.imag());

    c = a + b;

    EXPECT_EQ(a.real() + b.real(), c.real());
    EXPECT_EQ(a.imag() + b.imag(), c.imag());
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ComplexTest, Subtract) {
    Complex c;

    EXPECT_EQ(ComplexTest::complex_t(), c.real());
    EXPECT_EQ(ComplexTest::complex_t(), c.imag());

    c = a - b;

    EXPECT_EQ(a.real() - b.real(), c.real());
    EXPECT_EQ(a.imag() - b.imag(), c.imag());
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(ComplexTest, Multiply) {
    Complex c;

    EXPECT_EQ(ComplexTest::complex_t(), c.real());
    EXPECT_EQ(ComplexTest::complex_t(), c.imag());

    c = a * b;

    EXPECT_EQ((a.real() * b.real()) - (a.imag() * b.imag()), c.real());
    EXPECT_EQ((a.real() * b.imag()) + (a.imag() * b.real()), c.imag());
}

} /* namespace dsp */
