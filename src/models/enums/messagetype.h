#pragma once

#include <QMetaType>

namespace MessageType {
Q_NAMESPACE
enum class Type
{
    NORMAL,
    ACTION,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(MessageType::Type value);
}
