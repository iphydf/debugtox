#pragma once

#include <QMetaType>

namespace UserStatus {
Q_NAMESPACE
enum class Type
{
    NONE,
    AWAY,
    BUSY,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(UserStatus::Type value);
}
