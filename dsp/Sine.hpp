/*-
 * $Copyright$
-*/

#ifndef _DSP_SINE_HPP_eaf1471c_c373_495a_9902_7855951e94ff
#define _DSP_SINE_HPP_eaf1471c_c373_495a_9902_7855951e94ff

namespace dsp {
    
template <typename T, const int t_sampleRate>
class SineT {
public:
    SineT(void);
    ~SineT();

    static T get_sample(const unsigned p_freqInHz, const int p_sample);
};

} /* namespace dsp */

#include <dsp/Sine.cpp>

#endif /* _DSP_SINE_HPP_eaf1471c_c373_495a_9902_7855951e94ff */
