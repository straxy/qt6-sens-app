/**
 *
 * @file sysfsattr.h
 * @author Strahinja Jankovic (strahinja.p.jankovic[at]gmail.com)
 * @details Implementation of sysfs attribute class
 */

#ifndef _SYSFS_ATTR_H_
#define _SYSFS_ATTR_H_

#include <QString>

namespace sysfsattr
{

class SysfsAttr
{
public:
    /**
     * @brief Constructor
     * @param path - path to sysfs attribute
     */
    explicit SysfsAttr(const QString& path);

    /** Disable copy constructor and assignment. */
    SysfsAttr(const SysfsAttr&)              = delete;
    SysfsAttr & operator=(const SysfsAttr&)  = delete;

    /** Destructor. */
    virtual ~SysfsAttr();

    /**
     * @brief read
     * Read string value from sysfs attribute.
     * @param buf - pointer to buffer where read data will be stored
     * @returns bool - True if read was successful
     */
    bool read(QString *buf);

    /**
     * @brief write
     * Write string value to sysfs attribute.
     * @param data - data to write
     * @returns bool - True if write was successful
     */
    bool write(const QString &data);

    /**
     * @brief read
     * Read one byte value interpreted as uint8_t
     * @param buf - pointer to buffer where read data will be stored
     * @returns bool - True if read was successful
     */
    bool read(uint8_t *buf);

    /**
     * @brief write
     * Write one byte value interpreted as uint8_t
     * @param data - data to write
     * @returns bool - True if read was successful
     */
    bool write(const uint8_t &data);

private:
    /** Stored attribute path. */
    QString m_path;
};

}   // namespace sysfsattr

#endif  // _SYSFS_ATTR_H_
