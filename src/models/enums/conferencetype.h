#pragma once

#include <QMetaType>

namespace ConferenceType {
Q_NAMESPACE
enum class Type
{
    TEXT,
    AV,
};

Q_ENUM_NS(Type)
} // namespace ConferenceType

namespace Enums {
QString toString(ConferenceType::Type value);
}
