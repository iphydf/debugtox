#include "groupmodevent_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

GroupModEvent::Type Enums::fromTox(Tox_Group_Mod_Event value)
{
    switch (value) {
    case TOX_GROUP_MOD_EVENT_KICK:
        return GroupModEvent::Type::KICK;
    case TOX_GROUP_MOD_EVENT_OBSERVER:
        return GroupModEvent::Type::OBSERVER;
    case TOX_GROUP_MOD_EVENT_USER:
        return GroupModEvent::Type::USER;
    case TOX_GROUP_MOD_EVENT_MODERATOR:
        return GroupModEvent::Type::MODERATOR;
    }
    return GroupModEvent::Type::KICK;
}
Tox_Group_Mod_Event Enums::toTox(GroupModEvent::Type value)
{
    switch (value) {
    case GroupModEvent::Type::KICK:
        return TOX_GROUP_MOD_EVENT_KICK;
    case GroupModEvent::Type::OBSERVER:
        return TOX_GROUP_MOD_EVENT_OBSERVER;
    case GroupModEvent::Type::USER:
        return TOX_GROUP_MOD_EVENT_USER;
    case GroupModEvent::Type::MODERATOR:
        return TOX_GROUP_MOD_EVENT_MODERATOR;
    }
    return TOX_GROUP_MOD_EVENT_KICK;
}

QString Enums::toString(GroupModEvent::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<GroupModEvent::Type>().valueToKey(static_cast<int>(value)));
}
