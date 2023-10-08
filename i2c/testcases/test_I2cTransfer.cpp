/*-
 * $Copyright$
-*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <i2c/I2cTransfer.hpp>
#include <i2c/I2cTransfer.cpp>

#include <sys/types.h>
#include <stdint.h>

#if defined(__cplusplus)
#if !defined(__STDC_FORMAT_MACROS)
#error This code requires __STDC_FORMAT_MACROS to be defined!
#endif /* !defined(__STDC_FORMAT_MACROS) */
#endif /* defined(__cplusplus) */
#include <inttypes.h>

#include <string.h>

#include <iostream>
#include <sstream>

using ::testing::_;
using ::testing::DoAll;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::Pointee;
using ::testing::Return;
using ::testing::NotNull;
using ::testing::StrEq;
using ::testing::SetArgPointee;
using ::testing::Sequence;

MATCHER_P2(IsEqualBuffer, p_buffer, p_len, "") {
    if (arg == NULL && p_buffer != NULL)
        return false;

    return (bcmp(arg, p_buffer, p_len) == 0);
};

ACTION_P2(SetReadBuffer, p_buffer, p_len) {
    memcpy(arg1, p_buffer, p_len);
}

namespace i2c {
/*******************************************************************************
 *
 ******************************************************************************/
class I2cTransferTest : public ::testing::Test {
protected:
    I2cBusMock m_bus;
    I2cDeviceMock m_device;
    i2c::TransferT<I2cBusMock, I2cDeviceMock> *m_obj;
    std::stringstream m_istream;
    std::stringstream m_ostream;

public:
    I2cTransferTest() {
        m_obj = new i2c::TransferT<I2cBusMock, I2cDeviceMock>(&m_bus, &m_device, m_istream, m_ostream);
    }

    virtual ~I2cTransferTest() {
        delete m_obj;
    }
};

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, CreateAndDelete) {

}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, Reset) {
    EXPECT_CALL(m_bus, reset()).WillOnce(Return(0));

    int rc = m_obj->reset();
    EXPECT_EQ(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, ResetWithFailure) {
    EXPECT_CALL(m_bus, reset()).WillOnce(Return(123));

    int rc = m_obj->reset();
    EXPECT_EQ(123, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, ScanFullBus) {
    InSequence s;
    /* uint16_t so we can loop from 0..256 */
    for (uint16_t addr = 0; addr < 256; addr += 2) {
        EXPECT_CALL(m_bus, start((uint8_t) addr, false)).WillOnce(Return(0));
        EXPECT_CALL(m_bus, stop()).Times(1).WillRepeatedly(Return(0));
    }

    int rc = m_obj->scan();
    EXPECT_EQ(0, rc);

    EXPECT_NE(std::string::npos, m_ostream.str().find(std::string("Devices found:")));
    /* uint16_t so we can loop from 0..256 */
    for (uint16_t addr = 0; addr < 256; addr += 2) {
        char buf[16];
        snprintf(buf, sizeof(buf), "0x%.02" PRIx8, (uint8_t) addr);
        EXPECT_NE(std::string::npos, m_ostream.str().find(std::string(buf)));
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, ScanFullBusWithUnresponsiveDevices) {
    uint8_t responding = 0xA0;

    InSequence s;
    for (uint16_t addr = 0; addr < 256; addr += 2) {
        if (addr != responding) {
            EXPECT_CALL(m_bus, start(addr, false)).Times(1).WillOnce(Return(-1));
            EXPECT_CALL(m_bus, reset()).Times(1).WillOnce(Return(0));
        } else {
            EXPECT_CALL(m_bus, start(addr, false)).Times(1).WillOnce(Return(0));
            EXPECT_CALL(m_bus, stop()).Times(1).WillOnce(Return(0));
        }
    }

    int rc = m_obj->scan();
    EXPECT_EQ(0, rc);
    EXPECT_NE(std::string::npos, m_ostream.str().find(std::string("Devices found:")));

    /* uint16_t so we can loop from 0..256 */
    for (uint16_t addr = 0; addr < 256; addr += 2) {
        char buf[16];
        snprintf(buf, sizeof(buf), "0x%.02" PRIx8, (uint8_t) addr);
        if (addr != responding) {
            EXPECT_EQ(std::string::npos, m_ostream.str().find(std::string(buf)));
        } else {
            EXPECT_NE(std::string::npos, m_ostream.str().find(std::string(buf)));
        }
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, TransferWriteBinary) {
    char buffer[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    ssize_t len = sizeof(buffer);
    off_t offset = 0xdeadc0de;

    m_istream.write(buffer, len);

    EXPECT_CALL(m_device, write(offset, IsEqualBuffer(buffer, len), len)).WillOnce(Return(len));

    EXPECT_EQ(len, m_obj->write(offset, len, NULL));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, TransferWriteBinaryShortInput) {
    char buffer[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    off_t offset = 0xdeadc0de;
    ssize_t len = sizeof(buffer);
    ssize_t missing = 2;

    m_istream.write(buffer, len - missing);

    EXPECT_CALL(m_device, write(offset, IsEqualBuffer(buffer, len - missing), len - missing)).WillOnce(Return(len - missing));

    EXPECT_EQ(len - missing, m_obj->write(offset, len, NULL));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, TransferWrite) {
    off_t offset = 0xdeadc0de;

    const uint8_t data[] = { 0xca, 0xfe, 0xba, 0xbe };

    uint8_t write_data[sizeof(data)];
    memcpy(write_data, data, sizeof(data));

    size_t count = sizeof(write_data);

    EXPECT_CALL(m_device, write(offset, IsEqualBuffer(&write_data, sizeof(data)), count)).WillOnce(Return(count));

    EXPECT_EQ((ssize_t) count, m_obj->write(offset, sizeof(write_data), write_data));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, TransferReadBinary) {
    char buffer[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    ssize_t len = sizeof(buffer);

    off_t offset = 0xdeadc0de;
    size_t count = 64;

    EXPECT_CALL(m_device, read(offset, NotNull(), count)).WillOnce(DoAll(SetReadBuffer(buffer, len), Return(len)));

    EXPECT_EQ(len, m_obj->read(offset, count, true));

    m_ostream.seekg(0, m_ostream.beg);
    for (int i = 0; i < len; i++) {
        EXPECT_EQ(buffer[i], m_ostream.get());
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, TransferRead) {
    char buffer[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
        0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    };

    char outp[4096];

    snprintf(outp, sizeof(outp),
      "[0x00000000] 00010203 04050607 08090a0b 0c0d0e0f\n"
      "[0x00000010] 10111213 14151617 18191a1b 1c1d1e1f\n"
      "[0x00000020] 20212223 24252627 28292a2b 2c2d2e2f\n"
    );

    ssize_t len = sizeof(buffer);

    off_t offset = 0;

    EXPECT_CALL(m_device, read(offset, NotNull(), len)).WillOnce(DoAll(SetReadBuffer(buffer, len), Return(len)));

    EXPECT_EQ((ssize_t) len, m_obj->read(offset, len, false));

    int cmp = strcmp(m_ostream.str().c_str(), outp);
    EXPECT_EQ(0, cmp);
    if (cmp) {
        std::cout << "Expected:" << std::endl << outp << std::endl;
        std::cout << "Actual:" << std::endl << m_ostream.str() << std::endl;
    }
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cTransferTest, TransferReadAtNonEvenOffset) {
    char buffer[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
        0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    };

    char outp[4096];

    snprintf(outp, sizeof(outp),
             "[0x00000080] ......00 01020304 05060708 090a0b0c\n"
             "[0x00000090] 0d0e0f10 11121314 15161718 191a1b1c\n"
             "[0x000000a0] 1d1e1f20 21222324 25262728 292a2b2c\n"
             "[0x000000b0] 2d2e.... ........ ........ ........\n"
    );

    ssize_t len = sizeof(buffer);

    off_t offset = 0x83;

    EXPECT_CALL(m_device, read(offset, NotNull(), len)).WillOnce(DoAll(SetReadBuffer(buffer, len - 1), Return(len - 1)));

    EXPECT_EQ((ssize_t) len - 1, m_obj->read(offset, len, false));

    int cmp = strcmp(m_ostream.str().c_str(), outp);
    EXPECT_EQ(0, cmp);
    if (cmp) {
        std::cout << "Expected:" << std::endl << outp << std::endl;
        std::cout << "Actual:" << std::endl << m_ostream.str() << std::endl;
    }
}

} /* namespace i2c */
