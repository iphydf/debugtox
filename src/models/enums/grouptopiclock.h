#pragma once

#include <QMetaType>

namespace GroupTopicLock {
Q_NAMESPACE
enum class Type
{
    ENABLED,
    DISABLED,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(GroupTopicLock::Type value);
}
