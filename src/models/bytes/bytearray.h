#pragma once

#include <QByteArray>

class ByteArray
{
public:
    ByteArray(const uint8_t* data, size_t size);

    QString toString() const;

private:
    QByteArray data;
};
