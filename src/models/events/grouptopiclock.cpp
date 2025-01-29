#include "grouptopiclock.h"

#include "src/models/enums/grouptopiclock_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupTopicLock::GroupTopicLock(const Tox_Event_Group_Topic_Lock* event)
    : groupNumber(tox_event_group_topic_lock_get_group_number(event))
    , topicLock(Enums::fromTox(tox_event_group_topic_lock_get_topic_lock(event)))
{
}

GroupTopicLock::~GroupTopicLock() = default;

QString GroupTopicLock::toString() const
{
    return QStringLiteral("GroupTopicLock(groupNumber: %1, topicLock: %2)")
        .arg(groupNumber)
        .arg(Enums::toString(topicLock));
}
} // namespace Events
