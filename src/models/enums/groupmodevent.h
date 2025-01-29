#pragma once

#include <QMetaType>

namespace GroupModEvent {
Q_NAMESPACE
enum class Type
{
    KICK,
    OBSERVER,
    USER,
    MODERATOR,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(GroupModEvent::Type value);
}
