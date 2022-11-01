/**
 * @file I2CHandler.h
 * @author Strahinja Jankovic (strahinja.p.jankovic[at]gmail.com)
 * @details Implementation of I2C userspace handling
 */

#ifndef _I2C_HANDLER_H_
#define _I2C_HANDLER_H_

#include <QObject>
#include <QString>
#include <QTimer>

namespace i2chandler
{

class I2CHandler : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param path: path to I2C device
     */
    explicit I2CHandler(QString path, QObject *parent = nullptr);

    /** Disable copy constructor and assignment. */
    I2CHandler(const I2CHandler&)              = delete;
    I2CHandler & operator=(const I2CHandler&)  = delete;

    /** Destructor. */
    virtual ~I2CHandler();

    /**
     * @brief init
     * Initialize I2C device.
     */
    int8_t init(void);

    /**
     * @brief deinit
     * Disable I2C device.
     */
    void deinit(void);

public slots:
    /**
     * @brief enable
     * Init or deinit based on @p en
     * @param en
     */
    void enable(bool en);

signals:
    /**
     * @brief readData
     * Send data that was read.
     */
    void readData(int);

private slots:
    /**
     * @brief do_read
     * Timer callback that reads I2C temperature data.
     */
    void do_read(void);

private:
    /**
     * @brief write_reg
     * Helper function to write register value.
     */
    bool write_reg(uint8_t reg_nr, uint8_t val);

    /**
     * @brief read_reg
     * Helper function to read register value
     */
    bool read_reg(uint8_t reg_nr, uint8_t& val);

    /**
     * @brief m_path
     * Path to I2C device.
     */
    QString m_path;

    /**
     * @brief m_timer
     * Periodic timer
     */
    QTimer* m_timer;

    /**
     * @brief m_fd
     * I2C dev file descriptor.
     */
    int m_fd;
};

}   // namespace i2chandler

#endif  // _I2C_HANDLER_H_
