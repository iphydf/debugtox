#include "grouptopic.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupTopic::GroupTopic(const Tox_Event_Group_Topic* event)
    : groupNumber(tox_event_group_topic_get_group_number(event))
    , peerId(tox_event_group_topic_get_peer_id(event))
    , topic(tox_event_group_topic_get_topic(event), tox_event_group_topic_get_topic_length(event))
{
}

GroupTopic::~GroupTopic() = default;

QString GroupTopic::toString() const
{
    return QStringLiteral("GroupTopic(groupNumber: %1, peerId: %2, topic: %3)")
        .arg(groupNumber)
        .arg(peerId)
        .arg(topic.toString());
}
} // namespace Events
