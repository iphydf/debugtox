#pragma once

#include <QMetaType>

namespace FileControl {
Q_NAMESPACE
enum class Type
{
    RESUME,
    PAUSE,
    CANCEL,
};

Q_ENUM_NS(Type);
}

namespace Enums {
QString toString(FileControl::Type value);
}
