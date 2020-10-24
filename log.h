#ifndef LOG_H
#define LOG_H

#include <QString>

namespace Log
{

    extern QList<QString> history;

    void debug(const QString &);

} // namespace Log

#endif // LOG_H
