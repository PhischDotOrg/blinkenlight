/*-
 * $Copyright$
-*/

#ifndef _DMA_CHANNEL_HPP_e94ddf65_7e91_4056_a4ce_6e2f83ff5102
#define _DMA_CHANNEL_HPP_e94ddf65_7e91_4056_a4ce_6e2f83ff5102

#include <stddef.h>
#include <stdint.h>

#if defined(DEBUG_BUILD) && defined(GMOCK_FOUND)
#include <gmock/gmock.h>
#endif /* defined(DEBUG_BUILD) && defined(GMOCK_FOUND) */

/*******************************************************************************
 * 
 ******************************************************************************/
#if !defined(DMA_ENV)
#define DMA_ENV Undefined
#endif

/*******************************************************************************
 * 
 ******************************************************************************/
namespace dma {

typedef enum DmaImpl_e {
    GTest,
    STM32F4,
    Undefined,
} DmaImpl_t;

} /* namespace dma */

/*******************************************************************************
 * 
 ******************************************************************************/
#include "dma/DmaChannelViaSTM32F4.hpp"

/*******************************************************************************
 * DMA Channel Type Definition
 ******************************************************************************/
namespace dma {

template<DmaImpl_t> struct DmaChannelChoice;

class DmaChannelMock;

template<> struct DmaChannelChoice<GTest> {
    typedef DmaChannelMock m_type;
};

template<> struct DmaChannelChoice<STM32F4> {
    typedef DmaChannelViaSTM32F4T<> m_type;
};

template<> struct DmaChannelChoice<Undefined> {
    typedef void m_type;
};

struct DmaChannelT {
    typedef DmaChannelChoice<DMA_ENV>::m_type m_type;
};

typedef DmaChannelT::m_type DmaChannel;

} /* namespace dma */

#endif /* _DMA_CHANNEL_HPP_e94ddf65_7e91_4056_a4ce_6e2f83ff5102 */
