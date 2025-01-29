#include "conferencetype_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

ConferenceType::Type Enums::fromTox(Tox_Conference_Type value)
{
    switch (value) {
    case TOX_CONFERENCE_TYPE_TEXT:
        return ConferenceType::Type::TEXT;
    case TOX_CONFERENCE_TYPE_AV:
        return ConferenceType::Type::AV;
    }
    return ConferenceType::Type::TEXT;
}
Tox_Conference_Type Enums::toTox(ConferenceType::Type value)
{
    switch (value) {
    case ConferenceType::Type::TEXT:
        return TOX_CONFERENCE_TYPE_TEXT;
    case ConferenceType::Type::AV:
        return TOX_CONFERENCE_TYPE_AV;
    }
    return TOX_CONFERENCE_TYPE_TEXT;
}

QString Enums::toString(ConferenceType::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<ConferenceType::Type>().valueToKey(static_cast<int>(value)));
}
