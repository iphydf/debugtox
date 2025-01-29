#pragma once

#include <QMetaType>

namespace GroupJoinFail {
Q_NAMESPACE
enum class Type
{
    PEER_LIMIT,
    INVALID_PASSWORD,
    UNKNOWN,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(GroupJoinFail::Type value);
}
