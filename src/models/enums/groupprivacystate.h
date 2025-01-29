#pragma once

#include <QMetaType>

namespace GroupPrivacyState {
Q_NAMESPACE
enum class Type
{
    PUBLIC,
    PRIVATE,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(GroupPrivacyState::Type value);
}
