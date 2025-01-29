#include "groupprivacystate_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

GroupPrivacyState::Type Enums::fromTox(Tox_Group_Privacy_State value)
{
    switch (value) {
    case TOX_GROUP_PRIVACY_STATE_PUBLIC:
        return GroupPrivacyState::Type::PUBLIC;
    case TOX_GROUP_PRIVACY_STATE_PRIVATE:
        return GroupPrivacyState::Type::PRIVATE;
    }
    return GroupPrivacyState::Type::PUBLIC;
}
Tox_Group_Privacy_State Enums::toTox(GroupPrivacyState::Type value)
{
    switch (value) {
    case GroupPrivacyState::Type::PUBLIC:
        return TOX_GROUP_PRIVACY_STATE_PUBLIC;
    case GroupPrivacyState::Type::PRIVATE:
        return TOX_GROUP_PRIVACY_STATE_PRIVATE;
    }
    return TOX_GROUP_PRIVACY_STATE_PUBLIC;
}

QString Enums::toString(GroupPrivacyState::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<GroupPrivacyState::Type>().valueToKey(static_cast<int>(value)));
}
