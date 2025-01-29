#pragma once

#include <QMetaType>

namespace GroupExitType {
Q_NAMESPACE
enum class Type
{
    QUIT,
    TIMEOUT,
    DISCONNECTED,
    SELF_DISCONNECTED,
    KICK,
    SYNC_ERROR,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(GroupExitType::Type value);
}
