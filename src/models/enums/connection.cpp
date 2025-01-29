#include "connection_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

Connection::Type Enums::fromTox(Tox_Connection value)
{
    switch (value) {
    case TOX_CONNECTION_NONE:
        return Connection::Type::NONE;
    case TOX_CONNECTION_TCP:
        return Connection::Type::TCP;
    case TOX_CONNECTION_UDP:
        return Connection::Type::UDP;
    }
    return Connection::Type::NONE;
}
Tox_Connection Enums::toTox(Connection::Type value)
{
    switch (value) {
    case Connection::Type::NONE:
        return TOX_CONNECTION_NONE;
    case Connection::Type::TCP:
        return TOX_CONNECTION_TCP;
    case Connection::Type::UDP:
        return TOX_CONNECTION_UDP;
    }
    return TOX_CONNECTION_NONE;
}

QString Enums::toString(Connection::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<Connection::Type>().valueToKey(static_cast<int>(value)));
}
