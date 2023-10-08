/*-
 * $Copyright$
-*/

#include <gmock/gmock.h>

#include <i2c/I2cBusViaGpio.hpp>
#include <i2c/I2cBusViaGpio.cpp>

#include <gpio/GpioPin.hpp>

using ::testing::_;
using ::testing::DoAll;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::SetArgReferee;

/*******************************************************************************
 *
 ******************************************************************************/
namespace i2c {

class I2cBusViaGpioTest : public ::testing::Test {
protected:
    gpio::GpioPinMock                   m_scl;
    gpio::GpioPinMock                   m_sda;
    I2cBusViaGpioT<gpio::GpioPinMock> * m_bus;

    uint8_t                             m_addr;

    void mock_tx_bit(bool p_bit) {
        /* SCL Low */
        mock_set(m_scl, false);

        EXPECT_CALL(m_sda, _set(p_bit ? gpio::Pin::HiZ : gpio::Pin::Off)).Times(1).WillOnce(Return(0));

        /* SCL HiZ */
        EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
        EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

        EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(p_bit ? gpio::Pin::On : gpio::Pin::Off), Return(0)));

        /* SCL Low */
        mock_set(m_scl, false);
    }

    void mock_set(gpio::GpioPinMock &p_mock, bool p_bit) {
        EXPECT_CALL(p_mock, _set(p_bit ? gpio::Pin::HiZ : gpio::Pin::Off)).Times(1).WillOnce(Return(0));
        EXPECT_CALL(p_mock, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(p_bit ? gpio::Pin::On : gpio::Pin::Off), Return(0)));
    }

    void mock_rx_bit(bool p_bit) {
        /* SCL Low */
        mock_set(m_scl, false);

        EXPECT_CALL(m_sda, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));

        /* SCL HiZ */
        EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
        EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

        EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(p_bit ? gpio::Pin::On : gpio::Pin::Off), Return(0)));

        /* SCL Low */
        mock_set(m_scl, false);
    }

public:
    I2cBusViaGpioTest(void) : m_scl(NULL, "SCL", gpio::Pin::On), m_sda(NULL, "SDA", gpio::Pin::On), m_bus(NULL) {
        m_bus = new I2cBusViaGpioT<gpio::GpioPinMock>(&m_scl, &m_sda);
        m_addr = 0xA0;
    }
    virtual ~I2cBusViaGpioTest() {
        delete m_bus;
    }
};

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, CreateAndDelete) {

}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, Start) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    mock_set(m_sda, false);
    mock_set(m_scl, false);

    /* Transmit address */
    for (int i = 7; i >= 0; i--)
        mock_tx_bit((m_addr >> i ) & 0x1);

    /* Wait for ACK bit */
    mock_rx_bit(false);

    int rc = m_bus->start(m_addr, false);
    EXPECT_EQ(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartNotIdleSclNotHi) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    int rc = m_bus->start(m_addr, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartNotIdleSdaNotHi) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    int rc = m_bus->start(m_addr, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartConflictSdaNotLo) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    int rc = m_bus->start(0xA0, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartConflictSclNotLo) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    int rc = m_bus->start(0xA0, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartTxSclNotLo) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    /* Transmit address */
    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    int rc = m_bus->start(0xA0, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartTxSdaSetError) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    /* Transmit address */
    bool bit = (m_addr >> 7) & 0x1;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(bit ? gpio::Pin::HiZ : gpio::Pin::Off)).Times(1).WillOnce(Return(-1));

    int rc = m_bus->start(0xA0, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartTxSclSetError) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    /* Transmit address */
    bool bit = (m_addr >> 7) & 0x1;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(bit ? gpio::Pin::HiZ : gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(-1));

    int rc = m_bus->start(0xA0, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartTxSclStuckLoThenError) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    /* Transmit address */
    bool bit = (m_addr >> 7) & 0x1;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(bit ? gpio::Pin::HiZ : gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));

    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(-1)));

    int rc = m_bus->start(0xA0, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartTxSdaUnexpected) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    /* Transmit address */
    bool bit = (m_addr >> 7) & 0x1;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(bit ? gpio::Pin::HiZ : gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));

    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(!bit ? gpio::Pin::On : gpio::Pin::Off), Return(0)));

    int rc = m_bus->start(0xA0, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StartNoAck) {
    InSequence s;

    /* Ensure bus is idle */
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* Signal Start Condition: SDA -> Low; SCL -> Low */
    mock_set(m_sda, false);
    mock_set(m_scl, false);

    /* Transmit address */
    for (int i = 7; i >= 0; i--)
        mock_tx_bit((m_addr >> i ) & 0x1);

    /* Wait for ACK bit */
    /* SCL Low */
    mock_set(m_scl, false);

    EXPECT_CALL(m_sda, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));

    /* SCL HiZ */
    EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    /* SCL Low */
    mock_set(m_scl, false);

    int rc = m_bus->start(m_addr, false);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, Stop) {
    InSequence s;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    EXPECT_CALL(m_sda, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    int rc = m_bus->stop();
    EXPECT_EQ(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StopSclNotLo) {
    InSequence s;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(-1)));

    int rc = m_bus->stop();
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StopSdaNotLo) {
    InSequence s;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    int rc = m_bus->stop();
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StopSclNotHi) {
    InSequence s;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(-1));

    int rc = m_bus->stop();
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, StopSdaNotHi) {
    InSequence s;

    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    EXPECT_CALL(m_sda, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    int rc = m_bus->stop();
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, ReadAck) {
    uint8_t data = 0, expected_data = 0xa5;

    InSequence s;
    for (int i = ((sizeof(expected_data) * 8) - 1); i >= 0; i--)
        mock_rx_bit((expected_data >> i) & 0x1);
    mock_tx_bit(false);

    int rc = m_bus->read(&data, true);
    EXPECT_EQ(0, rc);
    EXPECT_EQ(expected_data, data);
}


/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, ReadNoAck) {
    uint8_t data = 0, expected_data = 0xa5;

    InSequence s;
    for (int i = ((sizeof(expected_data) * 8) - 1); i >= 0; i--)
        mock_rx_bit((expected_data >> i) & 0x1);
    mock_tx_bit(false);

    int rc = m_bus->read(&data, true);
    EXPECT_EQ(0, rc);
    EXPECT_EQ(expected_data, data);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, WriteAck) {
    uint8_t data = 0xa5;

    InSequence s;
    for (int i = ((sizeof(data) * 8) - 1); i >= 0; i--)
        mock_tx_bit((data >> i) & 0x1);
    mock_rx_bit(false);

    int rc = m_bus->write(data);
    EXPECT_EQ(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, WriteNoAck) {
    uint8_t data = 0xa5;

    InSequence s;
    for (int i = ((sizeof(data) * 8) - 1); i >= 0; i--)
        mock_tx_bit((data >> i) & 0x1);
    mock_rx_bit(true);

    int rc = m_bus->write(data);
    EXPECT_NE(0, rc);
}

/*******************************************************************************
 *
 ******************************************************************************/
TEST_F(I2cBusViaGpioTest, Reset) {
    InSequence s;

    for (int i = 0; i < 9; i++)
        mock_rx_bit(i % 2);

    /* Signal STOP */
    EXPECT_CALL(m_scl, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_sda, _set(gpio::Pin::Off)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::Off), Return(0)));

    EXPECT_CALL(m_scl, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_scl, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    EXPECT_CALL(m_sda, _set(gpio::Pin::HiZ)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(m_sda, _get(_)).Times(1).WillOnce(DoAll(SetArgReferee<0>(gpio::Pin::On), Return(0)));

    int rc = m_bus->reset();
    EXPECT_EQ(0, rc);
}

} /* namespace i2c */
