/**
 * @file Poller.h
 * @author Strahinja Jankovic (strahinja.p.jankovic[at]gmail.com)
 * @details Implementation of polling mechanism
 */

#ifndef _POLLER_H_
#define _POLLER_H_

#include <QObject>
#include <QString>
#include <QMap>
#include <QFileSystemWatcher>
#include "sysfsattr.h"

using namespace sysfsattr;

namespace poller
{

class Poller : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param path - path to sysfs device
     */
    explicit Poller(QString path = "", QObject *parent = nullptr);

    /** Disable copy constructor and assignment. */
    Poller(const Poller&)              = delete;
    Poller & operator=(const Poller&)  = delete;

    /** Destructor. */
    virtual ~Poller();

    /**
     * @brief init
     * Initialize device and enable interrupt generation.
     */
    void init(QString sspeed = "normal");

    /**
     * @brief deinit
     * Disable interrupt generation and turn off device.
     */
    void deinit(void);

public slots:
    /**
     * @brief enable
     * Function that enables memory-mapped sensor and interrupt
     * @param en
     * @param sspeed
     */
    void enable(bool en, QString sspeed);

    /**
     * @brief setSamplingSpeed
     * Set sampling speed for the memory-mapped sensor
     * @param sspeed
     */
    void setSamplingSpeed(QString sspeed);

signals:
    /**
     * @brief readData
     * Sends data that was read
     */
    void readData(QString);

private:
    /**
     * @brief do_read
     * Callback that checks interrupt attribute.
     */
    void do_read(void);

    /** Path to sysfs device. */
    QString m_path;

    /** Map where all attributes are stored. */
    QMap<QString, SysfsAttr *> m_attributes;

    /** File system watcher for sysfs where notify is called. */
    QFileSystemWatcher* m_notifyFile;
};

}   // namespace poller

#endif  // _POLLER_H_
