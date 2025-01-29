#include "groupexittype_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

GroupExitType::Type Enums::fromTox(Tox_Group_Exit_Type value)
{
    switch (value) {
    case TOX_GROUP_EXIT_TYPE_QUIT:
        return GroupExitType::Type::QUIT;
    case TOX_GROUP_EXIT_TYPE_TIMEOUT:
        return GroupExitType::Type::TIMEOUT;
    case TOX_GROUP_EXIT_TYPE_DISCONNECTED:
        return GroupExitType::Type::DISCONNECTED;
    case TOX_GROUP_EXIT_TYPE_SELF_DISCONNECTED:
        return GroupExitType::Type::SELF_DISCONNECTED;
    case TOX_GROUP_EXIT_TYPE_KICK:
        return GroupExitType::Type::KICK;
    case TOX_GROUP_EXIT_TYPE_SYNC_ERROR:
        return GroupExitType::Type::SYNC_ERROR;
    }
    return GroupExitType::Type::QUIT;
}
Tox_Group_Exit_Type Enums::toTox(GroupExitType::Type value)
{
    switch (value) {
    case GroupExitType::Type::QUIT:
        return TOX_GROUP_EXIT_TYPE_QUIT;
    case GroupExitType::Type::TIMEOUT:
        return TOX_GROUP_EXIT_TYPE_TIMEOUT;
    case GroupExitType::Type::DISCONNECTED:
        return TOX_GROUP_EXIT_TYPE_DISCONNECTED;
    case GroupExitType::Type::SELF_DISCONNECTED:
        return TOX_GROUP_EXIT_TYPE_SELF_DISCONNECTED;
    case GroupExitType::Type::KICK:
        return TOX_GROUP_EXIT_TYPE_KICK;
    case GroupExitType::Type::SYNC_ERROR:
        return TOX_GROUP_EXIT_TYPE_SYNC_ERROR;
    }
    return TOX_GROUP_EXIT_TYPE_QUIT;
}

QString Enums::toString(GroupExitType::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<GroupExitType::Type>().valueToKey(static_cast<int>(value)));
}
