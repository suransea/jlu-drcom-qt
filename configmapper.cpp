#include "configmapper.h"

#include <QFile>

ConfigMapper ConfigMapper::instance("drcom-client.conf");

ConfigMapper::ConfigMapper(const QString &filename) : filename(filename)
{
    reload();
}

void ConfigMapper::reload()
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        if (line[0] == '#' || line.size() == 0)
            continue;
        QString key{}, value{};
        bool flag = true;
        for (char c : line)
        {
            if (c == '\n')
            {
                break;
            }
            if (flag)
            {
                if (c == '=')
                {
                    flag = false;
                    continue;
                }
                key.append(c);
            }
            else
            {
                value.append(c);
            }
        }
        config[key] = value;
    }
    file.close();
}

QMap<QString, QString> ConfigMapper::get()
{
    return config;
}

void ConfigMapper::set(const QString &key, const QString &value)
{
    config[key] = value;
}

void ConfigMapper::flush()
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    for (auto &it : config.keys())
    {
        file.write(it.toUtf8());
        file.write("=");
        file.write(config[it].toUtf8());
        file.write("\n");
    }
    file.close();
}

QString ConfigMapper::operator[](const QString &key)
{
    return config[key];
}
