#include <QVector>
#include <QDebug>

#include "poller.h"

using namespace poller;

namespace
{
    /** Names of all attributes that are used. */
    const QVector<QString> attributes =
    {
        "enable",
        "enable_interrupt",
        "data",
        "frequency"
    };
};  // namespace anonymous

//-----------------------------------------------------------------------------

Poller::Poller(QString path, QObject *parent) : QObject{parent}, m_path{path}
{
    // Create attributes
    for (auto &attr : attributes)
    {
        m_attributes[attr] = new SysfsAttr(m_path + "/" + attr);
    }
    // Initialize file watcher
    m_notifyFile = new QFileSystemWatcher{this};
    m_notifyFile->addPath(m_path + "/interrupt");
    connect(m_notifyFile, &QFileSystemWatcher::fileChanged, this, &Poller::do_read);
}

//-----------------------------------------------------------------------------

Poller::~Poller()
{
    // Cleanup attributes list
    for (auto &attr : attributes)
    {
        delete(m_attributes[attr]);
    }
    m_attributes.clear();
}

//-----------------------------------------------------------------------------

void Poller::init(QString sspeed)
{
    // Enable device
    m_attributes["enable"]->write(1);

    // Configure frequency
    m_attributes["frequency"]->write(sspeed);

    // Enable interrupt
    m_attributes["enable_interrupt"]->write(1);
}

//-----------------------------------------------------------------------------

void Poller::deinit(void)
{
    // Disable interrupt
    m_attributes["enable_interrupt"]->write(0);

    // Disable device
    m_attributes["enable"]->write(0);
}

//-----------------------------------------------------------------------------

void Poller::enable(bool en, QString sspeed)
{
    if (en)
    {
        init(sspeed);
    }
    else
    {
        deinit();
    }
}

//-----------------------------------------------------------------------------

void Poller::setSamplingSpeed(QString sspeed)
{
    m_attributes["frequency"]->write(sspeed);
}

//-----------------------------------------------------------------------------

void Poller::do_read(void)
{
    QString data;

    // Read and print data value
    m_attributes["data"]->read(&data);
    qDebug() << data;
    emit readData(data);
}
