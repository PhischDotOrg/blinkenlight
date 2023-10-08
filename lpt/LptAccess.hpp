/*-
 * $Copyright$
-*/
#ifndef _LPT_ACCESS_HPP_9c0e5e74_f160_4f25_9a58_5825f677c2ad
#define _LPT_ACCESS_HPP_9c0e5e74_f160_4f25_9a58_5825f677c2ad

#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 *
 ******************************************************************************/
#if !defined(LPT_ENV)
#define LPT_ENV Undefined
#endif

#include <lpt/LptAccessDarwin.hpp>
#include <lpt/LptAccessFreeBSD.hpp>
#include <lpt/LptAccessLinux.hpp>
#include <lpt/LptAccessMock.hpp>
#include <lpt/LptAccessEmbedded.hpp>

namespace lpt {

typedef enum LptAccessImpl_e {
    Undefined,
    Darwin,
    Embedded,
    FreeBSD,
    GTest,
    Linux,
} LptAccessImpl_t;

template<LptAccessImpl_t> struct LptAccessChoice;

template<> struct LptAccessChoice<Darwin> {
    typedef LptAccessDarwin m_type;
};

template<> struct LptAccessChoice<Embedded> {
    typedef LptAccessEmbedded m_type;
};

template<> struct LptAccessChoice<FreeBSD> {
    typedef LptAccessFreeBSD m_type;
};

template<> struct LptAccessChoice<GTest> {
    typedef LptAccessMock m_type;
};

template<> struct LptAccessChoice<Linux> {
    typedef LptAccessLinux m_type;
};

template<> struct LptAccessChoice<Undefined> {
    typedef void m_type;
};

struct LptAccessT {
    typedef LptAccessChoice<LPT_ENV>::m_type m_type;
};

typedef LptAccessT::m_type LptAccess;

} /* namespace lpt */

#endif /* _LPT_HPP_9c0e5e74_f160_4f25_9a58_5825f677c2ad */
