#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "i2chandler.h"

using namespace i2chandler;

namespace
{
    constexpr uint8_t I2CSENS_ADDR = 0x36;
    // Register definitions
    enum class I2CSensRegs : uint8_t
    {
        ID,
        CTRL,
        TEMPERATURE
    };
    // Enable value
    constexpr uint8_t ENABLE = 0x01;
};  // namespace anonymous

//-----------------------------------------------------------------------------

I2CHandler::I2CHandler(QString path, QObject *parent) : QObject{parent}, m_path{path}
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &I2CHandler::do_read);
}

//-----------------------------------------------------------------------------

I2CHandler::~I2CHandler()
{
}

//-----------------------------------------------------------------------------

void I2CHandler::enable(bool en)
{
    if (en)
    {
        (void)init();
    }
    else
    {
        deinit();
    }
}

//-----------------------------------------------------------------------------

int8_t I2CHandler::init(void)
{
    // Open FD
    m_fd = open(m_path.toStdString().c_str(), O_RDWR);
    if (m_fd == -1)
    {
        return m_fd;
    }

    // Set I2C slave address
    if (ioctl(m_fd, I2C_SLAVE, I2CSENS_ADDR) < 0)
    {
        return -2;
    }

    // Enable device
    if (!write_reg(static_cast<uint8_t>(I2CSensRegs::CTRL), ENABLE))
    {
        return -3;
    }

    // Start timer
    m_timer->start(1000);

    return 0;
}

//-----------------------------------------------------------------------------

void I2CHandler::deinit(void)
{
    m_timer->stop();

    if (!write_reg(static_cast<uint8_t>(I2CSensRegs::CTRL), 0))
    {
        std::cerr << "Problem disabling device";
    }
}

//-----------------------------------------------------------------------------

void I2CHandler::do_read(void)
{
    uint8_t value;

    // read I2C device and print
    if (read_reg(static_cast<uint8_t>(I2CSensRegs::TEMPERATURE), value))
    {
        emit readData(value);
    }
}

//-----------------------------------------------------------------------------

bool I2CHandler::write_reg(uint8_t reg_nr, uint8_t val)
{
    uint8_t buffer[2] = { reg_nr, val };

    return (write(m_fd, buffer, 2) == 2);
}

//-----------------------------------------------------------------------------

bool I2CHandler::read_reg(uint8_t reg_nr, uint8_t& val)
{
    uint8_t buffer[1] = { reg_nr };
    bool retval = (write(m_fd, buffer, 1) == 1);

    if (retval)
    {
        retval = (read(m_fd, buffer, 1) == 1);
        if (retval)
        {
            val = buffer[0];
        }
    }

    return retval;
}
