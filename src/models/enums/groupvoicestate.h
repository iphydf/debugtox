#pragma once

#include <QMetaType>

namespace GroupVoiceState {
Q_NAMESPACE
enum class Type
{
    ALL,
    MODERATOR,
    FOUNDER,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(GroupVoiceState::Type value);
}
