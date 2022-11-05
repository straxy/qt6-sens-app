/**
 * @file manager.h
 * @author Strahinja Jankovic (strahinja.p.jankovic@gmail.com)
 *
 * @brief Manager class which routes data between Cpp and Qml parts
 * @details This class handles signals between Cpp and Qml parts of the code.
 * This way UI implementation can remain independent of the Engine.
 */
#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "poller.h"
#include "i2chandler.h"

namespace manager {

class Manager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Destructor
     */
    virtual ~Manager();

    /**
     * @brief getInstance
     * Get pointer to Manager, singleton
     */
    static Manager& getInstance();
signals:
    /**
     * @brief new memory-mapped sensor value
     * @param data - 4 byte string
     */
    void newMMSensValue(const QString data);

    /**
     * @brief new I2C Sensor Value
     * @param temp - mesured temperature in 0.5 degrees resolution
     */
    void newI2CSensValue(const int temp);

    /**
     * @brief callEnableMMSens
     * Call passed to Poller class
     * @param enable
     * @param speed
     */
    void callEnableMMSens(const bool enable, const QString speed = "normal");

    /**
     * @brief call Set Sampling Speed
     * Call passed to Poller class
     * @param speed
     */
    void callSetSamplingSpeed(const QString speed = "normal");

    /**
     * @brief call Enable I2C Sens
     * Call passed to I2CHandler class
     * @param enable
     */
    void callEnableI2CSens(const bool enable);

public slots:
    /**
     * @brief enable memory mapped sensor and enable interrupt
     * @param enable - set whether it is enabled or disabled
     * @param speed - sampling speed, can be either normal or fast
     */
    void enableMMSens(const bool enable, const QString speed = "normal");

    /**
     * @brief set Sampling Speed for the memory mapped sensor
     * @param speed - "normal" or "fast"
     */
    void setSamplingSpeed(const QString speed = "normal");

    /**
     * @brief enable I2C Sensor
     * @param enable
     */
    void enableI2CSens(const bool enable);

private:
    /**
     * @brief Manager - private constructor
     * @param parent
     */
    Manager(QObject *parent = 0);

    /**
     * @brief m_mmsens
     * Pointer to a poller instance that handles mmsens
     */
    poller::Poller* m_mmsens;

    /**
     * @brief m_i2csens
     * Pointer to a i2c handler instance
     */
    i2chandler::I2CHandler* m_i2csens;
};

}  // namespace manager

#endif // MANAGER_H
