/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <i2c/I2cDevice.hpp>
#include <i2c/I2cDevice.cpp>

using ::testing::Return;
using ::testing::NotNull;
using ::testing::StrEq;
using ::testing::SetArgPointee;
using ::testing::InSequence;

namespace i2c {

/*******************************************************************************
 *
 ******************************************************************************/
class I2cDeviceTest : public ::testing::Test {
protected:
    static const char * const   m_filename;
    static const uint8_t        m_addr;
    static const uint8_t        m_width;
    static const uint32_t       m_pageSize;
    static const AddressMode    m_mode;

    I2cBusMock              m_bus;
    DeviceT<I2cBusMock> *   m_device;

public:
    I2cDeviceTest() {
        m_device = new i2c::DeviceT<I2cBusMock>(&m_bus, m_addr, m_width, m_pageSize, m_mode);
    };

    virtual ~I2cDeviceTest() {
        delete m_device;
    };
};

const char * const  I2cDeviceTest::m_filename = "/dev/null";
const uint8_t       I2cDeviceTest::m_addr = 0xc0;
const uint8_t       I2cDeviceTest::m_width = 4;
const uint32_t      I2cDeviceTest::m_pageSize = 0;
const AddressMode   I2cDeviceTest::m_mode = i2c::RepeatedStart;

/*******************************************************************************
 *
 ******************************************************************************/
TEST(I2cDeviceTestNoFixture, Read) {
    static const uint8_t data = 0xa5;
    uint8_t buffer = 0;
    uint32_t offset = 0xaffe;
    size_t length = sizeof(buffer);
    uint8_t m_addr = 0xA0;

    I2cBusMock              m_bus;
    DeviceT<I2cBusMock> *   m_device = new i2c::DeviceT<I2cBusMock>(&m_bus, m_addr, 2, 4096, i2c::RepeatedStart);

    InSequence s;
    EXPECT_CALL(m_bus, start(m_addr, false)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  8) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  0) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, start(m_addr | 0x01, true)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, read(NotNull(), false)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data), Return(0)));
    EXPECT_CALL(m_bus, stop()).Times(1).WillOnce(Return(0));

    EXPECT_EQ(1, m_device->read(offset, &buffer, length));
    EXPECT_EQ(1u, length);
    EXPECT_FALSE(memcmp(&buffer, &data, sizeof(buffer)));

    delete m_device;
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST(I2cDeviceTestNoFixture, Write) {
    static const uint8_t data = 0xa5;
    uint32_t offset = 0xaffe;
    size_t length = sizeof(data);
    uint8_t m_addr = 0xA0;

    I2cBusMock              m_bus;
    DeviceT<I2cBusMock> *   m_device = new i2c::DeviceT<I2cBusMock>(&m_bus, m_addr, 2, 4096, i2c::RepeatedStart);

    InSequence s;
    EXPECT_CALL(m_bus, start(m_addr, false)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  8) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  0) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, stop()).Times(1).WillOnce(Return(0));

    EXPECT_EQ(1, m_device->write(offset, &data, length));
    EXPECT_EQ(1u, length);

    delete m_device;
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cDeviceTest, CreateAndDelete) {

}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cDeviceTest, ReadSingleByte) {
    static const uint8_t data = 0xa5;
    uint8_t buffer = 0;
    uint32_t offset = 0xdeadc0de;
    size_t length = sizeof(buffer);

    InSequence s;
    EXPECT_CALL(m_bus, start(m_addr, false)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 24) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 16) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  8) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  0) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, start(m_addr | 0x01, true)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, read(NotNull(), false)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data), Return(0)));
    EXPECT_CALL(m_bus, stop()).Times(1).WillOnce(Return(0));

    EXPECT_EQ(1, m_device->read(offset, &buffer, length));
    EXPECT_EQ(1u, length);
    EXPECT_FALSE(memcmp(&buffer, &data, sizeof(buffer)));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cDeviceTest, ReadFourBytes) {
    static const uint8_t data[4] = { 0xaf, 0xfe, 0xa5, 0x5a };
    uint8_t buffer[sizeof(data)];
    bzero(buffer, sizeof(buffer));
    uint32_t offset = 0xdeadc0de;
    size_t length = sizeof(data);

    InSequence s;
    EXPECT_CALL(m_bus, start(m_addr, false)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 24) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 16) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  8) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  0) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, start(m_addr | 0x01, true)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, read(NotNull(), true)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data[0]), Return(0)));
    EXPECT_CALL(m_bus, read(NotNull(), true)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data[1]), Return(0)));
    EXPECT_CALL(m_bus, read(NotNull(), true)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data[2]), Return(0)));
    EXPECT_CALL(m_bus, read(NotNull(), false)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data[3]), Return(0)));
    EXPECT_CALL(m_bus, stop()).Times(1).WillOnce(Return(0));

    EXPECT_EQ((ssize_t) sizeof(buffer), m_device->read(offset, buffer, length));
    EXPECT_EQ(sizeof(buffer), length);
    EXPECT_FALSE(memcmp(&buffer, &data, sizeof(buffer)));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cDeviceTest, ReadAFewBytesWithError) {
    static const uint8_t data[4] = { 0xaf, 0xfe, 0xa5, 0x5a };
    uint8_t buffer[sizeof(data)];
    bzero(buffer, sizeof(buffer));
    uint32_t offset = 0xdeadc0de;
    size_t length = sizeof(data);

    InSequence s;
    EXPECT_CALL(m_bus, start(m_addr, false)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 24) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 16) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  8) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  0) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, start(m_addr | 0x01, true)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, read(NotNull(), true)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data[0]), Return(0)));
    EXPECT_CALL(m_bus, read(NotNull(), true)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data[1]), Return(0)));
    EXPECT_CALL(m_bus, read(NotNull(), true)).Times(1).WillOnce(DoAll(SetArgPointee<0>(data[2]), Return(1)));
    EXPECT_CALL(m_bus, reset()).Times(1).WillOnce(Return(0));

    EXPECT_EQ((ssize_t) 2u, m_device->read(offset, buffer, length));
    EXPECT_EQ(sizeof(buffer), length);
    EXPECT_TRUE(memcmp(&buffer, &data, sizeof(buffer)));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cDeviceTest, WriteSingleByte) {
    static const uint8_t data = 0xa5;
    uint32_t offset = 0xdeadc0de;
    size_t length = sizeof(data);

    InSequence s;
    EXPECT_CALL(m_bus, start(m_addr, false)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 24) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 16) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  8) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  0) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, stop()).Times(1).WillOnce(Return(0));

    EXPECT_EQ((ssize_t) length, m_device->write(offset, &data, length));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cDeviceTest, WriteFourBytes) {
    static const uint8_t data[4] = { 0xaf, 0xfe, 0xa5, 0x5a };
    uint32_t offset = 0xdeadc0de;
    size_t length = sizeof(data);

    InSequence s;
    EXPECT_CALL(m_bus, start(m_addr, false)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 24) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 16) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  8) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  0) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data[0])).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data[1])).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data[2])).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data[3])).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, stop()).Times(1).WillOnce(Return(0));

    EXPECT_EQ((ssize_t) length, m_device->write(offset, data, length));
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cDeviceTest, WriteAFewBytesWithError) {
    static const uint8_t data[4] = { 0xaf, 0xfe, 0xa5, 0x5a };
    uint32_t offset = 0xdeadc0de;
    size_t length = sizeof(data);

    InSequence s;
    EXPECT_CALL(m_bus, start(m_addr, false)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 24) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >> 16) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  8) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write((offset >>  0) & 0xFF)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data[0])).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data[1])).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_bus, write(data[2])).Times(1).WillOnce(Return(1));
    EXPECT_CALL(m_bus, reset()).Times(1).WillOnce(Return(0));

    EXPECT_EQ((ssize_t) 2u, m_device->write(offset, data, length));
}

}; /* namespace i2c */
