/*-
 * $Copyright$
-*/

#ifndef _SIN_COS_LIBM_HPP_0c6ce036_c36c_4a50_8313_834059894941
#define _SIN_COS_LIBM_HPP_0c6ce036_c36c_4a50_8313_834059894941

#include <stdint.h>

namespace dsp {

template<typename T, bool useMathLib_t> class SinCosT;

/*******************************************************************************
 *
 ******************************************************************************/
template<typename T>
class SinCosT<T, true> {
private:
    static double phase(const T p_phase);
    
public:
    SinCosT(void);
    ~SinCosT();

    static T sin(const T p_phase);
    static T cos(const T p_phase);
    
    static const T PI;
    static const T AMPLITUDE;
};

} /* namespace dsp */

#include <dsp/SinCosLibM.cpp>

#endif /* _SIN_COS_LIBM_HPP_0c6ce036_c36c_4a50_8313_834059894941 */
    