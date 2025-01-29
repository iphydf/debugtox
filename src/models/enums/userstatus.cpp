#include "userstatus_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

UserStatus::Type Enums::fromTox(Tox_User_Status value)
{
    switch (value) {
    case TOX_USER_STATUS_NONE:
        return UserStatus::Type::NONE;
    case TOX_USER_STATUS_AWAY:
        return UserStatus::Type::AWAY;
    case TOX_USER_STATUS_BUSY:
        return UserStatus::Type::BUSY;
    }
    return UserStatus::Type::NONE;
}
Tox_User_Status Enums::toTox(UserStatus::Type value)
{
    switch (value) {
    case UserStatus::Type::NONE:
        return TOX_USER_STATUS_NONE;
    case UserStatus::Type::AWAY:
        return TOX_USER_STATUS_AWAY;
    case UserStatus::Type::BUSY:
        return TOX_USER_STATUS_BUSY;
    }
    return TOX_USER_STATUS_NONE;
}

QString Enums::toString(UserStatus::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<UserStatus::Type>().valueToKey(static_cast<int>(value)));
}
