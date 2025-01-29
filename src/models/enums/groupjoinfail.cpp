#include "groupjoinfail_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

GroupJoinFail::Type Enums::fromTox(Tox_Group_Join_Fail value)
{
    switch (value) {
    case TOX_GROUP_JOIN_FAIL_PEER_LIMIT:
        return GroupJoinFail::Type::PEER_LIMIT;
    case TOX_GROUP_JOIN_FAIL_INVALID_PASSWORD:
        return GroupJoinFail::Type::INVALID_PASSWORD;
    case TOX_GROUP_JOIN_FAIL_UNKNOWN:
        return GroupJoinFail::Type::UNKNOWN;
    }
    return GroupJoinFail::Type::UNKNOWN;
}
Tox_Group_Join_Fail Enums::toTox(GroupJoinFail::Type value)
{
    switch (value) {
    case GroupJoinFail::Type::PEER_LIMIT:
        return TOX_GROUP_JOIN_FAIL_PEER_LIMIT;
    case GroupJoinFail::Type::INVALID_PASSWORD:
        return TOX_GROUP_JOIN_FAIL_INVALID_PASSWORD;
    case GroupJoinFail::Type::UNKNOWN:
        return TOX_GROUP_JOIN_FAIL_UNKNOWN;
    }
    return TOX_GROUP_JOIN_FAIL_UNKNOWN;
}

QString Enums::toString(GroupJoinFail::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<GroupJoinFail::Type>().valueToKey(static_cast<int>(value)));
}
