#include "log.h"

#include <QDebug>

void Log::debug(const QString &msg)
{
    qDebug() << msg;
    Log::history.append(msg);
}

QList<QString> Log::history = {};
