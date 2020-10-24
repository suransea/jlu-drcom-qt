#ifndef CONFIGUREREADER_H
#define CONFIGUREREADER_H

#include <QString>
#include <QMap>

class ConfigMapper
{
    QMap<QString, QString> config;

    QString filename;

public:
    static ConfigMapper instance;

    ConfigMapper(const QString &filename);

    QMap<QString, QString> get();

    void set(const QString &key, const QString &value);

    void reload();

    void flush();

    QString operator[](const QString &key);
};

#endif // CONFIGUREREADER_H
