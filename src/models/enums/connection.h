#pragma once

#include <QMetaType>

namespace Connection {
Q_NAMESPACE
enum class Type
{
    NONE,
    TCP,
    UDP,
};

Q_ENUM_NS(Type)
} // namespace Connection

namespace Enums {
QString toString(Connection::Type value);
}
