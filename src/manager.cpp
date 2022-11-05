#include <QDebug>
#include "manager.h"

using namespace i2chandler;
using namespace poller;

namespace {
    /* path used to interact with I2C sensor. */
    constexpr char i2cpath[] = "/dev/i2c-2";
    /* path used to interact with memory-mapped sensor. */
    constexpr char mmpath[] = "/sys/class/mmsens/mmsens0";
}

namespace manager {

Manager::Manager(QObject *parent) : m_i2csens{new I2CHandler{i2cpath}}, m_mmsens{new Poller{mmpath}}
{
    /* I2C sensor signals. */
    QObject::connect(m_i2csens, SIGNAL(readData(int)), this, SIGNAL(newI2CSensValue(int)));
    QObject::connect(this, SIGNAL(callEnableI2CSens(bool)), m_i2csens, SLOT(enable(bool)));

    /* Memory-mapped sensor signals. */
    QObject::connect(m_mmsens, SIGNAL(readData(QString)), this, SIGNAL(newMMSensValue(QString)));
    QObject::connect(this, SIGNAL(callEnableMMSens(bool,QString)), m_mmsens, SLOT(enable(bool,QString)));
    QObject::connect(this, SIGNAL(callSetSamplingSpeed(QString)), m_mmsens, SLOT(setSamplingSpeed(QString)));
}

//-----------------------------------------------------------------------------

Manager &Manager::getInstance(void)
{
    static Manager manager;
    return manager;
}

//-----------------------------------------------------------------------------

Manager::~Manager()
{}

//-----------------------------------------------------------------------------

void Manager::enableMMSens(const bool enable, const QString speed)
{
    qDebug() << "Got Enable MMSENS" << enable << " with speed" << speed;
    emit callEnableMMSens(enable, speed);
}

//-----------------------------------------------------------------------------

void Manager::setSamplingSpeed(const QString speed)
{
    qDebug() << "Got Set Sampling Speed" << speed;
    emit callSetSamplingSpeed(speed);
}

//-----------------------------------------------------------------------------

void Manager::enableI2CSens(const bool enable)
{
    qDebug() << "Got Enable I2Csens" << enable;
    emit callEnableI2CSens(enable);
}


} // namespace manager
