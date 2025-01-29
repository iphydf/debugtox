#include "groupmessage.h"

#include "src/models/enums/messagetype_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupMessage::GroupMessage(const Tox_Event_Group_Message* event)
    : groupNumber(tox_event_group_message_get_group_number(event))
    , peerId(tox_event_group_message_get_peer_id(event))
    , messageType(Enums::fromTox(tox_event_group_message_get_message_type(event)))
    , message(tox_event_group_message_get_message(event),
              tox_event_group_message_get_message_length(event))
    , messageId(tox_event_group_message_get_message_id(event))
{
}

GroupMessage::~GroupMessage() = default;

QString GroupMessage::toString() const
{
    return QStringLiteral("GroupMessage(groupNumber: %1, peerId: %2, messageType: %3, message: %4, "
                          "messageId: %5)")
        .arg(groupNumber)
        .arg(peerId)
        .arg(Enums::toString(messageType))
        .arg(message.toString())
        .arg(messageId);
}
} // namespace Events
