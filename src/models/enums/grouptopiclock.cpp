#include "grouptopiclock_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

GroupTopicLock::Type Enums::fromTox(Tox_Group_Topic_Lock value)
{
    switch (value) {
    case TOX_GROUP_TOPIC_LOCK_ENABLED:
        return GroupTopicLock::Type::ENABLED;
    case TOX_GROUP_TOPIC_LOCK_DISABLED:
        return GroupTopicLock::Type::DISABLED;
    }
    return GroupTopicLock::Type::ENABLED;
}
Tox_Group_Topic_Lock Enums::toTox(GroupTopicLock::Type value)
{
    switch (value) {
    case GroupTopicLock::Type::ENABLED:
        return TOX_GROUP_TOPIC_LOCK_ENABLED;
    case GroupTopicLock::Type::DISABLED:
        return TOX_GROUP_TOPIC_LOCK_DISABLED;
    }
    return TOX_GROUP_TOPIC_LOCK_ENABLED;
}

QString Enums::toString(GroupTopicLock::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<GroupTopicLock::Type>().valueToKey(static_cast<int>(value)));
}
