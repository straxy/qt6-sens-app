/**
 * @file sysfsattr.cpp
 * @author Strahinja Jankovic (strahinja.p.jankovic[at]gmail.com)
 * @details Implementation of sysfs attribute class
 */

#include "sysfsattr.h"
#include <QFile>
#include <QTextStream>

namespace sysfsattr
{

SysfsAttr::SysfsAttr(const QString &path) : m_path{path}
{
}

//-----------------------------------------------------------------------------

SysfsAttr::~SysfsAttr()
{
}

//-----------------------------------------------------------------------------

bool SysfsAttr::read(QString *buf)
{
    bool read = false;
    QFile file(m_path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream ifile(&file);
        ifile >> *buf;
        read = true;
        file.close();
    }
    return read;
}

//-----------------------------------------------------------------------------

bool SysfsAttr::write(const QString &data)
{
    bool written = false;
    QFile file(m_path);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream ofile(&file);
        ofile << data;
        file.close();
        written = true;
    }
    return written;
}

//-----------------------------------------------------------------------------

bool SysfsAttr::read(uint8_t *buf)
{
    QString tmp;
    bool ret = false;

    if (read(&tmp))
    {
        *buf = tmp.toUShort();
        ret = true;
    }

    return ret;
}

//-----------------------------------------------------------------------------

bool SysfsAttr::write(const uint8_t &data)
{
    QString tmp = QString::number(data);

    return write(tmp);
}

//-----------------------------------------------------------------------------

}   // namespace sysfsattr
